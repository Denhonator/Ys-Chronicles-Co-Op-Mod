// dllmain.cpp : Entry point for the DLL application.
#include "pch.h"

#include <Windows.h>
#include <WinBase.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

#include "Game.h"
#include "ys1.h"
#include "ys2.h"

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

    int game = std::strcmp(filename, "ys1plus.exe") == 0 ? 1 : std::strcmp(filename, "ys2plus.exe") == 0 ? 2 : 0;
    if (game == 0) {
        OutputDebugStringA("Not ys1plus.exe or ys2plus.exe, exiting thread");
        return 0;
    }

	std::unique_ptr<Game> g(game == 1 ? static_cast<Game*>(new ys1()) : static_cast<Game*>(new ys2()));

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

    g->main();
    
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
    if (dwReason == DLL_PROCESS_ATTACH) {
        char path[MAX_PATH];
        GetSystemDirectoryA(path, MAX_PATH);
        strcat_s(path, "\\dbghelp.dll");
        //hOriginal = LoadLibraryA(path);

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