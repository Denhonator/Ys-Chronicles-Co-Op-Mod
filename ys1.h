#pragma once
#include "Game.h"

int feena = 0;

void __fastcall Ys1MovementHook(void* arg1) {
    int ecxValue = 0;
    __asm {
        mov ecxValue, esi
    }

    int Running = baseAddress + 0x142628,
        AdolInput = baseAddress + 0x14BC18;

    int prevRunning = ReadValue<char>(Running);
    int prevMoving = ReadValue<char>(AdolInput + 0x31);
    int prevDirection = ReadValue<char>(AdolInput + 0x40);
    int prevRotation = ReadValue<char>(AdolInput + 0x38);
    int prevHorizontal = ReadValue<char>(AdolInput);

    if (ecxValue == feena) {
        int verticalDir = (GetKeyState(UP) & 0x8000) ? 1 : ((GetKeyState(DOWN) & 0x8000) ? -1 : 0);
        int horizontalDir = (GetKeyState(RIGHT) & 0x8000) ? 1 : ((GetKeyState(LEFT) & 0x8000) ? -1 : 0);
        int speed = GetKeyState(WALK) & 0x8000 ? 640 : 1152;

        WriteValue(Running, (verticalDir != 0 || horizontalDir != 0) && speed > 640 ? 1 : 0);
        WriteValue(AdolInput + 0x31, (verticalDir != 0 || horizontalDir != 0) ? 1 : 0);
        WriteValue(AdolInput, horizontalDir > 0 ? 2 : horizontalDir < 0 ? 1 : 0);
        if ((verticalDir != 0 || horizontalDir != 0)) {
            WriteValue(AdolInput + 0x40, horizontalDir > 0 ? 6 : horizontalDir < 0 ? 5 : verticalDir < 0 ? 4 : verticalDir > 0 ? 3 : 0);

            int rotation = 0;
            if (verticalDir > 0)
                rotation = 64 - horizontalDir * 32;
            else if (verticalDir < 0)
                rotation = 192 + horizontalDir * 32;
            else
                rotation = horizontalDir < 0 ? 128 : 0;

            WriteValue(AdolInput + 0x38, rotation);
            WriteValue(AdolInput + 0x28, ReadValue<int>(AdolInput + 0x28) + 16);
        }
    }

    typedef void(__fastcall* OrigFunc)(void*);
    void* originalFunc = (void*)(baseAddress + 0x1B550);
    ((OrigFunc)originalFunc)(arg1);

    WriteValue(Running, prevRunning);
    WriteValue(AdolInput + 0x31, prevMoving);
    WriteValue(AdolInput + 0x40, prevDirection);
    WriteValue(AdolInput + 0x38, prevRotation);
    WriteValue(AdolInput, prevHorizontal);
}

void __fastcall Ys1DamageHook(uint32_t arg1) {
    if ((int)arg1 == feena)
        WriteBytes(baseAddress + 0x1CF01, "\x1C\x18", 2);

    typedef void(__fastcall* OrigFunc)(uint32_t);
    void* originalFunc = (void*)(baseAddress + 0x1C1D0);
    ((OrigFunc)originalFunc)(arg1);

    if ((int)arg1 == feena)
        WriteBytes(baseAddress + 0x1CF01, "\xFC\x17", 2);
}

