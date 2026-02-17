#pragma once
#include "Game.h"

int feena = 0;
bool allowFeena = true;
int feenaQuest = false;
bool feenaSpawned = false;
const char* feenaSample = "\x1C\xAE\x4D\x00\x01\x00\x00\x00\x80\x05\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\xD3\x00\x00\x00\x00\x00\x00\x00\x40\x00\x00\x00\x00\x00\x00\x00\x0C\x05\x00\x00\x80\x05\x00\x00\x00\x00\x00\x00\x6A\xB7\x0C\x05\xE4\xC2\x80\x05\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x14\x59\xEB\x0A\x01\x00\x00\x00\x00\x00\x00\x00\x0C\x00\x00\x00\x00\x00\x00\x00\x4E\x00\x00\x00\x04\x00\x00\x00\x00\x00\x20\x41\x97\xFF\x1F\x41\x01\x00\x00\x00\xA0\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0F\x00\x00\x00\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0B\x00\x00\x00\x01\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xF0\xFF\xFF\xFF\xF8\xFF\xFF\xFF\x0F\x00\x00\x00\x07\x00\x00\x00\x01\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x11\x00\x00\x00\x11\x00\x00\x00\x07\x00\x00\x00\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x30\x05\x00\x00\x20\x05\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0C\x05\x00\x00\x80\x05\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0B\x00\x00\x00\xFF\xFF\xFF\xFF\x09\x00\x00\x00\x07\x00\x00\x00\xEC\xFD\xF7\x44\x00\x00\x00\x00\x00\x00\x00\x00\x11\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xC0\x40\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x80\x01\x00\x00\xC0\x00\x00\x00\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x00\x00\x00\x00\xD4\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
struct CamDummy {
    CamDummy* self;
    char dummyData[0x20];
    int32_t x = 0;
    int32_t y = 0;
};
CamDummy camTarget;

void __fastcall Ys1MovementHook(void* arg1) {
    int Running = baseAddress + 0x142628,
        AdolInput = baseAddress + 0x14BC18;

    int prevRunning = ReadValue<char>(Running);
    char prevMoving = ReadValue<char>(AdolInput + 0x31);
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
    else if (GetKeyState('P') & 0x8000) {
        typedef int32_t(*OrigFunc)();
        void* originalFunc = (void*)(baseAddress + 0xA58E0);
        ((OrigFunc)originalFunc)();
    }
    
    typedef void(__fastcall* OrigFunc)(void*);
    void* originalFunc = (void*)(baseAddress + 0x1B550);
    ((OrigFunc)originalFunc)(arg1);

    if ((int)arg1 != feena) {
        if (feenaSpawned) {
            camTarget.x = (ReadValue<int>((int)arg1 + 0x24) + ReadValue<int>(feena + 0x24)) / 2;
            camTarget.y = (ReadValue<int>((int)arg1 + 0x28) + ReadValue<int>(feena + 0x28)) / 2;
        }
        else {
            camTarget.x = ReadValue<int>((int)arg1 + 0x24);
            camTarget.y = ReadValue<int>((int)arg1 + 0x28);
        }
    }

    WriteValue(Running, prevRunning);
    WriteValue<char>(AdolInput + 0x31, prevMoving);
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

	WriteBytes(arg1 + 0x78, (int)arg1 == adol ? 
        "\x25\x00\x00\x00\x02\x00\x00\x00\x14\x00\x00\x00\xE1\xFF\xFF\xFF\x00\x00\x00\x00\x20\x20\x20\x20\x20\x20\x50\x31\x00\x00\x00\x00" :
        "\x15\x00\x00\x00\x02\x00\x00\x00\x14\x00\x00\x00\xE1\xFF\xFF\xFF\x00\x00\x00\x00\x20\x20\x20\x20\x20\x20\x50\x32\x00\x00\x00\x00", 32); //Enable player text


    WriteBytes(baseAddress + 0x1DE4F, (int)arg1 == adol ? "\xFC\x17" : "\x1C\x18", 2);  //Damage code
    char bytes[4];
    *(int*)bytes = (int)arg1;
    WriteBytes(baseAddress + 0x1D769, bytes, 4);    //Knockback code

    typedef void(__fastcall* OrigFunc)(uint32_t);
    void* originalFunc = (void*)(baseAddress + 0x1C1D0);
    ((OrigFunc)originalFunc)(arg1);

	if ((int)arg1 == adol) {
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

        if (ReadValue<int>(FeenaData) < baseAddress && ReadValue<int>(baseAddress+0x1313B0) > 0) {
            int FeenaRoom = baseAddress + 0x13169C;
			int FeenaActive = baseAddress + 0x131C44;
			int AdolRoom = baseAddress + 0x11E494;
			int prevRoom = ReadValue<int>(FeenaRoom);
			int prevActive = ReadValue<char>(FeenaActive);
			WriteValue<int>(FeenaRoom, ReadValue<int>(AdolRoom));
			WriteValue<char>(FeenaActive, 1);

            typedef int32_t(*AllocateCharacter)();
            AllocateCharacter funcPtr = reinterpret_cast<AllocateCharacter>((void*)(baseAddress + 0x8C870));
            bool result = funcPtr();
            feena = ReadValue<int>(FeenaData);

            if (result && feena >= baseAddress) {
				WriteBytes(feena, feenaSample, 0x480);
                int slot1 = ReadValue<int>(AdolData + 4);
                WriteValue<int>(FeenaData, slot1);
                WriteValue<int>(AdolData+4, feena);
                WriteValue(feena + 0x24, ReadValue<int>(adol + 0x24));
                WriteValue(feena + 0x28, ReadValue<int>(adol + 0x28));
            }
            else {
				OutputDebugStringA("Failed to spawn P2!");
            }
			WriteValue<int>(FeenaRoom, prevRoom);
			WriteValue<char>(FeenaActive, prevActive);
        }
    }
    else
        feenaSpawned = true;
}

