#pragma once
#include "Game.h"
#include <unordered_map>

std::unordered_map<std::string, std::string> translations = {
    {"ƒjƒ…[ƒQ[ƒ€", "New Game"},
};

void __fastcall TextHook(void* dummy, void* arg1, int32_t arg2, int32_t arg3, int32_t arg4, char* arg5, char arg6, int32_t arg7, char arg8, int32_t arg9, double arg10) {
    //OutputDebugStringA(arg5);
	std::string str(arg5);
    if(translations.find(str) != translations.end()) {
        str = translations[str];
        strcpy_s(arg5, str.size() + 1, str.c_str());
    }

	//Replace Japanese wide alphabet characters with ASCII equivalents
    int wlen = MultiByteToWideChar(932 /* CP_SHIFTJIS */, 0, arg5, -1, NULL, 0);
    if (wlen > 0) {
        std::vector<wchar_t> wbuf(static_cast<size_t>(wlen));
        int got = MultiByteToWideChar(932, 0, arg5, -1, wbuf.data(), wlen);
        if (got > 0) {
            std::wstring wstr(wbuf.data());

            // Replace fullwidth ASCII characters (U+FF01 .. U+FF5E) with their ASCII equivalents
            for (wchar_t& wc : wstr) {
                if (wc >= 0xFF01 && wc <= 0xFF5E) {
                    wc = static_cast<wchar_t>(wc - 0xFEE0); // map to ASCII
                }
                else if (wc == 0x3000) {
                    wc = L' '; // fullwidth space to ASCII space
                }
            }

            // Convert back to Shift-JIS (CP 932)
            int newLen = WideCharToMultiByte(932, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
            if (newLen > 0) {
                std::vector<char> outbuf(static_cast<size_t>(newLen));
                int wrote = WideCharToMultiByte(932, 0, wstr.c_str(), -1, outbuf.data(), newLen, NULL, NULL);
                if (wrote > 0) {
                    // write bytes back into arg5 (match prior usage where buffer length isn't explicitly known)
                    strcpy_s(arg5, static_cast<size_t>(wrote), outbuf.data());
                }
            }
        }
    }

    unsigned char* c = (unsigned char*)arg5;
    while (*c != 0) {
        if (*c == 0x81 && *(c + 1) == 0x41) {
            *c = ',';
			*(c + 1) = ' ';
            c += 2;
        }
        //else if (*c == 0x82 && *(c + 1) >= 0x81) {
        //    *(c + off) = *(c + 1) - 0x20;
        //    *(c + 1) = 0;
        //    off--;
        //    c++;
        //}
        c++;
	}

    typedef void*** (__fastcall* Orig)(void*, void*, int32_t, int32_t, int32_t, char*, char, int32_t, char, int32_t, double);
    void* orig = (void*)(baseAddress + 0x47090);
    void*** ret = ((Orig)orig)(dummy, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
}

int32_t TextHook2(char arg1, char arg2, char arg3) {
    int32_t stack = 0;
    __asm {
        mov stack, ebp;
    }
	int32_t s = *(int32_t*)(stack + 0x3C);
	unsigned int check = *(unsigned int*)(s + 0x18);
	char* arg5 = check < 0x10 ? (char*)(s + 4) : *(char**)(s + 4);

    std::string str(arg5);
	OutputDebugStringA(str.c_str());
    if (translations.find(str) != translations.end()) {
        str = translations[str];
        strcpy_s(arg5, str.size() + 1, str.c_str());
    }

    unsigned char* c = (unsigned char*)arg5;
    while (*c != 0) {
        if (*c == 0x81 && *(c + 1) == 0x41) {
            *c = ',';
            *(c + 1) = ' ';
            c += 2;
        }
        //else if (*c == 0x82 && *(c + 1) >= 0x81) {
        //    *(c + off) = *(c + 1) - 0x20;
        //    *(c + 1) = 0;
        //    off--;
        //    c++;
        //}
        c++;
    }

    typedef int32_t(*Orig)(char, char, char);
    void* orig = (void*)(baseAddress + 0x2529D0);
    return *(int32_t*)(stack + 0x50) == -1 ? ((Orig)orig)(arg1, arg2, arg3) : *(int32_t*)(stack + 0x50);
}

class evalice : public Game
{
public:
    void main() {
        char bytes[4] = {0x90, 0x90, 0, 0};
        WriteBytes(baseAddress+0x477ED, bytes, 2);

        *(int*)(bytes) = (int)TextHook2 - 4 - 0x477F6 - baseAddress;
        WriteBytes(baseAddress + 0x477F6, bytes, 4);

		//Read Translations.txt into translations map
        std::ifstream file("Translations.txt");
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                translations[key] = value;
            }
        }
    }
};

