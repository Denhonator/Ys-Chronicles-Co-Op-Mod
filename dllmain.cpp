// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <Windows.h>
#include <WinBase.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

HMODULE hOriginal = nullptr;
int baseAddress = 0;

int FindPointer(int offsets[], int count)
{
    int address = offsets[0];
    for (int i = 1; i < count; i++)
    {
        if(address < baseAddress || *(int*)address < baseAddress)
            return 0;
        address = *(int*)address + offsets[i];
    }
    return address;
}

template<typename T> T ReadValue(int offsets[], int count) {
	int address = count > 1 ? FindPointer(offsets, count) : offsets[0];
	return address >= baseAddress ? *(T*)address : 0;
}

template<typename T> void WriteValue(int offsets[], int count, T value) {
    int address = count > 1 ? FindPointer(offsets, count) : offsets[0];
	if (address >= baseAddress)
	    *(T*)address = value;
}

template<typename T> T ReadValue(int offset) {
    return offset >= baseAddress ? *(T*)offset : 0;
}

template<typename T> void WriteValue(int offset, T value) {
    if (offset >= baseAddress)
        *(T*)offset = value;
}

void WriteBytes(int offset, const char* bytes, size_t size) {
    if (offset < baseAddress)
        return;
    DWORD oldProtect;
    VirtualProtect((void*)offset, size, PAGE_EXECUTE_READWRITE, &oldProtect);
    memcpy((void*)offset, bytes, size);
    VirtualProtect((void*)offset, size, oldProtect, &oldProtect);
}

