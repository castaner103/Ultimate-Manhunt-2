#include "ManhuntSdk.h"
#include "MemoryMgr.h"

/*Credits: Sor3nt*/
void ManhuntSdk::ClearWriteDebugOutput() {

	//todo , es gibt hier nen clear befehl ....
	SetWriteDebugDisplayDuration(1);

	for (int i = 0; i <= 22; i++)
	{
		WriteDebug(i, "");
	}


	SetWriteDebugDisplayDuration(6000);
}

/*Credits: Ermaccer*/
void ManhuntSdk::SetWriteDebugDisplayDuration( int duration ) {
	Memory::VP::Patch<char>(0x53D8DC, duration);
}

void ManhuntSdk::SetWriteDebugFontSize(float size)
{
	Memory::VP::Patch<float>(0x63D294, size);
}

/*Credits: Sor3nt*/
void ManhuntSdk::ToggleFunMode() {
	ToggleFunWeapons();
	ToggleFlowers();
}

/*Credits: Sor3nt, improved by Ermaccer*/
void ManhuntSdk::ToggleFunWeapons() {
	*(int*)0x76BE40 = *(int*)0x76BE40 == 32 ? 0 : 32;
}

/*Credits: Sor3nt*/
void ManhuntSdk::ToggleFlowers() {
	*(char*)0x6b26e5 ^= 1;
}

/*Credits: Ermaccer*/
void ManhuntSdk::SetFreeCamera(bool status) {
	*(int*)0x7894A4 = (int)status;
}

void ManhuntSdk::SetIsmMovementEnabled(bool status) {
	*(int*)0x7894A8 = (int)status;
}


void ManhuntSdk::FreezeCameraAllowMovements() {
	SetFreeCamera(true);
	SetIsmMovementEnabled(true);
}

void ManhuntSdk::SetCameraPosition(Cameras camera, CSDKVector3 vector) {
	/*
	
	CSDKVector3 vec;
	vec.x = 0.0;
	vec.y = 0.0;
	vec.z = 0.0;

	SetCameraPosition(Cameras::DEFAULT_1, vec);
	SetCameraPosition(Cameras::DEFAULT_2, vec);
	*/

	switch (camera) {
		case Cameras::DEFAULT_1:
			*(CSDKVector3*)0x76F2F0 = vector;
			break;
		case Cameras::DEFAULT_2:
			*(CSDKVector3*)0x76F300 = vector;
			break;
	}

}

MouseKeys ManhuntSdk::GetCurrentMouseKey() {
	switch (*(int*)0x76BE6C) {
		case 0: return MouseKeys::NONE;
		case 2: return MouseKeys::LEFT;
		case 32: return MouseKeys::RIGHT;
		case 1024: return MouseKeys::MOVE;
	}

	return MouseKeys::NONE;
}

void ManhuntSdk::InterrupExecution() {
	CGameSettings* sett = GetGameSettings();
	sett->exectype ^= 1;
	Sleep(100);
	sett->exectype ^= 1;
}


CGameSettings* ManhuntSdk::GetGameSettings() {
	return (CGameSettings*) * (int*)0x7604B0;
}


void ManhuntSdk::DrawCurrentPosition() {
	char buffer[64];
	CSDKVector3 pos = GetCurrentPosition();
	sprintf_s(buffer, "X = %f Y = %f Z = %f", pos.x, pos.y, pos.z);
	WriteDebug(22, buffer);
}

void ManhuntSdk::EffectExecutionColramp(int rolramp, int rnd, float x, float y, float z) {
	/*
	
	int rnd = rand();
	EffectExecutionColramp(
			*(int*)0x797718,
		rnd % 5 + 4,
		0.05,
		0.05,
		0.1
	);

	*/

	((void(__cdecl*)(int, int, float, float, float))0x605E20)(rolramp, rnd, x, y, z);
}

void ManhuntSdk::AiAddEntity(const char* entityName) {
	CallMethod<0x42E0C0, int, const char*>(0x6E5F78, entityName);
}


void ManhuntSdk::MoveEntity(CSDKEntity* entity, CSDKVector3 vec) {

	//TODO: why is my struct pointer not working ?! ask ermaccer...
//	(*(void(__thiscall * *)(CSDKEntity*, CSDKVector3*, signed int))(entityFunctions.moveFunction))(entity, &vec, 1);
	(*(void(__thiscall * *)(CSDKEntity*, CSDKVector3*, signed int))(*(int*)entity + 60))(entity, &vec, 1);
}


CSDKVector3 ManhuntSdk::GetCurrentPosition() {

	CSDKVector3 pos;
	pos.x = *(float*)0x704F68;
	pos.z = *(float*)0x704F70;
	pos.y = *(float*)0x704F6C;
	return pos;
}

int currentCloneHunterIndex = 1;

CSDKEntity* ManhuntSdk::SpawnHunterNearByPlayer(const char* name) {

	AiAddEntity(name);

	CSDKEntity* hunter = GetEntity(name);

	CSDKVector3 pos = GetCurrentPosition();

	pos.z += 0.7;

	MoveEntity(hunter, pos);

	return hunter;
}

void ManhuntSdk::DebugEntity( CSDKEntity* entity) {

	printf("Pointer: %p\n", entity);
	printf("Position: %f,%f,%f\n", entity->position.x, entity->position.y, entity->position.z);
	printf("Position2: %f,%f,%f\n", entity->position2.x, entity->position2.y, entity->position2.z);
	printf("Health: %f\n", entity->health);
	printf("Invulnnerable: %i\n", entity->invulnnerable);
	printf("heading: %f\n", entity->heading);
}