class ys1 : public Game
{
public:
    void main() {
        int FeenaActive = baseAddress + 0x131C44,
            AdolData = baseAddress + 0x14061C,
            FeenaData = baseAddress + 0x14061C,
            AdolHP = baseAddress + 0x1317FC,
            FeenaHP = AdolHP + 0x20,
            FeenaRoomCheckCode = baseAddress + 0x351A2,
            CanMove = baseAddress + 0x135884,
            AdolRoom = baseAddress + 0x11E494,
            FeenaRoom = baseAddress + 0x13169C,
            NextRoom = baseAddress + 0x131554,
            cam = baseAddress + 0x127DFC,
            FeenaMoveFuncPointer = baseAddress + 0xDB140,
            AdolMoveFuncPointer = baseAddress + 0xDAE30;

        WriteBytes(FeenaRoomCheckCode, "\x90\x90", 2);
        //int origFeenaMoveFunc = ReadValue<int>(FeenaMoveFuncPointer);
        char bytes[4];
        *(int*)bytes = (int)Ys1MovementHook;
        WriteBytes(AdolMoveFuncPointer, bytes, 4);
        *(int*)bytes = (int)Ys1DamageHook;
        WriteBytes(AdolMoveFuncPointer + 0xC, bytes, 4);

        int adolLastHP = 0;
        bool allowFeena = true;

        while (true) {
            Sleep(10);

            int adol = ReadValue<int>(AdolData);
            feena = adol + 0x480;

            while (feena >= baseAddress && ReadValue<char>(FeenaActive)) {
                if (ReadValue<int>(feena + 0x160) == 2) {
                    break;
                }
                feena += 0x480;
            }

            int nextRoom = ReadValue<int>(NextRoom);
            allowFeena = ReadValue<int>(NextRoom) != 36;
            int feenaQuest = false;
            if (nextRoom > 1 && adol > baseAddress) {
                WriteValue(FeenaRoom, nextRoom); //Keep Feena in the same room as Adol
                WriteValue<char>(FeenaActive, allowFeena ? 1 : 0); //Keep Feena active
            }

            if (ReadValue<int>(feena + 0x160) == 2 && !feenaQuest && ReadValue<char>(FeenaActive)) {
                WriteValue(feena, 0x4DAE1C);
                WriteValue<char>(feena + 0x250, ReadValue<char>(adol + 0x250));
                WriteValue<char>(feena + 0x1CC, ReadValue<char>(adol + 0x1CC)); //Disable Feena specific damage
                //WriteValue<char>(feena + 0x160, ReadValue<char>(adol + 0x160));
                WriteValue(feena + 0x4C, ReadValue<int>(adol + 0x4C));    //Character sprite
                float prevMaxHP = ReadValue<short>(FeenaHP + 4);
                WriteValue(FeenaHP + 4, ReadValue<short>(AdolHP + 4));        //Copy Feena's HP from Adol's HP
                WriteValue(FeenaHP + 8, ReadValue<short>(adol + 0x188));      //Copy Feena's STR from Adol's STR
                WriteValue(FeenaHP + 12, ReadValue<short>(adol + 0x18C));     //Copy Feena's DEF from Adol's DEF
                WriteValue(feena + 0x184, ReadValue<short>(FeenaHP + 4));
                WriteValue(feena + 0x188, ReadValue<short>(FeenaHP + 8));
                WriteValue(feena + 0x18C, ReadValue<short>(FeenaHP + 0xC));
                short curHP = ReadValue<short>(adol + 0x180);
                if (prevMaxHP < ReadValue<short>(FeenaHP + 4))
                    WriteValue(feena + 0x180, ReadValue<short>(FeenaHP + 4)); //If Feena's max HP increased, heal her to full
                if (curHP - adolLastHP > 5 && adolLastHP > 0)
                    WriteValue(feena + 0x180, ReadValue<short>(feena + 0x180) + curHP - adolLastHP);
                //WriteValue(FeenaHP, ReadValue<short>(feena + 0x180)); //Sync visual HP with actual HP
                WriteValue(feena + 0x180, ReadValue<short>(FeenaHP)); //Sync visual HP with actual HP
                if (ReadValue<short>(feena + 0x180) <= 0)
                    WriteValue<char>(feena + 0x19C, 1); //If Feena is dead, death animation

                //        int verticalDir = (GetKeyState(UP) & 0x8000) ? 1 : ((GetKeyState(DOWN) & 0x8000) ? -1 : 0);
                //        int horizontalDir = (GetKeyState(RIGHT) & 0x8000) ? 1 : ((GetKeyState(LEFT) & 0x8000) ? -1 : 0);
                //        int speed = GetKeyState(WALK) & 0x8000 ? 640 : 1152;

                //        if ((verticalDir != 0 || horizontalDir != 0)) {
                //            int rotation = 0;
                //            if (verticalDir > 0)
                //                rotation = 64 - horizontalDir * 32;
                //            else if (verticalDir < 0)
                //                rotation = 192 + horizontalDir * 32;
                //            else
                //                rotation = horizontalDir < 0 ? 128 : 0;

                //            WriteValue(feena + 0x14, rotation);
                //            WriteValue(feena + 0x18, speed);
                //        }
                //        else
                            //WriteValue(feena + 0x18, 0);


                int camCenterX = ReadValue<int>(cam) + 296;
                int camCenterY = ReadValue<int>(cam + 4) + 192;
                if (std::abs(ReadValue<int>(feena + 0x24) - camCenterX) > maxDistanceX
                    || std::abs(ReadValue<int>(feena + 0x28) - camCenterY) > maxDistanceY) {
                    WriteValue(feena + 0x24, ReadValue<int>(adol + 0x24) + 25);
                    WriteValue(feena + 0x28, ReadValue<int>(adol + 0x28) - 25);
                }
            }

            adolLastHP = ReadValue<short>(adol + 0x180);
        }
    }
};

