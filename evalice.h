#pragma once
#include "Game.h"

void __fastcall TextHook(void* dummy, void* arg1, int32_t arg2, int32_t arg3, int32_t arg4, char* arg5, char arg6, int32_t arg7, char arg8, int32_t arg9, double arg10) {
    OutputDebugStringA(arg5);

    unsigned char* c = (unsigned char*)arg5;
    while (*c != 0) {
        if (*c == 0x81 && *(c + 1) == 0x41) {
            *c = ',';
			*(c + 1) = ' ';
            c += 2;
        }
        c++;
	}

    typedef void*** (__fastcall* Orig)(void*, void*, int32_t, int32_t, int32_t, char*, char, int32_t, char, int32_t, double);
    void* orig = (void*)(baseAddress + 0x47090);
    void*** ret = ((Orig)orig)(dummy, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
}

class evalice :
    public Game
{
public:
    void main() {
        char bytes[4];
        *(int*)bytes = (int)TextHook-4-0x47BBB-baseAddress;
        WriteBytes(baseAddress+0x47BBB, bytes, 4);
    }
};

