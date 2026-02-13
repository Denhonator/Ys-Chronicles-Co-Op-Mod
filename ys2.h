#pragma once
#include "Game.h"

class ys2 : public Game
{
public:
    void main() {
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
                if (curHP > adolLastHP && adolLastHP > 0)
                    WriteValue(tarf + 0xA0, ReadValue<short>(tarf + 0xA0) + curHP - adolLastHP);

                float verticalDir = (GetKeyState(UP) & 0x8000) ? 1.0f : ((GetKeyState(DOWN) & 0x8000) ? -1.0f : 0.0f);
                float horizontalDir = (GetKeyState(RIGHT) & 0x8000) ? 1.0f : ((GetKeyState(LEFT) & 0x8000) ? -1.0f : 0.0f);
                float speed = GetKeyState(WALK) & 0x8000 ? 1.5f : 3.5f;

                if ((verticalDir != 0 || horizontalDir != 0) && !ReadValue<int>(CanMove)) {
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
                float camCenterY = ReadValue<int>(cam + 4) + 192.0f;
                if (std::abs(ReadValue<float>(tarf + 0x14) - camCenterX) > maxDistanceX
                    || std::abs(ReadValue<float>(tarf + 0x18) - camCenterY) > maxDistanceY) {
                    WriteValue(tarf + 0x14, ReadValue<float>(adol + 0x14) + 25.0f);
                    WriteValue(tarf + 0x18, ReadValue<float>(adol + 0x18) - 25.0f);
                }
            }

            adolLastHP = ReadValue<short>(adol + 0xA0);

            //float posX = ReadValue<float>(posXAddr, 2);
            //sprintf_s(buffer, "PosX: %.f", posX);
            //OutputDebugStringA(buffer);
        }
    }
};