void DamageRedirect(int16_t arg1, float arg2) {
    int ediVal = 0;
    __asm {
        mov ediVal, edi
    }

    typedef void(*OrigFunc)(int16_t, float);
    void* originalFunc = (void*)(baseAddress + 0xCA100);
    ((OrigFunc)originalFunc)(arg1, arg2);

    int AdolData = baseAddress + 0x20BA48;
    int adol = ReadValue<int>(AdolData);

    if (ediVal != adol)
        WriteBytes(baseAddress + 0x1CF01, "\x1C\x18", 2);

    else if (ediVal == adol)
        WriteBytes(baseAddress + 0x1CF01, "\xFC\x17", 2);
}

void TowerLoop() {
    int AdolData = baseAddress + 0x14061C;
    int adol = ReadValue<int>(AdolData);
    int lastAdolX = ReadValue<int>(adol + 0x24);

    typedef void(*OrigFunc)();
    void* originalFunc = (void*)(baseAddress + 0x98650);
    ((OrigFunc)originalFunc)();

    int xjump = ReadValue<int>(adol + 0x24) - lastAdolX;
    if (std::abs(xjump) > 200 && feenaSpawned) {
        int newx = ReadValue<int>(feena + 0x24) + xjump;
        WriteValue(feena + 0x24, newx);
        WriteValue(feena + 0x30, newx * (int)std::pow(2, 16));
    }

    camTarget.x = ReadValue<int>(adol + 0x24);
    camTarget.y = ReadValue<int>(adol + 0x28);
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
            AdolRoom = baseAddress + 0x11E494,
            FeenaRoom = baseAddress + 0x13169C,
            NextRoom = baseAddress + 0x131554,
            cam = baseAddress + 0x127DFC,
            CamOffset = baseAddress + 0x1DEC1C,
            pause = baseAddress + 0x131518,
            CanMove = baseAddress + 0xF906C,
            EquippedRing = baseAddress + 0x131680,
            FadeOut = baseAddress + 0x1313B0,
            FeenaMoveFuncPointer = baseAddress + 0xDB140,
            AdolMoveFuncPointer = baseAddress + 0xDAE30,
            DamageRedirectCall = baseAddress + 0x1C4D7,
            FeenaStatShowCode = baseAddress + 0x9F10D,
            FeenaHPBarCode = baseAddress + 0x56C46,
            FeenaHPBarCode2 = baseAddress + 0x5525E,
            KnockbackCode = baseAddress + 0x1D768,
            CamDummyCode = baseAddress + 0x8BE21,
            TowerLoopCode = baseAddress + 0x77D06,
            BatAttackCode = baseAddress + 0x2606C;

        //WriteBytes(FeenaRoomCheckCode, "\x90\x90", 2);
        WriteBytes(FeenaStatShowCode, "\x90\x90\x90\x90\x90\x90", 6);
        WriteBytes(FeenaHPBarCode, "\x90\x90", 2);
        WriteBytes(FeenaHPBarCode2, "\x90\x90", 2);
        WriteBytes(BatAttackCode, "\xEB", 1);
        WriteBytes(KnockbackCode, "\xBE\x01\x01\x01\x01\x90", 6);

        char bytes[4];
        *(int*)bytes = (int)Ys1MovementHook;
        WriteBytes(AdolMoveFuncPointer, bytes, 4);
        *(int*)bytes = (int)Ys1DamageHook;
        WriteBytes(AdolMoveFuncPointer + 0xC, bytes, 4);

		*(int*)bytes = (int)DamageRedirect - 5 - DamageRedirectCall;
        WriteBytes(DamageRedirectCall + 1, bytes, 4);

        *(int*)bytes = (int)TowerLoop - 5 - TowerLoopCode;
        WriteBytes(TowerLoopCode + 1, bytes, 4);

        *(int*)bytes = (int)&camTarget;
        WriteBytes(CamDummyCode, bytes, 4);
        camTarget.self = &camTarget;

        int adolLastHP = 0;
        int feenaRegenTimer = 0;

        while (true) {
            Sleep(10);

            int adol = ReadValue<int>(AdolData);

            if(adol < baseAddress)
                continue;

            int nextRoom = ReadValue<int>(NextRoom);
            //allowFeena = ReadValue<int>(NextRoom) != 36;

            if (nextRoom > 0)
                feenaSpawned = false;

            if (nextRoom == 0 && feenaSpawned) {
				WriteValue<int>(FeenaActive+0x20, 1);   //HP bar
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
                int canHeal = ReadValue<char>(AdolHP + 0x29C) && !ReadValue<char>(AdolHP + 0x298) ? 10 : 0;
                if (prevMaxHP < ReadValue<short>(FeenaHP + 4))
                    WriteValue(feena + 0x180, ReadValue<short>(FeenaHP + 4)); //If Feena's max HP increased, heal her to full
                if (curHP - adolLastHP > canHeal && adolLastHP > 0)
                    WriteValue(feena + 0x180, ReadValue<short>(feena + 0x180) + curHP - adolLastHP);
                //WriteValue(FeenaHP, ReadValue<short>(feena + 0x180)); //Sync visual HP with actual HP

                if (ReadValue<int>(feena + 0x18) == 0 && ReadValue<int>(feena + 0x20) == 0 && ReadValue<int>(FeenaHP) > 0
                     && ReadValue<int>(FeenaHP) < ReadValue<int>(FeenaHP+4) && !ReadValue<char>(pause+0x34)) {
                    
                    canHeal += ReadValue<int>(EquippedRing) == 18 ? 5 : 0;

                    feenaRegenTimer += canHeal;
                    if (feenaRegenTimer >= 315 - (ReadValue<int>(FeenaHP+4) * 85) / 100) {
                        WriteValue<short>(FeenaHP, ReadValue<short>(FeenaHP) + 1);
                        feenaRegenTimer = 0;
                    }
                }
                else
					feenaRegenTimer = 0;

                WriteValue(feena + 0x180, ReadValue<short>(FeenaHP)); //Sync visual HP with actual HP
                if (ReadValue<short>(feena + 0x180) <= 0)
                    WriteValue<char>(feena + 0x19C, 1); //If Feena is dead, death animation
                if (ReadValue<char>(pause + 0x1F0)) {
                    WriteValue<int>(FeenaHP, 0);
                    WriteValue<int>(AdolHP, 0);
                    WriteValue<char>(feena + 0x19C, 1);
                    WriteValue<char>(adol + 0x19C, 1);
                }

                //16:9 mode: 240, 136
                int camCenterX = ReadValue<int>(cam) + ReadValue<int>(CamOffset + 0xC) / 2;
                int camCenterY = ReadValue<int>(cam + 4) + ReadValue<int>(CamOffset + 0x10) / 2;
                if (!ReadValue<char>(CanMove) || (ReadValue<int>(AdolRoom) == 36 && ReadValue<int>(FeenaActive)) 
                    || std::abs(ReadValue<int>(feena + 0x24) - camCenterX) > maxDistanceX
                    || std::abs(ReadValue<int>(feena + 0x28) - camCenterY) > maxDistanceY) {
                    WriteValue(feena + 0x24, ReadValue<int>(adol + 0x24));
                    WriteValue(feena + 0x28, ReadValue<int>(adol + 0x28));
                }
            }
            //else {
            //    camTarget.x = ReadValue<int>(adol + 0x24);
            //    camTarget.y = ReadValue<int>(adol + 0x28);
            //}

            adolLastHP = ReadValue<short>(adol + 0x180);
        }
    }
};

