// dllmain.cpp : Defines the entry point for the DLL application.

#define LOWORD(_dw)     ((WORD)(((DWORD_PTR)(_dw)) & 0xffff))
#define HIWORD(_dw)     ((WORD)((((DWORD_PTR)(_dw)) >> 16) & 0xffff))
#define LODWORD(_qw)    ((INT)(_qw))
#define HIDWORD(_qw)    ((DWORD)(((_qw) >> 32) & 0xffffffff))

#include "menu.h"
#include "ManhuntSdk.h"
#include <stdarg.h>
#include <algorithm>


struct CConfig
{
	int headshot = 0;
	int bloodStay = 0;
	int firearm3 = 0;
	int flash = 0;
	int cameraShake = 0;
	int funmode = 0;
	int tvpCamera = 0;
	int debug = 0;
	int whitenoise = 0;
};

void DummyReturnVoid() { 
	printf("Dummy Called");
	return; }

CConfig config;

void ResetConfig() {
	config.headshot = 0;
	config.bloodStay = 0;
	config.firearm3 = 0;
	config.flash = 0;
	config.cameraShake = 0;
	config.funmode = 0;
	config.tvpCamera = 0;
	config.debug = 0;
	config.whitenoise = 0;
}

void UpdateWhitenoise() {
	if (config.whitenoise == 1) {
		//disable whitenoise
		Memory::VP::InjectHook(0x5C5CED, DummyReturnVoid, PATCH_CALL);

		Memory::VP::Patch<char>(0x5AF74F + 1, 0x00);
		Memory::VP::Patch<char>(0x5AF734 + 1, 0x00);


	}
	else {
		Memory::VP::Patch<char>(0x5C5CED, 0xE8);
		Memory::VP::Patch<char>(0x5C5CED + 1, 0x9E);
		Memory::VP::Patch<char>(0x5C5CED + 2, 0x9A);
		Memory::VP::Patch<char>(0x5C5CED + 3, 0xFE);
		Memory::VP::Patch<char>(0x5C5CED + 4, 0xFF);

		Memory::VP::Patch<char>(0x5AF74F + 1, 0x01);
		Memory::VP::Patch<char>(0x5AF734 + 1, 0x01);
	}
}


void UpdateFunMode() {

	if (config.funmode == 1) {
		*(int*)0x76BE40 = 32;
		*(char*)0x6B26E5 = 0;
	}
	else {
		*(int*)0x76BE40 = 0;
		*(char*)0x6B26E5 = 1;
	}
}

void UpdateCameraShake() {
	if (config.cameraShake == 1) {
		Memory::VP::Patch<char>(0x5956CA + 1, 0x85);
	}
	else {
		Memory::VP::Patch<char>(0x5956CA + 1, 0x84);
	}
}

void UpdateFlash() {
	int colRampName = *(int*)0x75C0A8;
	colRampName = colRampName + 0x208;

	if (config.flash == 1) {
		//break the colramp name so he can not load it anymore
		Memory::VP::Patch<char>(colRampName + 2, 0x00);

	}
	else {
		//restore the colramp name so he can not load it anymore
		Memory::VP::Patch<char>(colRampName + 2, 0x5f);
	}
}

void UpdateBloodStay() {
	if (config.bloodStay == 1) {
		Memory::VP::Patch<char>(0x5E4C10, 0x74);
		Memory::VP::Patch<char>(0x5E4388, 0x75);
		Memory::VP::Patch<char>(0x5E42C8, 0x75);
			
	}
	else {
		Memory::VP::Patch<char>(0x5E4C10, 0x75);
		Memory::VP::Patch<char>(0x5E4388, 0x74);
		Memory::VP::Patch<char>(0x5E42C8, 0x74);
	}

}


