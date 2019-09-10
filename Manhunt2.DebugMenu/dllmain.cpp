// dllmain.cpp : Defines the entry point for the DLL application.

#define LOWORD(_dw)     ((WORD)(((DWORD_PTR)(_dw)) & 0xffff))
#define HIWORD(_dw)     ((WORD)((((DWORD_PTR)(_dw)) >> 16) & 0xffff))
#define LODWORD(_qw)    ((INT)(_qw))
#define HIDWORD(_qw)    ((DWORD)(((_qw) >> 32) & 0xffffffff))

#include "menu.h"
#include "ManhuntSdk.h"
#include <stdarg.h>
#include <algorithm>

void Init()
{
	CMenu* menu = new CMenu();

	while (true)
	{
		Sleep(1);
		menu->ProcessMenu();
	}
}

signed int __fastcall OverwriteGetHardcodedExecutoinLevel(int ptr)
{
	int v1; // esi@1
	signed int result; // eax@2
	int v3; // eax@4
	int v4; // edi@4

	v1 = ptr;
	if (*(char*)(ptr + 4359))
	{
		result = *(int*)(ptr + 4372);
		if (*(int*)(ptr + 4372) >= 2) {
			return 2;
		}
	}
	else
	{
		v3 = *(int*)(ptr + 1160);
		v4 = *(int*)(ptr + 108);

		bool isWeaponFireArm = ((bool(__thiscall*)(int*))0x4F89A0)( (int*)ptr );

		//this prevent the firearm to have 3 execution stages
		//if ((v3 == 4 || v3 == 5) && v3 != 3 || isWeaponFireArm || *(int*)(v1 + 4472)) {
		if ((v3 == 4 || v3 == 5) && v3 != 3 || *(int*)(v1 + 4472)) {
			return 2;
		}

		if (*(float*)(v4 + 5480) > (double) * (float*)(v1 + 0x1234)) {
			return 0;
		}

		result = 1;

		if (*(float*)(v4 + 5484) <= (double) * (float*)(v1 + 4660)) {
			result = 2;
		}
	}

	return result;
}


int explodeHead_ebx;
int explodeHead_unk;
int explodeHead_true = 0x5097FC;
int explodeHead_false = 0x5097C1;

void __declspec(naked) HookExtraWeaponCheck() {
	_asm {
		mov explodeHead_ebx, ebx
		mov explodeHead_unk, eax
		pushad
	}
//	if (explodeHead_ebx == CT_SAWNOFF || explodeHead_ebx == CT_SHOTGUN || explodeHead_ebx == CT_SHOTGUN_TORCH)
	if (explodeHead_ebx == 52 || explodeHead_ebx == 46 || explodeHead_ebx == 47)
	{
		if (explodeHead_unk != *(char*)0x69939C)
		{
			// decrease headshot distance for shotguns
			Memory::VP::Patch<float>(0x6991C0, 10.0);
			_asm
			{
				popad
				jmp explodeHead_true
			}
		}

	}
	else
	{
		// increase headshot distance for everything else
		Memory::VP::Patch<float>(0x6991C0, 100.0);
		_asm {
			popad
			jmp  explodeHead_false
		}
	}

}



extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{

		AllocConsole();
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);


		printf("Enable 60 FPS patch ..");
		Memory::VP::Patch(0x40D2A3, 0x412B);
		printf(". OK\n");

		
		printf("Init SDK Menu ..");
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Init), nullptr, 0, nullptr);
		printf(". OK\n");		
		
		//prevent the blood for disappearing
		printf("Prevent blood from disappearing ..");
		Memory::VP::Patch<char>(0x5E4C10, 0x74);
		printf(". OK\n");

		/*
			3-Stage firearm executions code
		*/
		//replace the function to get 3 stages for firearm
		printf("Enable Firearm 3-Stage executions ..");
		Memory::VP::InjectHook(0x599840, OverwriteGetHardcodedExecutoinLevel, PATCH_JUMP);
		printf(". OK\n");

		printf("Apply Firearm 3-Stage die pose fixes ..");
		/* Fix the DIE position, the 3 and 2 anims are not available so reuse 4 */
		//rename BAT_FALL_DIE_POSE_1HFIREARM_3_ANIM to BAT_FALL_DIE_POSE_1HFIREARM_4_ANIM
		Memory::VP::Patch<char>(0x6423B4, 0x34);
		//rename BAT_FALL_DIE_POSE_1HFIREARM_2_ANIM to BAT_FALL_DIE_POSE_1HFIREARM_4_ANIM
		Memory::VP::Patch<char>(0x6423D8, 0x34);
		printf(".");

		//rename BAT_FALL_DIE_POSE_2HFIREARM_3_ANIM to BAT_FALL_DIE_POSE_2HFIREARM_4_ANIM
		Memory::VP::Patch<char>(0x642320, 0x34);
		//rename BAT_FALL_DIE_POSE_2HFIREARM_2_ANIM to BAT_FALL_DIE_POSE_2HFIREARM_4_ANIM
		Memory::VP::Patch<char>(0x642344, 0x34);
		printf(". OK\n");



		/*
			Enable headshot for any shooter weapon
			Ermaccer Code (https://github.com/ermaccer/Manhunt2.CleanHeadshots/blob/022ca6c7346e5d4645cff08f50c9da14fe2d0771/source/dllmain.cpp)
		*/
		Memory::VP::Patch<char>(0x5097F1, 0xE9);
		Memory::VP::Patch<int>(0x5097F1 + 1, (int)HookExtraWeaponCheck - ((int)0x5097F1 + 5));

	}
}


