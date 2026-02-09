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

    //uintptr_t address = baseAddress + 0x12345;
    //DWORD oldProtect;
    //VirtualProtect((void*)address, sizeof(int), PAGE_EXECUTE_READWRITE, &oldProtect);
    //*(int*)address = 999;
    //VirtualProtect((void*)address, sizeof(int), oldProtect, &oldProtect);

    int posXAddr[2] = { baseAddress + 0x1453D0, 0x14 };
	int TarfToggle = baseAddress + 0x25d3f0;
	int AdolData = baseAddress + 0x1453D0;
	int TarfData = baseAddress + 0x1453D8;
	int TarfScan[2] = { baseAddress + 0x1453D4, 0x1DC };
	int TarfUI = baseAddress + 0x25D3F4;
	int ResetSpeedCode = baseAddress + 0x1A0D4;
	int ResetAnimCode = baseAddress + 0x1A0E3;
	int TarfRoomCheckCode = baseAddress + 0x4CAB2;

	WriteBytes(ResetSpeedCode, "\x90\x90\x90\x90\x90\x90\x90", 7); //Nop out speed reset
	WriteBytes(ResetAnimCode, "\x90\x90\x90\x90\x90\x90\x90", 7);
	WriteBytes(TarfRoomCheckCode, "\x90\x90\x90\x90\x90\x90", 6);

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

		WriteValue(adol + 0x24, 0.0f); //Reset Adol's speed to prevent sliding
		WriteValue<char>(TarfToggle, 44); //Keep Tarf active

        if (ReadValue<int>(tarf) > baseAddress && ReadValue<int>(TarfUI) > 0) {
            WriteValue(tarf, 0x50B448);
            WriteValue(tarf + 0x1D8, 1);  //Character type
            WriteValue(tarf + 0x1DC, 2);    //Character sprite

			float verticalDir = (GetKeyState('I') & 0x8000) ? 1.0f : ((GetKeyState('K') & 0x8000) ? -1.0f : 0.0f);
			float horizontalDir = (GetKeyState('L') & 0x8000) ? 1.0f : ((GetKeyState('J') & 0x8000) ? -1.0f : 0.0f);

            if(verticalDir != 0 || horizontalDir != 0) {
                float rotation = 0;
                if (verticalDir < 0)
                    rotation = 1024.0f - horizontalDir * 512.0f;
                else if (verticalDir > 0)
                    rotation = 3072.0f + horizontalDir * 512.0f;
                else
					rotation = horizontalDir < 0 ? 2048.0f : 0.0f;

                WriteValue(tarf + 0x24, 3.5f);
				WriteValue(tarf + 0x28, rotation);
				WriteValue(tarf + 0x2C, rotation);
				WriteValue<char>(tarf + 0x1D1, 1);
			}
            else
                WriteValue(tarf + 0x24, 0.0f);

            if(std::abs(ReadValue<float>(tarf + 0x14) - ReadValue<float>(adol + 0x14)) > 350.0f
            || std::abs(ReadValue<float>(tarf + 0x18) - ReadValue<float>(adol + 0x18)) > 200.0f) {
                WriteValue(tarf + 0x14, ReadValue<float>(adol + 0x14)+25.0f);
                WriteValue(tarf + 0x18, ReadValue<float>(adol + 0x18)+25.0f);
            }
        }

		//float posX = ReadValue<float>(posXAddr, 2);
  //      sprintf_s(buffer, "PosX: %.f", posX);
  //      OutputDebugStringA(buffer);
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

#pragma comment(linker, "/export:SymInitialize=dbghelp_original.SymInitialize")
#pragma comment(linker, "/export:SymCleanup=dbghelp_original.SymCleanup")
#pragma comment(linker, "/export:SymFromAddr=dbghelp_original.SymFromAddr")
#pragma comment(linker, "/export:SymGetOptions=dbghelp_original.SymGetOptions")
#pragma comment(linker, "/export:SymSetOptions=dbghelp_original.SymSetOptions")
#pragma comment(linker, "/export:MiniDumpWriteDump=dbghelp_original.MiniDumpWriteDump")