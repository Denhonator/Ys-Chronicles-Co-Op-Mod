// dllmain.cpp : Entry point for the DLL application.
#include "pch.h"

#include <Windows.h>
#include <WinBase.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

#include "evalice.h"
#include "Game.h"

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

    int game = std::strcmp(filename, "EvaliceSaga.exe") == 0 ? 1 : 0;
    if (game == 0) {
        OutputDebugStringA("Not EvaliceSaga.exe, exiting thread");
        return 0;
    }

	std::unique_ptr<Game> g(static_cast<Game*>(new evalice()));

    g->main();
    
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
    if (dwReason == DLL_PROCESS_ATTACH) {
        char path[MAX_PATH];
        GetSystemDirectoryA(path, MAX_PATH);
        strcat_s(path, "\\version.dll");
        //hOriginal = LoadLibraryA(path);

        CreateThread(nullptr, 0, HookThread, nullptr, 0, nullptr);
    }
    return TRUE;
}

#pragma comment(linker, "/export:GetFileVersionInfoA=C:\\Windows\\SysWOW64\\version.GetFileVersionInfoA")
#pragma comment(linker, "/export:GetFileVersionInfoByHandle=C:\\Windows\\SysWOW64\\version.GetFileVersionInfoByHandle")
#pragma comment(linker, "/export:GetFileVersionInfoExA=C:\\Windows\\SysWOW64\\version.GetFileVersionInfoExA")
#pragma comment(linker, "/export:GetFileVersionInfoExW=C:\\Windows\\SysWOW64\\version.GetFileVersionInfoExW")
#pragma comment(linker, "/export:GetFileVersionInfoSizeA=C:\\Windows\\SysWOW64\\version.GetFileVersionInfoSizeA")
#pragma comment(linker, "/export:GetFileVersionInfoSizeExA=C:\\Windows\\SysWOW64\\version.GetFileVersionInfoSizeExA")
#pragma comment(linker, "/export:GetFileVersionInfoSizeExW=C:\\Windows\\SysWOW64\\version.GetFileVersionInfoSizeExW")
#pragma comment(linker, "/export:GetFileVersionInfoSizeW=C:\\Windows\\SysWOW64\\version.GetFileVersionInfoSizeW")
#pragma comment(linker, "/export:GetFileVersionInfoW=C:\\Windows\\SysWOW64\\version.GetFileVersionInfoW")
#pragma comment(linker, "/export:VerFindFileA=C:\\Windows\\SysWOW64\\version.VerFindFileA")
#pragma comment(linker, "/export:VerFindFileW=C:\\Windows\\SysWOW64\\version.VerFindFileW")
#pragma comment(linker, "/export:VerInstallFileA=C:\\Windows\\SysWOW64\\version.VerInstallFileA")
#pragma comment(linker, "/export:VerInstallFileW=C:\\Windows\\SysWOW64\\version.VerInstallFileW")
#pragma comment(linker, "/export:VerLanguageNameA=C:\\Windows\\SysWOW64\\version.VerLanguageNameA")
#pragma comment(linker, "/export:VerLanguageNameW=C:\\Windows\\SysWOW64\\version.VerLanguageNameW")
#pragma comment(linker, "/export:VerQueryValueA=C:\\Windows\\SysWOW64\\version.VerQueryValueA")
#pragma comment(linker, "/export:VerQueryValueW=C:\\Windows\\SysWOW64\\version.VerQueryValueW")