DWORD WINAPI HookThread(LPVOID) {
	OutputDebugStringA("HookThread started");

    baseAddress = (int)GetModuleHandle(NULL);

    char buffer[512];
    sprintf_s(buffer, "Base address: 0x%p\n", (void*)baseAddress);
    OutputDebugStringA(buffer);

    char processName[MAX_PATH];
    GetModuleFileNameA(NULL, processName, MAX_PATH);

    char* filename = strrchr(processName, '\\');
    if (filename)
        filename++;
    else
        filename = processName;

    sprintf_s(buffer, "Process name: %s\n", filename);
    OutputDebugStringA(buffer);

    if(std::strcmp(filename, "ys2plus.exe")) {
        OutputDebugStringA("Not ys2plus.exe, exiting thread");
        return 0;
	}

	char UP = 'I', DOWN = 'K', LEFT = 'J', RIGHT = 'L', WALK = 'U';
	float maxDistanceX = 400.0f;
	float maxDistanceY = 250.0f;
	std::ifstream config("coop_config.txt");
	// If the config file doesn't exist, create it with default values
	if (!config.is_open()) {
		std::ofstream newConfig("coop_config.txt");
		newConfig << "Up = I\n";
		newConfig << "Down = K\n";
		newConfig << "Left = J\n";
		newConfig << "Right = L\n";
		newConfig << "Walk = U\n";
		newConfig << "MaxDistanceX = 400.0\n";
		newConfig << "MaxDistanceY = 250.0\n";

		newConfig.close();
		OutputDebugStringA("Config file created with default values");
	}
	// If the config file exists, read the key bindings
    else {
        std::string key, value;
        while (std::getline(config, key, '=') && std::getline(config, value)) {
			key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
			value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());
            if (key.find("Up") != std::string::npos) UP = value[0];
            else if (key.find("Down") != std::string::npos) DOWN = value[0];
            else if (key.find("Left") != std::string::npos) LEFT = value[0];
            else if (key.find("Right") != std::string::npos) RIGHT = value[0];
            else if (key.find("Walk") != std::string::npos) WALK = value[0];
            else if (key.find("MaxDistanceX") != std::string::npos) maxDistanceX = std::stof(value);
            else if (key.find("MaxDistanceY") != std::string::npos) maxDistanceY = std::stof(value);
        }
    }

    int posXAddr[2] = { baseAddress + 0x1453D0, 0x14 };
	int TarfToggle = baseAddress + 0x25d3f0;
	int AdolData = baseAddress + 0x1453D0;
	int TarfData = baseAddress + 0x1453D8;
	int TarfScan[2] = { baseAddress + 0x1453D4, 0x1DC };
	int TarfUI = baseAddress + 0x25D3F4;
    int TarfStats = baseAddress + 0x12C3F0;
	int ResetSpeedCode = baseAddress + 0x1A0D4;
	int ResetAnimCode = baseAddress + 0x1A0E3;
	int TarfRoomCheckCode = baseAddress + 0x8DA04;
    int CanMove = baseAddress + 0x135884;
    int AdolRoom = baseAddress + 0x25c730;
	int cam = baseAddress + 0x25D6D0;
	int BlackOrbStatus = baseAddress + 0x25C8A6;

	WriteBytes(ResetSpeedCode, "\x90\x90\x90\x90\x90\x90\x90", 7); //Nop out speed reset
	WriteBytes(ResetAnimCode, "\x90\x90\x90\x90\x90\x90\x90", 7);
	WriteBytes(TarfRoomCheckCode, "\x90\x90\xB3\x00", 4);

	int adolLastHP = ReadValue<short>(AdolData + 0xA0);

    while (true) {
        Sleep(10);

		int adol = ReadValue<int>(AdolData);
        TarfScan[0] = AdolData;
        while (ReadValue<int>(TarfScan[0]) >= baseAddress) {
            if (ReadValue<int>(TarfScan, 2) == 0x2C) {
				TarfData = TarfScan[0];
                break;
            }
			TarfScan[0] += 4;
        }
		int tarf = ReadValue<int>(TarfData);

        bool allowTarf = ReadValue<short>(BlackOrbStatus) == 0x0100 || ReadValue<int>(AdolRoom) != 98;
		WriteValue(adol + 0x24, 0.0f); //Reset Adol's speed to prevent sliding
		WriteValue<char>(TarfToggle, allowTarf ? 44 : 0); //Keep Tarf active

        if (ReadValue<int>(tarf) > baseAddress && ReadValue<int>(TarfUI) > 0) {
            WriteValue(tarf, 0x50B448);
            //WriteValue(tarf + 0x1D8, 1);  //Character type
            WriteValue(tarf + 0x1DC, 2);    //Character sprite
			float prevMaxHP = ReadValue<short>(TarfStats + 4);
			WriteValue(TarfStats + 4, ReadValue<short>(adol + 0xA4)); //Copy Tarf's HP from Adol's HP
            WriteValue(TarfStats + 6, ReadValue<short>(adol + 0xB0)); //Copy Tarf's STR from Adol's STR
            WriteValue(TarfStats + 8, ReadValue<short>(adol + 0xB4)); //Copy Tarf's DEF from Adol's DEF
			short curHP = ReadValue<short>(adol + 0xA0);
            if (prevMaxHP < ReadValue<short>(TarfStats + 4))
				WriteValue(tarf + 0xA0, ReadValue<short>(TarfStats + 4)); //If Tarf's max HP increased, heal him to full
            if(curHP > adolLastHP && adolLastHP > 0)
				WriteValue(tarf + 0xA0, ReadValue<short>(tarf + 0xA0) + curHP - adolLastHP);

			float verticalDir = (GetKeyState(UP) & 0x8000) ? 1.0f : ((GetKeyState(DOWN) & 0x8000) ? -1.0f : 0.0f);
			float horizontalDir = (GetKeyState(RIGHT) & 0x8000) ? 1.0f : ((GetKeyState(LEFT) & 0x8000) ? -1.0f : 0.0f);
            float speed = GetKeyState(WALK) & 0x8000 ? 1.5f : 3.5f;

            if((verticalDir != 0 || horizontalDir != 0) && !ReadValue<int>(CanMove)) {
                float rotation = 0;
                if (verticalDir < 0)
                    rotation = 1024.0f - horizontalDir * 512.0f;
                else if (verticalDir > 0)
                    rotation = 3072.0f + horizontalDir * 512.0f;
                else
					rotation = horizontalDir < 0 ? 2048.0f : 0.0f;

                WriteValue(tarf + 0x24, speed);
				WriteValue(tarf + 0x28, rotation);
				WriteValue(tarf + 0x2C, rotation);
				WriteValue<char>(tarf + 0x1D1, speed > 2.0f ? 1 : 0);
			}
            else
                WriteValue(tarf + 0x24, 0.0f);

			float camCenterX = ReadValue<int>(cam) + 296.0f;
			float camCenterY = ReadValue<int>(cam+4) + 192.0f;
            if(std::abs(ReadValue<float>(tarf + 0x14) - camCenterX) > maxDistanceX
            || std::abs(ReadValue<float>(tarf + 0x18) - camCenterY) > maxDistanceY) {
                WriteValue(tarf + 0x14, ReadValue<float>(adol + 0x14)+25.0f);
                WriteValue(tarf + 0x18, ReadValue<float>(adol + 0x18)-25.0f);
            }
        }

        adolLastHP = ReadValue<short>(adol + 0xA0);

        //float posX = ReadValue<float>(posXAddr, 2);
        //sprintf_s(buffer, "PosX: %.f", posX);
        //OutputDebugStringA(buffer);
    }
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
    if (dwReason == DLL_PROCESS_ATTACH) {
        char path[MAX_PATH];
        GetSystemDirectoryA(path, MAX_PATH);
        strcat_s(path, "\\dbghelp.dll");
        hOriginal = LoadLibraryA(path);

        CreateThread(nullptr, 0, HookThread, nullptr, 0, nullptr);
    }
    return TRUE;
}