int ManhuntSdk::CreateEntityClass(char * name) {

	//int* scriptEntity = CallAndReturn<int*, 0x4E9130, char*>(name);
	CSDKEntity* scriptEntity = GetEntityInstance(name);

	if (scriptEntity) {
		return CallAndReturn<int, 0x4E12A0, CSDKEntity*>(scriptEntity);
	}
	else {
		printf("Entity %s not found!", name);
	}
}


void ManhuntSdk::TestFunction() {

	CSDKEntity* player = GetEntity("player(player)");

	CSDKVector3 pos;

	pos.x = -17.1411;
	pos.y = 6.69318;
	pos.z = 26.8479;

	MoveEntity(player, pos);


}

/*Credits: Ermaccer*/
void ManhuntSdk::TeleportToCamera() {

	//todo, thats not the correct value....s
	CSDKVector3 vec;
	vec.x = (*(float*)0x77D770 * -1);
	vec.y = (*(float*)0x77D774 * -1) - 1.7;
	vec.z = *(float*)0x77D778 * -1;

	SetFreeCamera(false);
	Teleport(vec);
}


/*Credits: Ermaccer*/
void ManhuntSdk::Teleport(CSDKVector3 vec) {
	(*(void(__thiscall * *)(CSDKEntity *, CSDKVector3*, signed int))(*(int*) * (int*)0x789490 + 60))(GetPlayer(), &vec, 1);
}

/*Credits: Ermaccer*/
void ManhuntSdk::Spawn(int itemId, bool firearm, const char* record)
{

	if (GetEntityInstance(record))
	{
		CreateInventoryItem(GetPlayer(), itemId, true);
		if (firearm == true) AddAmmoToInventoryWeapon(itemId, 150);
	}
	else printf("record %s does not exist here!\n", record);
}

/*Credits: Ermaccer*/
CSDKEntity* ManhuntSdk::GetPlayer()
{
	return *(CSDKEntity * *)0x789490;
}

/*Credits: Ermaccer*/
CSDKEntity* ManhuntSdk::GetEntityInstance(const char* name)
{
	return CallAndReturn<CSDKEntity*, 0x4E9130, const char*>(name);
}

/*Credits: Ermaccer*/
int ManhuntSdk::GetEntityPointer(const char* name)
{
	return CallAndReturn<int, 0x4EC530, const char*>(name);
}

CSDKEntity* ManhuntSdk::GetEntity(const char* name)
{
	CSDKEntity* entity = CallAndReturn<CSDKEntity*, 0x4EC530, const char*>(name);
	if (!entity) {
		sprintf("Entity %s is not loaded.\n", name);
	}
	return entity;
}


/*Credits: Ermaccer*/
void ManhuntSdk::CreateInventoryItem(CSDKEntity* ent, int item, bool b1)
{
	CallMethod<0x4F6500, CSDKEntity*, int, bool>(ent, item, b1);
}

/*Credits: Ermaccer*/
void ManhuntSdk::AddAmmoToInventoryWeapon(int itemId, int amount)
{
	int player = *(int*)(*(int*)0x789490 + 444);
	int weaponPointer = GetWeaponPointer(player, itemId );

	((void(__thiscall*)(int, int))0x5D2B30)(*(int*)(weaponPointer + 516), amount);
}

/*Credits: Ermaccer*/
int ManhuntSdk::GetWeaponPointer( int character, int itemId) {

	//generate a weapon pointer for the given character
	return ((int(__thiscall*)(int, int))0x5726F0)(character, itemId);
}

void ManhuntSdk::SetPlayerVisible(bool status) {

	*(char*)0x6D02CD = (char)status;
}

bool ManhuntSdk::IsPlayerCrawling()
{
	return (bool)*(int*)(*(int*)(*(int*)(0x789490 + 700)) + 336) == 69;
}


void ManhuntSdk::Debug(char* text, int sleep) {
	WriteDebug(22, text);
	Sleep(sleep);
}

void ManhuntSdk::SetExecutionFlashEffectStatus(bool status) {
	Memory::VP::Patch<INT8>(0x4AB1B0, status ? 0x74 : 0x75);
}


/*
	HOOKS
*/



void ManhuntSdk::HookEnableFPSCamera( int ptr)
{
	//hack because the arguments did not work ?!
	ptr = *(int*)0x789490;

	int ptrMovement = ptr + 4380;

	//we are already inside the FPS mode
	if ((*(int*)ptrMovement & 0x48000)) return;

	*(int*)ptrMovement |= 0x40000u;

	CCamera cam;
	cam.currentPosition = 0.0;
	cam.rangeUp = 150.0;
	cam.rangeDown = 150.0;
	cam.rangeLeft = -90.0;
	cam.rangeRight = 90.0;
	cam.enableFPS = 1; 
	cam.enableUnknown = 1;
	cam.center = (cam.rangeRight - cam.rangeLeft) * 0.5 + cam.rangeLeft;

	*(CCamera*)(*(int*)0x789490 + 4256) = cam;


//	SetPlayerVisible(false);
}

void ManhuntSdk::HookDisableFPSCamera(int playerPointer)
{

	playerPointer = *(int*)0x789490;

	int ptrMovement = playerPointer + 4380;

	if ((*(int*)ptrMovement & 0x40000) == 0) return;

	//Disable the FPS camera (mode)
	*(char*)(playerPointer + 4280) = 0;
//	SetPlayerVisible(true);

	*(int*)ptrMovement &= 0xFFFBFFFF;
	*(int*)ptrMovement |= 0x8000u;
}

