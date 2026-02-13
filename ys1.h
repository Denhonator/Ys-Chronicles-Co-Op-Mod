#pragma once
#include "Game.h"

int feena = 0;
bool allowFeena = true;
int feenaQuest = false;
bool feenaSpawned = false;
const char* feenaSample = "\x1C\xAE\x4D\x00\x01\x00\x00\x00\x80\x05\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\xD3\x00\x00\x00\x00\x00\x00\x00\x40\x00\x00\x00\x00\x00\x00\x00\x0C\x05\x00\x00\x80\x05\x00\x00\x00\x00\x00\x00\x6A\xB7\x0C\x05\xE4\xC2\x80\x05\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x14\x59\xEB\x0A\x01\x00\x00\x00\x00\x00\x00\x00\x0C\x00\x00\x00\x00\x00\x00\x00\x4E\x00\x00\x00\x04\x00\x00\x00\x00\x00\x20\x41\x97\xFF\x1F\x41\x01\x00\x00\x00\xA0\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0F\x00\x00\x00\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0B\x00\x00\x00\x01\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xF0\xFF\xFF\xFF\xF8\xFF\xFF\xFF\x0F\x00\x00\x00\x07\x00\x00\x00\x01\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x11\x00\x00\x00\x11\x00\x00\x00\x07\x00\x00\x00\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x30\x05\x00\x00\x20\x05\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0C\x05\x00\x00\x80\x05\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0B\x00\x00\x00\xFF\xFF\xFF\xFF\x09\x00\x00\x00\x07\x00\x00\x00\xEC\xFD\xF7\x44\x00\x00\x00\x00\x00\x00\x00\x00\x11\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xC0\x40\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x80\x01\x00\x00\xC0\x00\x00\x00\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x00\x00\x00\x00\xD4\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

void __fastcall Ys1MovementHook(void* arg1) {
    int Running = baseAddress + 0x142628,
        AdolInput = baseAddress + 0x14BC18;

    int prevRunning = ReadValue<char>(Running);
    int prevMoving = ReadValue<char>(AdolInput + 0x31);
    int prevDirection = ReadValue<char>(AdolInput + 0x40);
    int prevRotation = ReadValue<char>(AdolInput + 0x38);
    int prevHorizontal = ReadValue<char>(AdolInput);

    if ((int)arg1 == feena) {
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
    int AdolData = baseAddress + 0x20BA48;
    int adol = ReadValue<int>(AdolData);
    int NextRoom = baseAddress + 0x131554;

    if (adol < baseAddress || ReadValue<int>(NextRoom) > 0) {
        return;
    }

    if(ReadValue<int>(baseAddress + 0x14061C) != adol)
		WriteValue(baseAddress + 0x14061C, adol);

    if ((int)arg1 != adol)
        WriteBytes(baseAddress + 0x1CF01, "\x1C\x18", 2);

    typedef void(__fastcall* OrigFunc)(uint32_t);
    void* originalFunc = (void*)(baseAddress + 0x1C1D0);
    ((OrigFunc)originalFunc)(arg1);

    if ((int)arg1 != adol)
        WriteBytes(baseAddress + 0x1CF01, "\xFC\x17", 2);

	else {
        int FeenaData = AdolData + 4;
        feena = adol + 0x480;
        while (ReadValue<int>(FeenaData) >= baseAddress) {
            if (ReadValue<int>(ReadValue<int>(FeenaData)) == 0x4DAE1C) {
				feena =  ReadValue<int>(FeenaData);
                break;
            }
            FeenaData += 4;
            feena += 0x480;
        }

        if (ReadValue<int>(FeenaData) < baseAddress) {
            typedef int32_t(*AllocateCharacter)();
            AllocateCharacter funcPtr = reinterpret_cast<AllocateCharacter>((void*)(baseAddress + 0x8C870));
            bool result = funcPtr();
            feena = ReadValue<int>(FeenaData);

            if (result && feena >= baseAddress) {
				WriteBytes(feena, feenaSample, 0x480);
                int cam = baseAddress + 0x127DFC;
                WriteValue<int>(feena + 0x24, ReadValue<int>(adol + 0x24) + (ReadValue<int>(cam) + 296 - ReadValue<int>(adol + 0x24)/10));
                WriteValue<int>(feena + 0x28, ReadValue<int>(adol + 0x28) + (ReadValue<int>(cam + 4) + 192 - ReadValue<int>(adol + 0x28)/10));
            }
        }
    }
}

class ys1 : public Game
{
public:
    void main() {
        int FeenaActive = baseAddress + 0x131C44,
            AdolData = baseAddress + 0x14061C,
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
        char bytes[4];
        *(int*)bytes = (int)Ys1MovementHook;
        WriteBytes(AdolMoveFuncPointer, bytes, 4);
        *(int*)bytes = (int)Ys1DamageHook;
        WriteBytes(AdolMoveFuncPointer + 0xC, bytes, 4);

        int adolLastHP = 0;

        while (true) {
            Sleep(10);

            int adol = ReadValue<int>(AdolData);

            if(adol < baseAddress)
                continue;

            int nextRoom = ReadValue<int>(NextRoom);
            //allowFeena = ReadValue<int>(NextRoom) != 36;

            if (nextRoom > 1 && adol > baseAddress) {
                WriteValue(FeenaRoom, nextRoom); //Keep Feena in the same room as Adol
                WriteValue<char>(FeenaActive, allowFeena ? 1 : 0); //Keep Feena active
            }

			WriteValue<int>(FeenaActive, nextRoom == 0 ? 1 : 0);

            if (nextRoom == 0 && ReadValue<int>(feena) == 0x4DAE1C) {
                //WriteValue(feena, 0x4DAE1C);
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