void SaveSettings() {
	std::ofstream myfile;
	myfile.open("settings.umh");
	myfile << "headshot=" << config.headshot << "\n";
	myfile << "bloodStay=" << config.bloodStay << "\n";
	myfile << "firearm3=" << config.firearm3 << "\n";
	myfile << "flash=" << config.flash << "\n";
	myfile << "cameraShake=" << config.cameraShake << "\n";
	myfile << "funmode=" << config.funmode << "\n";
	myfile << "tvpCamera=" << config.tvpCamera << "\n";
	myfile << "debug=" << config.debug << "\n";
	myfile << "whitenoise=" << config.whitenoise << "\n";
	myfile.close();
}

bool settingsLoaded = false;
bool settingsFlashLoaded = false;
void ReadSettings() {
	std::ifstream fin("settings.umh");
	std::string line;
	while (std::getline(fin, line)) {

		std::string stdAttribute = line.substr(0, line.find("="));
		std::string stdValue = line.substr(line.find("=") + 1);

		char* attr = new char[stdAttribute.length() + 1];
		strcpy(attr, stdAttribute.c_str());

		char* value = new char[stdValue.length() + 1];
		strcpy(value, stdValue.c_str());

		if (strcmp(attr, "headshot") == 0) {
			config.headshot = atoi(value);
		}
		else if (strcmp(attr, "debug") == 0) {
			config.debug = atoi(value);
		}
		else if (strcmp(attr, "bloodStay") == 0) {
			config.bloodStay = atoi(value);
		}
		else if (strcmp(attr, "firearm3") == 0) {
			config.firearm3 = atoi(value);
		}
		else if (strcmp(attr, "cameraShake") == 0) {
			config.cameraShake = atoi(value);
		}
		else if (strcmp(attr, "funmode") == 0) {
			config.funmode = atoi(value);
		}
		else if (strcmp(attr, "whitenoise") == 0) {
			config.whitenoise = atoi(value);
		}
		else if (strcmp(attr, "flash") == 0) {
			config.flash = atoi(value);
		}
	}
}

void ApplySettings() {
	UpdateBloodStay();
	UpdateCameraShake();
	UpdateFunMode();
	UpdateWhitenoise();
//	UpdateFlash();
}


