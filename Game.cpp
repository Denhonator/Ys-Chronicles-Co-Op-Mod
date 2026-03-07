#include "pch.h"
#include "Game.h"

// Explicit template instantiations
// These are required to avoid linker errors for templates used in multiple translation units.
template int ReadValue<int>(int offsets[], int count);
template int ReadValue<int>(int offset);
template short ReadValue<short>(int offsets[], int count);
template short ReadValue<short>(int offset);
template char ReadValue<char>(int offsets[], int count);
template char ReadValue<char>(int offset);
template unsigned char ReadValue<unsigned char>(int offsets[], int count);
template unsigned char ReadValue<unsigned char>(int offset);
template float ReadValue<float>(int offsets[], int count);
template float ReadValue<float>(int offset);

template void WriteValue<float>(int offsets[], int count, float value);
template void WriteValue<float>(int offset, float value);
template void WriteValue<int>(int offsets[], int count, int value);
template void WriteValue<int>(int offset, int value);
template void WriteValue<short>(int offsets[], int count, short value);
template void WriteValue<short>(int offset, short value);
template void WriteValue<char>(int offsets[], int count, char value);
template void WriteValue<char>(int offset, char value);

int baseAddress = 0;
char UP = 'I', DOWN = 'K', LEFT = 'J', RIGHT = 'L', WALK = 'U', ACTION = 'H', SAVE = 'P', SPEEDUP = 'M';
float maxDistanceX = 250.0f;
float maxDistanceY = 400.0f;
int minQuicksave = 110;
int maxQuicksave = 120;

int FindPointer(int offsets[], int count)
{
    int address = offsets[0];
    for (int i = 1; i < count; i++)
    {
        if (address < baseAddress || *(int*)address < baseAddress)
            return 0;
        address = *(int*)address + offsets[i];
    }
    return address;
}

template<typename T> void WriteValue(int offsets[], int count, T value) {
    int address = count > 1 ? FindPointer(offsets, count) : offsets[0];
    if (address >= baseAddress)
        *(T*)address = value;
}

template<typename T> T ReadValue(int offsets[], int count) {
    int address = count > 1 ? FindPointer(offsets, count) : offsets[0];
    return address >= baseAddress ? *(T*)address : 0;
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