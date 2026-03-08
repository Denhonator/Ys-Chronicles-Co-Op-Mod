#pragma once
#include "Game.h"

int tarf = 0;
int TarfData = baseAddress + 0x1453D8;
char magicInput[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
bool prevMagic = false;
float magicCharge = 0;
char magicChargeAddr[4];
char origMagicChargeBytes[4];
float regenTimer1 = 0;
float regenTimer2 = 0;
struct CamDummy2 {
    CamDummy2* self;
    char dummyData[0x60];
    int32_t x = 0;
    int32_t y = 0;
};
CamDummy2 camTarget2;
int bossTarget = 0;
int targetSwitchTimer = 0;

int32_t __fastcall AdolMoveHook(void* arg1) {
    int Input = baseAddress + 0x25E398;
	int Time = baseAddress + 0x25E394;
    int timeMS = ReadValue<int>(Time);
    int CanRest = baseAddress + 0x25D2BC;
    int SavePage = baseAddress + 0x425CF0;
    int SaveNum = baseAddress + 0x131D14;

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

        if (ReadValue<char>(CanRest) && ReadValue<float>(tarf + 0x14C) < 0 && ReadValue<int>(tarf + 0xA0) < ReadValue<int>(tarf + 0xA4)) {
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
    else if (ReadValue<int>(TarfData) == tarf && tarf > 0) {
        camTarget2.x = (ReadValue<int>(tarf + 0x64) + ReadValue<int>((int)arg1 + 0x64)) / 2;
        camTarget2.y = (ReadValue<int>(tarf + 0x68) + ReadValue<int>((int)arg1 + 0x68)) / 2;

		int EnemyHP = baseAddress + 0x138FE0;
        int AdolData = baseAddress + 0x1453D0;

        if (ReadValue<int>(EnemyHP) < lastEnemyHP && lastEnemyHP > 0 && ReadValue<int>(TarfData) == tarf 
                                                            && ReadValue<int>(Time) > targetSwitchTimer) {
            bossTarget = bossTarget == 0 ? (TarfData - AdolData) / 4 : 0;
            targetSwitchTimer = timeMS + 5000;
        }

		lastEnemyHP = ReadValue<int>(EnemyHP);

        if (GetKeyState(SAVE) & 0x8000 && savedTimer == 0) {
            int PreviewWidth = baseAddress + 0x44C634;
            int SavePreviewTrigger = baseAddress + 0x25DC7D;

            if (ReadValue<int>(PreviewWidth) == 0) {
                int SaveSlot = baseAddress + 0x425CF8;
                int newslot = std::max<int>(curSlot, ReadValue<int>(SaveSlot)) + 1;
                if (newslot > maxQuicksave)
                    newslot = minQuicksave;
                WriteValue(SaveSlot, newslot);
				WriteValue<char>(SavePreviewTrigger, 1);

                WriteValue<int>(SavePage, newslot / 11);
				WriteValue<int>(SaveNum, newslot % 11);
            }

            if (ReadValue<int>(PreviewWidth) > 0) {
                typedef int32_t(*OrigFunc)();
                void* originalFunc = (void*)(baseAddress + 0xC43D0);    //Preview img
                ((OrigFunc)originalFunc)();
                savedTimer = 90;
				WriteValue<int>(PreviewWidth, 0);
                WriteBytes((int)arg1 + 0x30C, "\x53\x61\x76\x65\x64", 5);
                WriteValue<int>((int)arg1 + 0x328, 0x80000009);
            }
        }
        else if (savedTimer > 0)
            savedTimer--;
    }
    else {
        camTarget2.x = ReadValue<int>((int)arg1 + 0x64);
        camTarget2.y = ReadValue<int>((int)arg1 + 0x68);
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
        int TarfGone = baseAddress + 0x25CEDC;
        int AdolData = baseAddress + 0x1453D0;
        int TarfScan[2] = { baseAddress + 0x1453D4, 0x1DC };
        int TarfUI = baseAddress + 0x25D3F4;
        int TarfStats = baseAddress + 0x12C3F0;
        int ResetSpeedCode = baseAddress + 0x1A0D4;
        int ResetAnimCode = baseAddress + 0x1A0E3;
        int TarfRoomCheckCode = baseAddress + 0x8DA04;
        int TarfRoomCheckCode2 = baseAddress + 0x4CA8B;
        int TarfRoomCheckCode3 = baseAddress + 0x4CC60;
        int CameraCode = baseAddress + 0x6F8EF;
        int CameraCode2 = baseAddress + 0x6F926;
        int IceBossCamXCode = baseAddress + 0x18A6A;
        int IceBossCamYCode = baseAddress + 0x18A9A;
        int Boss1Target = baseAddress + 0x2251E;
        int Boss1Target2 = baseAddress + 0x21352;
        int Boss1Target3 = baseAddress + 0x23E07;
        int Boss2Target = baseAddress + 0x24F90+1;
        int Boss2Target2 = baseAddress + 0x783C6+1;
        int Boss2Target3 = baseAddress + 0x9D66F+1;
        int CanMove = baseAddress + 0x135884;
        int AdolRoom = baseAddress + 0x25c730;
        //int TarfRoom = baseAddress + 0x25cecc;
        int NextRoom = baseAddress + 0x25e38c;
        int cam = baseAddress + 0x25D6D0;
        int BlackOrbStatus = baseAddress + 0x25C8A6;
        int AdolMoveFuncPtr = baseAddress + 0x10B448;
		int MagicCharge = baseAddress + 0x25CE14;
		int TarfMagic = baseAddress + 0x25D380;
        int FrameTime = baseAddress + 0x25E350;
        int CanRest = baseAddress + 0x25D2BC;
        int Fade = baseAddress + 0x12C3EA;

        WriteBytes(ResetSpeedCode, "\x90\x90\x90\x90\x90\x90\x90", 7); //Nop out speed reset
        WriteBytes(ResetAnimCode, "\x90\x90\x90\x90\x90\x90\x90", 7);
        WriteBytes(TarfRoomCheckCode, "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 10);
        WriteBytes(TarfRoomCheckCode2, "\xEB\x12", 2);
        WriteBytes(TarfRoomCheckCode3, "\xEB\x44", 2);
        WriteBytes(CameraCode, "\x8B\x05\x01\x01\x01\x01\x90", 7);
        WriteBytes(CameraCode2, "\x8B\x05\x01\x01\x01\x01\x90", 7);
        WriteBytes(IceBossCamXCode, "\x8B\x05\x01\x01\x01\x01\x90", 7);
        WriteBytes(IceBossCamYCode, "\x8B\x05\x01\x01\x01\x01\x90", 7);

        char bytes[4];
        *(int*)bytes = (int)AdolMoveHook;
		WriteBytes(AdolMoveFuncPtr, bytes, 4);

        *(int*)bytes = (int)&bossTarget;
        WriteBytes(Boss1Target, bytes, 4);
        WriteBytes(Boss1Target2, bytes, 4);
        WriteBytes(Boss1Target3, bytes, 4);

        //WriteBytes(Boss2Target, bytes, 4);
        //WriteBytes(Boss2Target2, bytes, 4);
        //WriteBytes(Boss2Target3, bytes, 4);

        *(int*)bytes = (int)&camTarget2;
        WriteBytes(CameraCode+2, bytes, 4);
        WriteBytes(CameraCode2+2, bytes, 4);
        WriteBytes(IceBossCamXCode + 2, bytes, 4);
        WriteBytes(IceBossCamYCode + 2, bytes, 4);
		camTarget2.self = &camTarget2;

		*(int*)magicChargeAddr = (int)(&magicCharge);
		*(int*)origMagicChargeBytes = MagicCharge;

        int adolLastHP = ReadValue<short>(AdolData + 0xA0);
        int adolLastMP = ReadValue<short>(AdolData + 0xA8);
        float normalFrameTime2 = 1;

        while (true) {
            Sleep(5);

            int adol = ReadValue<int>(AdolData);
			int nextRoom = ReadValue<int>(NextRoom);

            if (ReadValue<int>(AdolRoom) <= 1 || adol < baseAddress) {
                bossTarget = 0;
                continue;
            }

            if (ReadValue<unsigned char>(Fade) < 30) {
                tarf = 0;
                continue;
            }

			bool foundTarf = false;
            TarfScan[0] = AdolData + 4;
            int blankCounter = 0;
            while (blankCounter < 20) {
                if (ReadValue<int>(TarfScan, 2) == 0x2C || ReadValue<int>(TarfScan, 2) == 2 || ReadValue<int>(TarfScan, 2) == 1) {
                    TarfData = TarfScan[0];
                    tarf = ReadValue<int>(TarfData);
					foundTarf = true;
                    break;
                }
                TarfScan[0] += 4;
                if (ReadValue<int>(TarfScan[0]) < baseAddress)
                    blankCounter++;
            }

            if (ReadValue<float>(FrameTime) > 10000 && foundTarf) {
                if (normalFrameTime2 < 10000)
                    normalFrameTime2 = ReadValue<float>(FrameTime);
                else if (ReadValue<char>(CanRest) && (ReadValue<int>(adol + 0xA0) < ReadValue<int>(adol + 0xA4) || ReadValue<int>(tarf + 0xA0) < ReadValue<int>(tarf + 0xA4))
                    && ReadValue<int>(adol + 0x14C) < 0 && ReadValue<int>(tarf + 0x14C) < 0 && GetKeyState(SPEEDUP) & 0x8000) {

                    WriteValue(FrameTime, normalFrameTime2 * 0.4f);
                }
                else if (normalFrameTime2 > 10000)
                    WriteValue(FrameTime, normalFrameTime2);
            }

            bool allowTarf = ReadValue<short>(BlackOrbStatus) == 0x0100 || ReadValue<int>(NextRoom) != 98;
            WriteValue(adol + 0x24, 0.0f); //Reset Adol's speed to prevent sliding
            WriteValue<char>(TarfToggle, 44); //Keep Tarf active
            WriteValue<char>(TarfGone, allowTarf ? 0 : 1);

            if (foundTarf) {
                WriteValue(tarf, 0x50B448);
                //WriteValue(tarf + 0x1D8, 1);  //Character type
                WriteValue(tarf + 0x1D4, 1);    //Character sprite
                WriteValue(tarf + 0x1DC, 2);    //Character sprite
                WriteValue(tarf + 0x60, ReadValue<char>(adol+0x60));    //Collision layer
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
                    WriteValue(tarf + 0xA0, ReadValue<int>(tarf+0xA0) + ReadValue<short>(TarfStats + 4) - prevMaxHP);
                if(curHP - adolLastHP > 0 && curHP == ReadValue<int>(adol + 0xA4))
                    WriteValue(tarf + 0xA0, curHP);
                else if (curHP - adolLastHP > 1 && adolLastHP > 0)
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

