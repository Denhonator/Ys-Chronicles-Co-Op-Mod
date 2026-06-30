#pragma once

extern int baseAddress;

extern int FindPointer(int offsets[], int count);
template<typename T> extern T ReadValue(int offsets[], int count);
template<typename T> extern void WriteValue(int offsets[], int count, T value);
template<typename T> extern T ReadValue(int offset);
template<typename T> extern void WriteValue(int offset, T value);
extern void WriteBytes(int offset, const char* bytes, size_t size);

class Game
{
public:
	virtual void main() {};
};