#pragma comment(linker, "/export:SymCleanup=dbghelp_original.SymCleanup")
#pragma comment(linker, "/export:SymFromAddr=dbghelp_original.SymFromAddr")
#pragma comment(linker, "/export:SymGetSymFromAddr=dbghelp_original.SymGetSymFromAddr")
#pragma comment(linker, "/export:SymGetSymFromAddr64=dbghelp_original.SymGetSymFromAddr64")
#pragma comment(linker, "/export:SymGetOptions=dbghelp_original.SymGetOptions")
#pragma comment(linker, "/export:SymLoadModule64=dbghelp_original.SymLoadModule64")
#pragma comment(linker, "/export:SymLoadModule=dbghelp_original.SymLoadModule")
#pragma comment(linker, "/export:SymGetModuleInfo64=dbghelp_original.SymGetModuleInfo64")
#pragma comment(linker, "/export:SymGetModuleBase64=dbghelp_original.SymGetModuleBase64")
#pragma comment(linker, "/export:SymGetLineFromAddr64=dbghelp_original.SymGetLineFromAddr64")
#pragma comment(linker, "/export:SymSetOptions=dbghelp_original.SymSetOptions")
#pragma comment(linker, "/export:MiniDumpWriteDump=dbghelp_original.MiniDumpWriteDump")
#pragma comment(linker, "/export:StackWalk64=dbghelp_original.StackWalk64")
#pragma comment(linker, "/export:UnDecorateSymbolName=dbghelp_original.UnDecorateSymbolName")
#pragma comment(linker, "/export:SymInitialize=dbghelp_original.SymInitialize")
#pragma comment(linker, "/export:SymFunctionTableAccess64=dbghelp_original.SymFunctionTableAccess64")
#pragma comment(linker, "/export:SymGetModuleInfo=dbghelp_original.SymGetModuleInfo")
#pragma comment(linker, "/export:SymGetSearchPath=dbghelp_original.SymGetSearchPath")
#pragma comment(linker, "/export:SymSetSearchPath=dbghelp_original.SymSetSearchPath")
#pragma comment(linker, "/export:SymEnumSymbols=dbghelp_original.SymEnumSymbols")
#pragma comment(linker, "/export:SymFromName=dbghelp_original.SymFromName")
#pragma comment(linker, "/export:SymGetTypeInfo=dbghelp_original.SymGetTypeInfo")
#pragma comment(linker, "/export:SymRegisterCallback64=dbghelp_original.SymRegisterCallback64")
#pragma comment(linker, "/export:SymLoadModuleEx=dbghelp_original.SymLoadModuleEx")
#pragma comment(linker, "/export:SymUnloadModule64=dbghelp_original.SymUnloadModule64")
#pragma comment(linker, "/export:SymGetLineFromName64=dbghelp_original.SymGetLineFromName64")
#pragma comment(linker, "/export:SymEnumerateModules64=dbghelp_original.SymEnumerateModules64")
#pragma comment(linker, "/export:SymGetModuleBase=dbghelp_original.SymGetModuleBase")
#pragma comment(linker, "/export:ImageDirectoryEntryToData=dbghelp_original.ImageDirectoryEntryToData")
#pragma comment(linker, "/export:ImageNtHeader=dbghelp_original.ImageNtHeader")
#pragma comment(linker, "/export:ImageRvaToVa=dbghelp_original.ImageRvaToVa")
#pragma comment(linker, "/export:SymFindFileInPath=dbghelp_original.SymFindFileInPath")
#pragma comment(linker, "/export:SymMatchString=dbghelp_original.SymMatchString")
#pragma comment(linker, "/export:SymSearch=dbghelp_original.SymSearch")