void Init()
{
	CMenu* menu = new CMenu();

	while (true)
	{
		Sleep(1);
		menu->ProcessMenu();

		//we need to wait in some cases until the level is loaded before we can restore previous settings
		if (*(CSDKEntity * *)0x789490 != false && settingsFlashLoaded == false) {

			UpdateFlash();
			settingsFlashLoaded = true;
		}

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


		//this prevent the firearm to have 3 execution stages
		if (config.firearm3 == 1) {
			if ((v3 == 4 || v3 == 5) && v3 != 3 || *(int*)(v1 + 4472)) {
				return 2;
			}

		}
		else {
			bool isWeaponFireArm = ((bool(__thiscall*)(int*))0x4F89A0)((int*)ptr);
			if ((v3 == 4 || v3 == 5) && v3 != 3 || isWeaponFireArm || *(int*)(v1 + 4472)) {
				return 2;
			}
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
	
	if (config.headshot == 1) {
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
	else {
		_asm
		{
			popad
			jmp explodeHead_true
		}

	}


}


int endCase = 0x55F31D;
int command;
char* commandText;


void __cdecl HandleNeoMenuChangeLanguageLoadMap(int a1, int a2) {

	char* cmd = (char*)(*(int*)a2);
	printf("Neo cmd %s\n", cmd);

	if (strcmp(cmd, "setLanguage(chinese)") == 0) {
		printf("1");
			
		int set = *(int*)0x7604C8;

		((int(__fastcall*)(int, int, int))0x56C0A0)((int)& set, 1, 1);

		printf("2");
		int v4 = *(int*)0x75F110;
//		v4 = GetGameSettingsPointer();
		
		printf("3");
		((int(__fastcall*)(int))0x562AB0)((int)v4);
		//sub_562AB0((int)v4);

		printf("4");
		((void(__fastcall*)(int, int*, char))0x562B00)(v4, (int*)(a1 + 120), 1);
//		sub_562B00(v4, (_DWORD*)(a1 + 120), 1);
		printf("5");
	}
	else {
		((void(__cdecl*)(int, int))0x55F1A0)(a1, a2);

	}

}


void __cdecl HandleNeoMenuCommands(int a1, int a2) {

	char* cmd = (char*)(*(int*)a2);
	
	printf("HandleNeoMenuCommands %s\n", cmd);

	bool isCustomCmd = false;

	if (strcmp(cmd, "tvpOriginal") == 0) {
		isCustomCmd = true;
		config.tvpCamera = 0;
	}
	else if (strcmp(cmd, "tvpStatic") == 0) {
		isCustomCmd = true;
		config.tvpCamera = 1;
	}
	else if (strcmp(cmd, "tvpPs2Leak") == 0) {
		isCustomCmd = true;
		config.tvpCamera = 2;
	}
	else if (strcmp(cmd, "tvpPs2Psp") == 0) {
		isCustomCmd = true;
		config.tvpCamera = 3;
	}
	else if (strcmp(cmd, "tvpWii") == 0) {
		isCustomCmd = true;
		config.tvpCamera = 4;
	}
	else if (strcmp(cmd, "set default settings") == 0) {
		ResetConfig();
	}

	

	if (isCustomCmd) {
		//send apply msg
		((void(__thiscall*)(int*, int*, int))0x562B00)((int*)0x75F110, (int*)(a1 + 120), 1);

		SaveSettings();

		return;
	}


	((void(__cdecl*)(int, int))0x55CC60)(a1, a2);
}




/*
void __fastcall HookNeoMenuSettings( int GameSettingsPtr) {
	CallMethod<0x561C50, int>(GameSettingsPtr);
}
*/


int __fastcall WrapGetNeoMenuValue(int ptr, int a2, int a3) {
	char* fieldName = *(char**)a3;

	printf("WrapGetNeoMenuValue %s\n", fieldName);

	if (strcmp(fieldName, "headshot") == 0) {
		return config.headshot;
	}
	else if (strcmp(fieldName, "bloodStay") == 0) {
		return config.bloodStay;
	}
	else if (strcmp(fieldName, "firearm3") == 0) {
		return config.firearm3;
	}
	else if (strcmp(fieldName, "cameraShake") == 0) {
		printf("camera shake %i", config.cameraShake);
		return config.cameraShake;
	}
	else if (strcmp(fieldName, "funmode") == 0) {
		return config.funmode;
	}
	else if (strcmp(fieldName, "debug") == 0) {
		return config.debug;
	}
	else if (strcmp(fieldName, "whitenoise") == 0) {
		return config.whitenoise;
	}
	else if (strcmp(fieldName, "flash") == 0) {
		return config.flash;
	}

	return ((int(__thiscall*)(int, int))0x562510)(ptr, a3);
}



int __fastcall UpdateNeoMenuActiveStates(int ptr, int a2, int namePtr, int status) {
	
	char* fieldName = *(char**)namePtr;

	if (strcmp(fieldName, "headshot") == 0) {
		config.headshot = status;
	}
	else if (strcmp(fieldName, "firearm3") == 0) {
		config.firearm3 = status;
	}
	else if (strcmp(fieldName, "funmode") == 0) {
		config.funmode = status;
		UpdateFunMode();
	}
	else if (strcmp(fieldName, "cameraShake") == 0) {
		config.cameraShake = status;
		UpdateCameraShake();
	}
	else if (strcmp(fieldName, "flash") == 0) {
		config.flash = status;
		UpdateFlash();

	}
	else if (strcmp(fieldName, "debug") == 0) {
		config.debug = status;
	}
	else if (strcmp(fieldName, "whitenoise") == 0) {
		config.whitenoise = status;
		UpdateWhitenoise();
	}
	else if (strcmp(fieldName, "bloodStay") == 0) {
		config.bloodStay = status;
		UpdateBloodStay();
	}

	//update our config file, todo: only call this if required
	SaveSettings();

	return ((int(__thiscall*)(int, int, int))0x562630)(ptr, namePtr, status);
}



int __fastcall SetVecPairValues(int input, int a, int data) {
	
	int vecPairs = ((int(__thiscall*)(int, int))0x53B920)(input, data);

	if (config.tvpCamera == 1) {
		*(float*)(data + 36) = 5.5;
	}

	return vecPairs;

}


char* GetReplacementName(char* filename) {


	return filename;
}

int __cdecl WrapReadBinary(char* filename) {


	std::string modFilename = filename;

	std::string modFile = "mods/";
	modFile.append("Ultimate Manhunt 2/");

	printf("Load: %s\n", filename);


	if (strcmp(filename, "global/ini/resource13.glg") == 0 && config.tvpCamera != 0) {

		if (config.tvpCamera == 1) {
			modFile.append(modFilename);
			//static cam handled inline in SetVecPairValues
		}
		//ps2 leak cams
		else if (config.tvpCamera == 2) {
			modFile.append("global/ini/resource13_ps2leak.glg");
		}
		else if (config.tvpCamera == 3) {
			modFile.append("global/ini/resource13_ps2psp.glg");
		}
		else if (config.tvpCamera == 4) {
			modFile.append("global/ini/resource13_wii.glg");
		}
	}
	else {
		modFile.append(modFilename);

	}
	
	//use local save game file
	size_t isSavegame = modFilename.find("MH2_00.sav");
	if (isSavegame != std::string::npos) {
		modFile = "mods/Ultimate Manhunt 2/MH2_00.sav";
	}

	//we use our execution animation file
	size_t isExecutionFile = modFilename.find("strmanim_pc.bin");
	if (isExecutionFile != std::string::npos) {
		modFile = "mods/Ultimate Manhunt 2/strmanim_pc.bin";
	}

	size_t isAnimFile = modFilename.find("allanims_pc.IFP");
	if (isAnimFile != std::string::npos) {
		modFile = "mods/Ultimate Manhunt 2/allanims_pc.ifp";
	}

	// is the wanted file in our mod folder ?
	std::ifstream f(modFile.c_str());
	if (f.good()) {
		printf("Use custom file : %s\n", modFile.c_str());
		//copy the string to char*
		filename = new char[modFile.length() + 1];
		strcpy(filename, modFile.c_str());;
	}

	return ((int(__cdecl*)(char*))0x53BCC0)(filename);
}

FILE __cdecl Wrap2ReadBinary(char* filename, char* mode) {

	std::string modFilename = filename;

	printf("Load: %s\n", filename);

	std::string modFile = "mods/";
	modFile.append("Ultimate Manhunt 2/");
	modFile.append(modFilename);

	size_t isAnimFile = modFilename.find("allanims_pc.IFP");
	if (isAnimFile != std::string::npos) {
		modFile = "mods/Ultimate Manhunt 2/allanims_pc.ifp";
	}


	// is the wanted file in our mod folder ?
	std::ifstream f(modFile.c_str());
	if (f.good()) {
//		std::cout << "Replace file : " << filename << std::endl;

		//copy the string to char*
		filename = new char[modFile.length() + 1];
		strcpy(filename, modFile.c_str());;
	}

	return ((FILE(__cdecl*)(char*, char*, int))0x61B338)(filename, mode, 64);
}

unsigned int __cdecl GetTexturByName(char* textureName) {

//	textureName = "mangler";

	printf("textureName: %s", textureName);
	
		return ((unsigned int(__cdecl*)(char*))0x57A190)(textureName);

}




int __fastcall sub_5ED660(int mem, int count1, int count2, int pedHeadAndOrPlayerBitmask, int bitModel4, int a6, int a7, int a8, int a9, float a10, float a11, float a12, float a13, float a14, int a15, float a16)
{
	printf("Count 2: %i\n", count2);
	printf("a6: %i\n", a6);
	printf("a7: %i\n", a7);

	return ((int(__thiscall*)(int, int, int, int, int, int, int, int, int, float, float, float, float, float, int, float))0x5ED660)(mem, count1, count2, pedHeadAndOrPlayerBitmask, bitModel4, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
}

int __fastcall GetHudWeaponIcon(int graphicPtr, int a, int weaponId)
{
	return *(int*)(graphicPtr + 984);
}

/*
int __cdecl ChangeHudWeaponIconIfNoFists( int weaponId)
{
	printf("CALLED");
	return ((int(__cdecl*)(int, int))0x54C150)(weaponId, 1);
}
*/



void HandleHudWeaponIcon()
{

		int v0; // ebp@3
		int v1; // esi@3
		int v2; // edi@3
		int v3; // ecx@3
		int v4; // edx@3
		signed int v5; // eax@21
		signed int v6; // eax@44
		int v7; // edi@52
		signed int v8; // esi@52
		int v9; // eax@62
		int v10; // ebx@62
		int v11; // esi@65
		int v12; // edi@65
		float v13; // ST20_4@70
		double v14; // st6@68
		float v15; // ST18_4@70
		int v16; // eax@74
		int v17; // [sp+8h] [bp-Ch]@3
		int v18; // [sp+Ch] [bp-8h]@3
		int v19; // [sp+10h] [bp-4h]@0

		if (*(int*)0x75CF40)
		{
			((int(*)())0x54C210)();
			//sub_54C210();
			*(int*)0x75CF40 = 0;
		}
		v0 = *(int*)0x789490;
		v1 = *(int*)(*(int*)0x789490 + 448);
		v2 = *(int*)(*(int*)0x789490 + 444);
		*(int*)0x75CF84 = *(int*)(*(int*)(v2 + 12) + 4);
		*(int*)0x75CF88 = *(int*)(*(int*)(v2 + 12) + 8);
		v3 = *(int*)(*(int*)(v2 + 12) + 12);
		*(int*)0x75CF8C = *(int*)(*(int*)(v2 + 12) + 12);
		v4 = *(int*)(*(int*)(v2 + 12) + 16);
		v17 = v2;
		v18 = v1;
		*(int*)0x75CF90 = *(int*)(*(int*)(v2 + 12) + 16);
		if (*(int*)0x75CF84 || *(int*)0x75CF88 || (*(int*)0x75CDEC = 1, v4))
			* (int*)0x75CDEC = 0;
		if (*(int*)0x75CF00)
			goto LABEL_82;
		if (*(int*)0x75CF94 && !*(int*)0x75CF84)
		{
			((int(__fastcall*)(int, int))0x599D50)(*(int*)0x789490, 0);
//			sub_599D50(*(int*)0x789490, 0);
			v3 = *(int*)0x75CF8C;
		}
		if (*(int*)0x75CF98 && !*(int*)0x75CF88)
		{
			((int(__fastcall*)(int, int))0x599D50)(v0, 0);
//			sub_599D50(v0, 0);
			v3 = *(int*)0x75CF8C;
		}
		if (*(int*)0x75CF9C && !v3)
		{
			((int(__fastcall*)(int, int))0x599D50)(v0, 0);
//			sub_599D50(v0, 0);
			v3 = *(int*)0x75CF8C;
		}
		if (*(int*)0x75CFA0 && !*(int*)0x75CF90)
		{
			((int(__fastcall*)(int, int))0x599D50)(v0, 0);
//			sub_599D50(v0, 0);
			v3 = *(int*)0x75CF8C;
		}
		if (*(int*)0x75CF00)
		{
		LABEL_82:
			*(int*)0x75CF38 = *(int*)0x75CF04;
		LABEL_43:
			*(int*)0x75CF80 = 1;
			goto LABEL_44;
		}
		v5 = 0;
		if (!*(int*)0x75CF74 && v1)
			v5 = 1;
		if (*(int*)0x75CF38 == 3 && !v3)
			v5 = 1;
		if (*(int*)0x75CF84 != *(int*)0x75CF94)
		{
			if (v5)
				* (int*)0x75CF38 = 1;
			*(int*)0x75CF80 = 1;
		}
		if (*(int*)0x75CF88 != *(int*)0x75CF98)
		{
			if (v5)
				* (int*)0x75CF38 = 2;
			*(int*)0x75CF80 = 1;
		}
		if (v3 != *(int*)0x75CF9C)
		{
			if (v5)
				* (int*)0x75CF38 = 3;
			*(int*)0x75CF80 = 1;
		}
		if (*(int*)0x75CF90 != *(int*)0x75CFA0)
		{
			if (v5)
				* (int*)0x75CF38 = 4;
			goto LABEL_43;
		}
	LABEL_44:
		*(int*)0x75CF94 = *(int*)0x75CF84;
		*(int*)0x75CF98 = *(int*)0x75CF88;
		v6 = 0;
		*(int*)0x75CF9C = v3;
		*(int*)0x75CFA0 = *(int*)0x75CF90;
		*(int*)0x75CF74 = v1;
		if (!v3)
			v6 = 1;
		if (!*(int*)0x75CF00 || *(int*)0x75CF04)
		{
			if (!v6)
				goto LABEL_51;
		}
		else
		{
			*(int*)0x75CF38 = 3;
		}
		*(int*)0x75CF58 = 16;
		*(int*)0x75CF68 = ((int(__fastcall*)(int, int))0x569130)((int)&*(int*)0x75BDB8, 16);
		printf("1");

	LABEL_51:
		if (*(int*)0x75CF80)
		{
			((int(__cdecl*)())0x54C210)();
			//sub_54C210();
			((int(__cdecl*)())0x54C070)();
			//sub_54C070();
			v7 = v19;
			v8 = 0;
			do
			{
				if (v8)
				{
					switch (v8)
					{
					case 1:
						v7 = *(int*)0x75CF88;
						break;
					case 2:
						v7 = *(int*)0x75CF8C;
						break;
					case 3:
						v7 = *(int*)0x75CF90;
						break;
					}
				}
				else
				{
					v7 = *(int*)0x75CF84;
				}
				if (v7)
				{

					v9 = ((int(__fastcall*)(int))0x54C070)(v7);
					//v9 = sub_526960(v7);
					v10 = ((int(__cdecl*)(int, int))0x54C150)(v9, 0);
//					v10 = sub_54C150(v9, 0);

					int* stuff = *(int**)0x75CF50;
					stuff[v8] = ((int(__fastcall*)(int))0x54C150)(v7);
					// dword_75CF50[v8] = GetEntityId(entityId);

					int* stuff2 = *(int**)0x75CF60;
					stuff2[v8] = v10;
					//dword_75CF60[v8] = v10;
				}
				++v8;
			} while (v8 < 4);
			v2 = v17;
			*(int*)0x75CF80 = 0;
		}
		printf("2");
		v11 = *(int*)0x75CF38;
		printf("3");

		//v12 = *(int*)(*(int*)(v2 + 12) + 4 * *(int*)0x75CF38);

		printf("4");
		if (!((bool(__cdecl*)())0x53DEE0)())
//		if (!sub_53DEE0())
		{
			if (false)
			//if (v12)
			{
				if (v18 != v11)
				{
					v14 = *(float*)0x6ECE68;
					if (*(float*)0x6ECE68 <= 0.0)
						v14 = 0.000099999997;
					v15 = v14;
					*(float*)0x75CFA4 = v15 + *(float*)0x75CFA4;
					v13 = *(float*)0x76EB48 + *(float*)0x76EB44;
					if (v13 < (double) * (float*)0x75CFA4)
					{
						*(float*)0x75CFA4 = 0.0;
						((signed int(__fastcall*)(int, int, int))0x506BE0)(v0, v11, 0);
//						sub_506BE0(v0, v11, 0);
					}
				}
			}
			else
			{
				((signed int(__fastcall*)(int, int, int))0x506BE0)(v0, 0, 0);
//				sub_506BE0(v0, 0, 0);
			}
		}

		printf("5");
		
		if (*(int*)0x75CF44)
		{
			*(int*)0x75CF44 = 0;
			v16 = 0;
			while (*(int*)(0x75CF20 + v16) != v11)
			//while (*(int*)0x75CF20[v16] != v11)
			{
				if (++v16 >= 4)
				{
					*(int*)0x75CF7C = 0;
					*(int*)0x75CF00 = 0;
					return;
				}
			}
			*(int*)0x75CF34 = v16 + 1;
		}
		*(int*)0x75CF7C = 0;
		*(int*)0x75CF00 = 0;

		
}

int __cdecl CalcHash(char const* str)
{
	int hash = 0;
	for (char const* c = str; *c; ++c) {
		char chr = (unsigned char)(*c - 97) <= 25 ? *c - 32 : *c;
		hash = hash * 33 + chr;
	}

	std::ofstream myfile;
	myfile.open("hashes.txt", std::fstream::out | std::fstream::app);
	myfile << str << "\n";
	myfile.close();

	return hash;
}

int __fastcall crc32(int* self, int a, char* a2)
{
	char* v2; // edi@1
	char v3; // al@1
	unsigned int v4; // esi@1
	int* i; // ebx@1

	std::ofstream myfile;
	myfile.open("crc32.txt", std::fstream::out | std::fstream::app);
	myfile << a2 << "\n";
	myfile.close();


	v2 = a2;
	v3 = *a2;
	v4 = -1;
	for (i = self; v3; ++v2)
	{
		v4 = i[(unsigned __int8)(v4 ^ tolower(v3))] ^ (v4 >> 8);
		v3 = v2[1];
	}
	return ~v4;
}






extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{

		ReadSettings();
		ApplySettings();
		
		if (config.debug) {
			AllocConsole();
			freopen("CONIN$", "r", stdin);
			freopen("CONOUT$", "w", stdout);
			freopen("CONOUT$", "w", stderr);
		}

		printf("Remove legal screen ..");
		Memory::VP::Patch(0x53FC68, 0);
		Memory::VP::Patch(0x53FC50, 0);
		Memory::VP::Patch(0x53FC6F, 0);
		printf(". OK\n");

		printf("Enable 60 FPS patch ..");
		Memory::VP::Patch(0x40D2A3, 0x412B);
		printf(". OK\n");

//		Memory::VP::InjectHook(0x5890A0, CalcHash, PATCH_JUMP);
//		Memory::VP::InjectHook(0x7D8610, crc32, PATCH_JUMP);

		//skip vecpair handling
	//	Memory::VP::InjectHook(0x5CB6DE, 0x5CB6CB, PATCH_JUMP);


		//interactive skip icon drawer
//		Memory::VP::InjectHook(0x5B5DE0, 0x5B5E6B, PATCH_JUMP);

	//	Memory::VP::InjectHook(0x5A997A, 0x5A998B, PATCH_JUMP);

		
//		Memory::VP::InjectHook(0x5A987A, 0x5A98A8, PATCH_JUMP);


		//amount of brain bits
		Memory::VP::Patch<char>(0x523A9C + 2, 0x1e);



		//patch heap to 512MB. this can not be done here, exe need to be patched (thx to MAJEST1C_R3 !)
//			Memory::VP::Patch<char>(0x580950 + 4, 0x1f);


		printf("Enable ModLoader ..");

		// Hook the readBinary call
		Memory::VP::InjectHook(0x57B2E5, Wrap2ReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x418A1E, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4B0842, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4C3A7C, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4C7F68, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4C8D87, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4CCD10, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4CD186, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4CD245, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4CFEB7, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4E9029, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x4EBB04, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x53BD0B, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x53CC17, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x53EA07, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x56AEE9, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x56E550, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x583EC4, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x586249, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x5BC856, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x5BC86B, WrapReadBinary, PATCH_CALL);
		Memory::VP::InjectHook(0x5DEA76, WrapReadBinary, PATCH_CALL);
		printf(". OK\n");



			//	Memory::VP::InjectHook(0x5455F4, HandleHudWeaponIcon, PATCH_CALL);
		

		/*
			3-Stage firearm executions code
		*/
		//replace the function to get 3 stages for firearm
		printf("Hooking Firearm 3-Stage executions handler ..");
		Memory::VP::InjectHook(0x599840, OverwriteGetHardcodedExecutoinLevel, PATCH_JUMP);

		/* Fix the DIE position, the 3 and 2 anims are not available so reuse 4 */
		//rename BAT_FALL_DIE_POSE_1HFIREARM_3_ANIM to BAT_FALL_DIE_POSE_1HFIREARM_4_ANIM
		Memory::VP::Patch<char>(0x6423B4, 0x34);
		//rename BAT_FALL_DIE_POSE_1HFIREARM_2_ANIM to BAT_FALL_DIE_POSE_1HFIREARM_4_ANIM
		Memory::VP::Patch<char>(0x6423D8, 0x34);

		//rename BAT_FALL_DIE_POSE_2HFIREARM_3_ANIM to BAT_FALL_DIE_POSE_2HFIREARM_4_ANIM
		Memory::VP::Patch<char>(0x642320, 0x34);
		//rename BAT_FALL_DIE_POSE_2HFIREARM_2_ANIM to BAT_FALL_DIE_POSE_2HFIREARM_4_ANIM
		Memory::VP::Patch<char>(0x642344, 0x34);
		printf(". OK\n");



		/*
			Enable headshot for any shooter weapon
			Ermaccer Code (https://github.com/ermaccer/Manhunt2.CleanHeadshots/blob/022ca6c7346e5d4645cff08f50c9da14fe2d0771/source/dllmain.cpp)
		*/

		printf("Hooking headshot handler ..");
		Memory::VP::Patch<char>(0x5097F1, 0xE9);
		Memory::VP::Patch<int>(0x5097F1 + 1, (int)HookExtraWeaponCheck - ((int)0x5097F1 + 5));
		printf(". OK\n");


		printf("Hooking NeoMenu functions ..");
		Memory::VP::InjectHook(0x560078, HandleNeoMenuChangeLanguageLoadMap, PATCH_CALL);
		Memory::VP::InjectHook(0x560069, HandleNeoMenuCommands, PATCH_CALL);
		
		Memory::VP::InjectHook(0x5570B1, WrapGetNeoMenuValue, PATCH_CALL);
		Memory::VP::InjectHook(0x5571E6, WrapGetNeoMenuValue, PATCH_CALL);
		Memory::VP::InjectHook(0x55DFA0, WrapGetNeoMenuValue, PATCH_CALL);
		Memory::VP::InjectHook(0x55E58E, WrapGetNeoMenuValue, PATCH_CALL);
		Memory::VP::InjectHook(0x5625B6, WrapGetNeoMenuValue, PATCH_CALL);


		Memory::VP::InjectHook(0x55DEAA, UpdateNeoMenuActiveStates, PATCH_CALL);
		Memory::VP::InjectHook(0x55E4B6, UpdateNeoMenuActiveStates, PATCH_CALL);
		Memory::VP::InjectHook(0x55E721, UpdateNeoMenuActiveStates, PATCH_CALL);

		//replace the translation output "Key Missing:" to nothing...
		//we do not translate our keys because of limitations in the gxt / handler so we just remove the prependix
		for (int i = 0; i < 24; i++) {
			Memory::VP::Patch<char>(0x6A9984 + i, 0x20);
		}

		printf(". OK\n");
		
	
		printf("Hooking Timed Vector Pair handler ..");
		Memory::VP::InjectHook(0x5CB3FC, SetVecPairValues, PATCH_CALL);
		Memory::VP::InjectHook(0x5CB445, SetVecPairValues, PATCH_CALL);
		printf(". OK\n");

		printf("Init Debug Menu ..");
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Init), nullptr, 0, nullptr);
		printf(". OK\n");

		//printf("Replace FPS camera Menu.");
	//	Memory::VP::InjectHook(0x598D40, ManhuntSdk::HookEnableFPSCamera, PATCH_JUMP);
	//	Memory::VP::InjectHook(0x598EB0, ManhuntSdk::HookDisableFPSCamera, PATCH_JUMP);
		//printf(". OK\n");


		
//		Memory::VP::Patch<char>(0x54C1E4 + 2, 0x63);
	//	Memory::VP::Patch<char>(0x5285D0 + 2, 0x63);

//		Memory::VP::Patch<char>(0x55B292 + 1, 0x63);
		
		
		


		//Memory::VP::InjectHook(0x57A454, GetTexturByName, PATCH_CALL);


	}
}


