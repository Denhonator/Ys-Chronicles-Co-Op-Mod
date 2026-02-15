#pragma once
#include "Game.h"

int tarf = 0;
char magicInput[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
bool prevMagic = false;
float magicCharge = 0;
char magicChargeAddr[4];
char origMagicChargeBytes[4];
float regenTimer1 = 0;
float regenTimer2 = 0;

int32_t __fastcall AdolMoveHook(void* arg1) {
    int Input = baseAddress + 0x25E398;

    //typedef void* (__fastcall* InputFunc)(void*);
    //void* inputfunc = (void*)(baseAddress + 0x7FBB0);
    //((InputFunc)inputfunc)((void*)Input);

  //  if ((int)arg1 == tarf && false) {
  //      float verticalDir = (GetKeyState(UP) & 0x8000) ? 1.0f : ((GetKeyState(DOWN) & 0x8000) ? -1.0f : 0.0f);
  //      float horizontalDir = (GetKeyState(RIGHT) & 0x8000) ? 1.0f : ((GetKeyState(LEFT) & 0x8000) ? -1.0f : 0.0f);
  //      bool walk = !(GetKeyState(WALK) & 0x8000);
		//bool magic = GetKeyState(ACTION) & 0x8000;

  //      WriteValue<char>(Input + 0x40, walk ? 1 : 0);
		//WriteValue<char>(Input + 0x44, magic ? 1 : 0);
		//WriteValue<char>(Input + 0x3C, magic ? 1 : 0);

  //      if (verticalDir > 0)
  //          WriteValue<char>(Input + 0x28, 1);
		//else if (verticalDir < 0)
		//	WriteValue<char>(Input + 0x34, 1);
  //      if (horizontalDir > 0)
  //          WriteValue<char>(Input + 0x30, 1);
  //      else if (horizontalDir < 0)
  //          WriteValue<char>(Input + 0x2C, 1);
  //  }

    if ((int)arg1 == tarf) {
        int CanRest = baseAddress + 0x25D2BC;
		int MPCharge = baseAddress + 0x25D3AC;
		bool isDown = GetKeyState(ACTION) & 0x8000;
		magicInput[9] = isDown && !prevMagic;
		magicInput[10] = isDown ? 1 : 0;

        WriteBytes(baseAddress + 0x1CBFC + 4, magicChargeAddr, 4);
        WriteBytes(baseAddress + 0x1CC0B + 4, magicChargeAddr, 4);
        WriteBytes(baseAddress + 0x1CC15 + 2, magicChargeAddr, 4);
        WriteBytes(baseAddress + 0x1CC38 + 4, magicChargeAddr, 4);
        WriteBytes(baseAddress + 0x1CC51 + 2, magicChargeAddr, 4);
        WriteBytes(baseAddress + 0x1CC6C + 2, magicChargeAddr, 4);
        WriteBytes(baseAddress + 0x1B9B6 + 4, magicChargeAddr, 4);
        WriteBytes(baseAddress + 0x1C513 + 4, magicChargeAddr, 4);

        typedef void*** (__fastcall* FireBall)(void*, void*, void*);
        void* fireballFunc = (void*)(baseAddress + 0x1CBC0);
        void*** ret = ((FireBall)fireballFunc)(arg1, arg1, magicInput);

        WriteBytes(baseAddress + 0x1CBFC + 4, origMagicChargeBytes, 4);
        WriteBytes(baseAddress + 0x1CC0B + 4, origMagicChargeBytes, 4);
        WriteBytes(baseAddress + 0x1CC15 + 2, origMagicChargeBytes, 4);
        WriteBytes(baseAddress + 0x1CC38 + 4, origMagicChargeBytes, 4);
        WriteBytes(baseAddress + 0x1CC51 + 2, origMagicChargeBytes, 4);
        WriteBytes(baseAddress + 0x1CC6C + 2, origMagicChargeBytes, 4);
        WriteBytes(baseAddress + 0x1B9B6 + 4, origMagicChargeBytes, 4);
        WriteBytes(baseAddress + 0x1C513 + 4, origMagicChargeBytes, 4);

		prevMagic = isDown;

        if (ReadValue<char>(CanRest) && ReadValue<float>(tarf + 0x24) == 0 && ReadValue<float>(tarf + 0x4C) == 0 && ReadValue<int>(tarf + 0xA0) < ReadValue<int>(tarf + 0xA4)) {
			float fps = ReadValue<int>(baseAddress + 0x25E34C);
            regenTimer1 += 32.5f/fps;
            if (regenTimer1 >= 150.0f) {
				regenTimer2 += 32.5f / fps;
                if (regenTimer2 >= 25.0f) {
                    regenTimer2 = 0;
					WriteValue<short>(tarf + 0xA0, ReadValue<short>(tarf + 0xA0) + 1);
                }
            }
        }
        else {
            regenTimer1 = 0;
			regenTimer2 = 0;
        }
    }

    typedef int32_t(__fastcall* OrigFunc)(void*);
    void* originalFunc = (void*)(baseAddress + 0x19E60);
    int32_t ret = ((OrigFunc)originalFunc)(arg1);

	return ret;
}

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
        int NextRoom = baseAddress + 0x25e38c;
        int cam = baseAddress + 0x25D6D0;
        int BlackOrbStatus = baseAddress + 0x25C8A6;
        int AdolMoveFuncPtr = baseAddress + 0x10B448;
		int MagicCharge = baseAddress + 0x25CE14;
		int TarfMagic = baseAddress + 0x25D380;

        WriteBytes(ResetSpeedCode, "\x90\x90\x90\x90\x90\x90\x90", 7); //Nop out speed reset
        WriteBytes(ResetAnimCode, "\x90\x90\x90\x90\x90\x90\x90", 7);
        WriteBytes(TarfRoomCheckCode, "\x90\x90\xB3\x00", 4);

        char bytes[4];
        *(int*)bytes = (int)AdolMoveHook;
		WriteBytes(AdolMoveFuncPtr, bytes, 4);

		*(int*)magicChargeAddr = (int)(&magicCharge);
		*(int*)origMagicChargeBytes = MagicCharge;

        int adolLastHP = ReadValue<short>(AdolData + 0xA0);
        int adolLastMP = ReadValue<short>(AdolData + 0xA8);

        while (true) {
            Sleep(10);

            int adol = ReadValue<int>(AdolData);
			int nextRoom = ReadValue<int>(NextRoom);

            if (ReadValue<int>(AdolRoom) <= 1 || adol < baseAddress)
                continue;

			bool foundTarf = false;
            TarfScan[0] = AdolData + 4;
            while (ReadValue<int>(TarfScan[0]) >= baseAddress) {
                if (ReadValue<int>(TarfScan, 2) == 0x2C || ReadValue<int>(TarfScan, 2) == 2 || ReadValue<int>(TarfScan, 2) == 1) {
                    TarfData = TarfScan[0];
                    tarf = ReadValue<int>(TarfData);
					foundTarf = true;
                    break;
                }
                TarfScan[0] += 4;
            }

            bool allowTarf = ReadValue<short>(BlackOrbStatus) == 0x0100 || ReadValue<int>(AdolRoom) != 98;
            WriteValue(adol + 0x24, 0.0f); //Reset Adol's speed to prevent sliding
            WriteValue<char>(TarfToggle, allowTarf ? 44 : 0); //Keep Tarf active

            if (foundTarf) {
                WriteValue(tarf, 0x50B448);
                //WriteValue(tarf + 0x1D8, 1);  //Character type
                WriteValue(tarf + 0x1DC, 2);    //Character sprite
                float prevMaxHP = ReadValue<short>(TarfStats + 4);
                WriteValue(TarfStats + 4, ReadValue<short>(adol + 0xA4)); //Copy Tarf's HP from Adol's HP
                WriteValue(TarfStats + 6, ReadValue<short>(adol + 0xB0)); //Copy Tarf's STR from Adol's STR
                WriteValue(TarfStats + 8, ReadValue<short>(adol + 0xB4)); //Copy Tarf's DEF from Adol's DEF
                if (ReadValue<short>(tarf + 0xAC) < ReadValue<short>(adol + 0xAC) && ReadValue<short>(tarf + 0x234) == 18) {
					int readFrom = ReadValue<int>(TarfMagic + 0xC) == ReadValue<int>(adol + 0xAC) ? TarfMagic : adol + 0xA0;
                    WriteValue(tarf + 0xA8, ReadValue<short>(readFrom + 8)); //Copy MP
                    WriteValue(tarf + 0xAC, ReadValue<short>(readFrom + 12)); //Copy MP
                }
                WriteValue(tarf + 0x234, ReadValue<short>(adol + 0x234)); //Copy spell
                short curHP = ReadValue<short>(adol + 0xA0);
                if (prevMaxHP < ReadValue<short>(TarfStats + 4))
                    WriteValue(tarf + 0xA0, ReadValue<short>(TarfStats + 4)); //If Tarf's max HP increased, heal him to full
                if (curHP - adolLastHP > 2 && adolLastHP > 0)
                    WriteValue(tarf + 0xA0, ReadValue<short>(tarf + 0xA0) + curHP - adolLastHP);
                if (ReadValue<short>(adol+0xA8) > adolLastMP && ReadValue<short>(adol + 0xA8) == ReadValue<short>(adol + 0xAC))
					WriteValue(tarf + 0xA8, ReadValue<int>(tarf + 0xAC));

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
            adolLastMP = ReadValue<short>(adol + 0xA8);

            //float posX = ReadValue<float>(posXAddr, 2);
            //sprintf_s(buffer, "PosX: %.f", posX);
            //OutputDebugStringA(buffer);
        }
    }
};

