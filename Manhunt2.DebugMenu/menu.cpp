#pragma once
#include "menu.h"

ManhuntSdk* SDK = new ManhuntSdk();


/*Build the main menu*/

MenuEntry MAIN_MENU_WEAPONS{ Types::MENU_ENTRY, "Weapons", "", "weapons" };
MenuEntry MAIN_MENU_HELPER{ Types::MENU_ENTRY, "Helper", "", "helpers" };

MenuEntry TOGGLE_FREE_CAM{ Types::TOGGLE, "Free Camera", "freecam" };
MenuEntry TOGGLE_TEST{ Types::TOGGLE, "test", "TestFunction" };
MenuEntry TOGGLE_NEVERDEAD{ Types::TOGGLE, "Never dead", "neverDead" };

MenuEntry TOGGLE_GODMODE{ Types::TOGGLE, "GodMode", "GodMode" };

MenuEntry MenuHome[] = {
	MAIN_MENU_WEAPONS, 
	MAIN_MENU_HELPER,
	TOGGLE_FREE_CAM, 
	TOGGLE_TEST, 
	TOGGLE_GODMODE,
	TOGGLE_NEVERDEAD
};

int MenuHomeCount = sizeof(MenuHome) / sizeof(MenuHome[0]);

MenuEntry HELPER_BACK{ Types::MENU_ENTRY, "BACK", "", "home" };

MenuEntry WEAPON_BACK{ Types::MENU_ENTRY, "BACK", "", "home" };

/*Prepare the weapons*/
MenuEntry WEAPON_TORCH{ Types::WEAPON, "Torch", "Torch_(CT)", "", 6, false };
MenuEntry WEAPON_HUNT_KNIFE{ Types::WEAPON, "Hunt Knife", "Hunt_Knife_(CT)", "", 18, false };
MenuEntry WEAPON_SHARD{ Types::WEAPON, "Shard", "Shard_(CT)", "", 19, false };
MenuEntry WEAPON_BOTTLE{ Types::WEAPON, "Bottle", "Bottle_(CT)", "", 22, false };
MenuEntry WEAPON_CLEAVER{ Types::WEAPON, "Cleaver", "Cleaver_(CT)", "", 24, false };
MenuEntry WEAPON_CROWBAR{ Types::WEAPON, "Crowbar", "Crowbar_(CT)", "", 26, false };
MenuEntry WEAPON_SICKLE{ Types::WEAPON, "Sickle", "Sickle_(CT)", "", 27, false };
MenuEntry WEAPON_NIGHTSTICK{ Types::WEAPON, "NightStick", "NightStick_(CT)", "", 28, false };
MenuEntry WEAPON_AXE{ Types::WEAPON, "Axe", "Axe_(CT)", "", 30, false };
MenuEntry WEAPON_ICE_PICK{ Types::WEAPON, "IcePick", "IcePick_(CT)", "", 31, false };
MenuEntry WEAPON_MACHETE{ Types::WEAPON, "Machete", "Machete_(CT)", "", 32, false };
MenuEntry WEAPON_SMALL_BAT{ Types::WEAPON, "Small Bat", "Small_Bat_(CT)", "", 33, false };
MenuEntry WEAPON_PLIERS{ Types::WEAPON, "Pliers", "Pliers_(CT)", "", 34, false };
MenuEntry WEAPON_METAL_BAT{ Types::WEAPON, "Metal Bat", "M_B_Bat_(CT)", "", 35, false };
MenuEntry WEAPON_WOODEN_BAT{ Types::WEAPON, "Wooden Bat", "W_B_Bat_(CT)", "", 36, false };
MenuEntry WEAPON_FIRE_AXE{ Types::WEAPON, "Fire Axe", "Fire_Axe_(CT)", "", 37, false };
MenuEntry WEAPON_BAT_WITH_NAILS{ Types::WEAPON, "Bat with Nails", "W_B_Bat_Nails_(CT)", "", 39, false };
MenuEntry WEAPON_6SHOOTER{ Types::WEAPON, "6Shooter", "6Shooter_(CT)", "", 40, true };
MenuEntry WEAPON_GLOCK{ Types::WEAPON, "Glock", "Glock_(CT)", "", 41, true };
MenuEntry WEAPON_UZI{ Types::WEAPON, "Uzi", "Uzi_(CT)", "", 44, true };
MenuEntry WEAPON_UZI_TORCH{ Types::WEAPON, "Uzi Torch", "Uzi_Torch_(CT)", "", 45, true };
MenuEntry WEAPON_SHOTGUN{ Types::WEAPON, "Shotgun", "Shotgun_(CT)", "", 46, true };
MenuEntry WEAPON_SHOTGUN_TORCH{ Types::WEAPON, "Shotgun Torch", "Shotgun_Torch_(CT)", "", 47, true };
MenuEntry WEAPON_DESERT_EAGLE{ Types::WEAPON, "Desert Eagle", "Desert_Eagle_(CT)", "", 48, true };
MenuEntry WEAPON_COLT_COMMANDO{ Types::WEAPON, "Colt Commando", "C_Commando_(CT)", "",  49, true };
MenuEntry WEAPON_SNIPER_RIFLE{ Types::WEAPON, "Sniper Rifle", "Sniper_Rifle_(CT)", "",  50, true };
MenuEntry WEAPON_TRANQ_RIFLE{ Types::WEAPON, "Tranq Rifle", "Tranq_Rifle_(CT)", "",  51, true };
MenuEntry WEAPON_SAWNOFF_SHOTGUN{ Types::WEAPON, "SawnOff Shotgun", "SawnOff_Shotgun_(CT)", "",  52, true };
MenuEntry WEAPON_HALF_BRICK{ Types::WEAPON, "Half Brick", "Half_Brick_(CT)", "",  58, false };
MenuEntry WEAPON_BAG{ Types::WEAPON, "Bag", "Bag_(CT)", "",  60, false };
MenuEntry WEAPON_CHAINSAW{ Types::WEAPON, "Chainsaw", "Chainsaw_(CT)", "",  90, false };
MenuEntry WEAPON_NAIL_GUN{ Types::WEAPON, "Nail Gun", "Nail_Gun_(CT)", "",  91, true };
MenuEntry WEAPON_WIRE{ Types::WEAPON, "Wire", "Wire_(CT)", "",  92, false };
MenuEntry WEAPON_CAN{ Types::WEAPON, "Can", "Can_(CT)", "",  93, false };
MenuEntry WEAPON_WOODEN_SPIKE{ Types::WEAPON, "Wooden Spike", "Wooden_Spike_(CT)", "",  94, false };
MenuEntry WEAPON_SNIPER_RIFLE_SILENCED{ Types::WEAPON, "Sniper Rifle Silenced", "Sniper_Rifle_Silenced_(CT)", "",  95, true };
MenuEntry WEAPON_HAMMER{ Types::WEAPON, "Hammer", "Hammer_(CT)", "",  99, false };
MenuEntry WEAPON_CHAINSAW_PLAYER{ Types::WEAPON, "Chainsaw (Player)", "Chainsaw_Player_(CT)", "",  110, false };
MenuEntry WEAPON_SYRINGE{ Types::WEAPON, "Syringe", "Syringe_(CT)", "", 113, false };
MenuEntry WEAPON_SHOVEL{ Types::WEAPON, "Shovel", "Shovel_(CT)", "", 114, false };
MenuEntry WEAPON_SLEDGEHAMMER{ Types::WEAPON, "SledgeHammer", "SledgeHammer_(CT)", "", 115, false };
MenuEntry WEAPON_STUNPROD{ Types::WEAPON, "Stunprod", "Stunprod_(CT)", "", 116, true };
MenuEntry WEAPON_PEN{ Types::WEAPON, "Pen", "Pen_(CT)", "", 117, false };
MenuEntry WEAPON_ACID_BOTTLE{ Types::WEAPON, "Acid Bottle", "AcidBottle_(CT)", "", 118, false };
MenuEntry WEAPON_1H_FIREARM{ Types::WEAPON, "1H Firearm", "1HFirearm_(CT)", "", 119, true };
MenuEntry WEAPON_2H_FIREARM{ Types::WEAPON, "2H Firearm", "2HFirearm_(CT)", "", 120, true };
MenuEntry WEAPON_CUT_THROAT_RAZOR{ Types::WEAPON, "Cut throat razor", "CUT_THROAT_RAZOR_(CT)", "", 121, false };
MenuEntry WEAPON_BLOWTORCH{ Types::WEAPON, "Blowtorch", "Blowtorch_(CT)", "", 122, false };
MenuEntry WEAPON_MACE{ Types::WEAPON, "Mace", "Mace_(CT)", "", 123, false };
MenuEntry WEAPON_HEDGE_TRIMMER{ Types::WEAPON, "Hedge Trimmer", "Hedge_Trimmer_(CT)", "", 124, false };
MenuEntry WEAPON_METALHOOK{ Types::WEAPON, "MetalHook", "MetalHook_(CT)", "", 125, false };
MenuEntry WEAPON_CIRCULAR_SAW{ Types::WEAPON, "Circular Saw", "Circular_Saw_(CT)", "", 126, false };
MenuEntry WEAPON_FLAREGUN{ Types::WEAPON, "FlareGun", "FlareGun_(CT)", "", 127, true };
MenuEntry WEAPON_CROSSBOW{ Types::WEAPON, "Crossbow", "Crossbow_(CT)", "", 131, true };
MenuEntry WEAPON_NEWSPAPER{ Types::WEAPON, "Newspaper", "newspaper(CT)", "", 134, false };
MenuEntry WEAPON_MILKBOTTLE{ Types::WEAPON, "Milkbottle", "milkbottle(CT)", "", 135, false };
MenuEntry WEAPON_DILDO{ Types::WEAPON, "Dildo", "dildo(CT)", "", 136, false };
MenuEntry WEAPON_KATANA{ Types::WEAPON, "Katana", "katana(CT)", "", 137, false };
MenuEntry WEAPON_HACKSAW{ Types::WEAPON, "Hacksaw", "hacksaw(CT)", "", 138, false };
MenuEntry WEAPON_GOLFBALL{ Types::WEAPON, "GolfBall", "GolfBall_(CT)", "", 139, false };
MenuEntry WEAPON_CASH_BUNDLE{ Types::WEAPON, "Cash Bundle", "Cash_Bundle_(CT)", "", 140, false };
MenuEntry WEAPON_PORN{ Types::WEAPON, "Porn", "Porn_(CT)", "", 141, false };
MenuEntry WEAPON_MATCHBOOK{ Types::WEAPON, "Matchbook", "Matchbook_(CT)", "", 142, false };


MenuEntry HELPER_A01_JUMPSCARE{ Types::SET_PLAYER_POS, "Port to Jumpscare", "Jumpscare", "", 0, false };
MenuEntry HELPER_SPAWN{ Types::TRIGGER, "Spawn a hunter", "spawn", "", 0, false };

MenuEntry AnyHelpers[] = {
	HELPER_A01_JUMPSCARE,
	HELPER_SPAWN
};

MenuEntry AnyWeapons[] = { 
	WEAPON_TORCH, 
	WEAPON_HUNT_KNIFE,
	WEAPON_SHARD,
	WEAPON_BOTTLE,
	WEAPON_CLEAVER,
	WEAPON_CROWBAR,
	WEAPON_SICKLE,
	WEAPON_NIGHTSTICK,
	WEAPON_AXE,
	WEAPON_ICE_PICK,
	WEAPON_MACHETE,
	WEAPON_SMALL_BAT,
	WEAPON_PLIERS,
	WEAPON_METAL_BAT,
	WEAPON_WOODEN_BAT,
	WEAPON_FIRE_AXE,
	WEAPON_BAT_WITH_NAILS,
	WEAPON_GLOCK,
	WEAPON_6SHOOTER,
	WEAPON_UZI,
	WEAPON_UZI_TORCH,
	WEAPON_SHOTGUN,
	WEAPON_SHOTGUN_TORCH,
	WEAPON_DESERT_EAGLE,
	WEAPON_COLT_COMMANDO,
	WEAPON_SNIPER_RIFLE,
	WEAPON_TRANQ_RIFLE,
	WEAPON_SAWNOFF_SHOTGUN,
	WEAPON_HALF_BRICK,
	WEAPON_BAG,
	WEAPON_CHAINSAW,
	WEAPON_NAIL_GUN,
	WEAPON_WIRE, 
	WEAPON_CAN,
	WEAPON_WOODEN_SPIKE,
	WEAPON_SNIPER_RIFLE_SILENCED,
	WEAPON_HAMMER,
	WEAPON_CHAINSAW_PLAYER, 
	WEAPON_SYRINGE, 
	WEAPON_SHOVEL,
	WEAPON_SLEDGEHAMMER,
	WEAPON_STUNPROD,
	WEAPON_PEN, 
	WEAPON_ACID_BOTTLE,
	WEAPON_1H_FIREARM,
	WEAPON_2H_FIREARM,
	WEAPON_CUT_THROAT_RAZOR,
	WEAPON_BLOWTORCH,
	WEAPON_MACE,
	WEAPON_HEDGE_TRIMMER,
	WEAPON_METALHOOK,
	WEAPON_CIRCULAR_SAW, 
	WEAPON_FLAREGUN,
	WEAPON_CROSSBOW,
	WEAPON_NEWSPAPER,
	WEAPON_MILKBOTTLE,
	WEAPON_DILDO,
	WEAPON_KATANA, 
	WEAPON_HACKSAW,
	WEAPON_GOLFBALL, 
	WEAPON_CASH_BUNDLE,
	WEAPON_PORN, 
	WEAPON_MATCHBOOK
};


MenuEntry MenuWeapons[100];
int MenuWeaponsCount = 0;

MenuEntry MenuHelpers[100];
int MenuHelpersCount = 0;

int MenuCount = MenuHomeCount;

bool NavigationChanged = false;


int godMode = false;

void CMenu::BuildMenu() {

	int menuIndex = 0;
	int anyWeaponsCount = sizeof(AnyWeapons) / sizeof(AnyWeapons[0]);

	//add the back button
	MenuWeapons[menuIndex++] = { WEAPON_BACK };

	// append available weapons to the list, ignore other
	for (int i = 0; i < anyWeaponsCount; i++) {
		if (SDK->GetEntityInstance(AnyWeapons[i].entityName.c_str())) {
			MenuWeapons[menuIndex++] = { AnyWeapons[i] };
		}
	}

	MenuWeaponsCount = menuIndex;


	menuIndex = 0;
	int anyHelpersCount = sizeof(AnyHelpers) / sizeof(AnyHelpers[0]);

	//add the back button
	MenuHelpers[menuIndex++] = { HELPER_BACK };

	// append available helpers to the list, ignore other

	//todo: add level check and allow only level related helpers
	for (int i = 0; i < anyHelpersCount; i++) {
		MenuHelpers[menuIndex++] = { AnyHelpers[i] };
	}

	MenuHelpersCount = menuIndex;


	SDK->SetWriteDebugFontSize(1.0);
}

void CMenu::ProcessMenu()
{
	

	if (System::KeyHit(VK_SPACE)) {
		SDK->InterrupExecution();
	}

	//Toggle the Menu with F1
	CMenu::ToggleMenu();

	if (godMode) {
		CallMethod<0x4E1D20, CSDKEntity*, float>(SDK->GetPlayer(), 120.f);
	}

	//Nothing todo
	if (DisplayMenu == 0) return;

	//Auto hide the menu if the player in main menu (0x75B334) or no player is available
	if (*(int*)0x75B334 == 1 || SDK->GetPlayer() == false) return;


	//We did not build yet the menu entries
	if (MenuWeaponsCount == 0) BuildMenu();

	CMenu::ProcessUserNavigation();

	//only print the menu when the user changed something...
	if (NavigationChanged) {
		CMenu::PrintMenu();
		NavigationChanged = false;
	}
	
}

void CMenu::ToggleMenu() {
	if (System::KeyHit(VK_F1)) {
		DisplayMenu ^= 1;

		//We need to increase the display speed for menu rendering
		// PrintText(a2, (int)&a1, v4, 80, 0);
		Memory::VP::Patch<char>(0x53D8DC, DisplayMenu == 1 ? 6000 : 80);

		Memory::VP::Patch<double>(0x65F1A0, DisplayMenu == 1 ? -1.0 : 0.01999999955296516);

		if (DisplayMenu == 0) {
			//force the while do stop drawing the boxes
//			Memory::VP::Patch<BYTE>(0x545257, 0);
	
		}

//		SDK->WriteDebug(22, "~TM~ ~cross~ ~circle~ ~triangle~ ~square~ ~up~ ~down~ ~left~ ~right~ ~(C)~ ~(R)~ ~!~ ~ACTION_USE~ ~ACTION_MENU~ ~STAR2~ ~STAR~");
		
		//sleep some ms to avoid double calling the toggle
		Sleep(130);

		NavigationChanged = true;
	}


}


void CMenu::ProcessUserNavigation() {

	if (System::KeyHit(VK_UP)) {
		Sleep(130);
		Selection--;
		NavigationChanged = true;
	}

	if (System::KeyHit(VK_DOWN)) {
		Sleep(130);
		Selection++;
		NavigationChanged = true;
	}

	if (System::KeyHit(VK_RIGHT)) {
		Sleep(130);
		Selection = 0;
		CurrentPage++;
		NavigationChanged = true;
	}

	if (System::KeyHit(VK_LEFT)) {
		Sleep(130);
		Selection = 0;
		CurrentPage--;
		NavigationChanged = true;
	}

	if (System::KeyHit(VK_RETURN)) {
		Sleep(130);

		MenuEntry& selectedEntry = GetSelectedEntry();
		if (selectedEntry.type == Types::MENU_ENTRY) {
			CurrentMenuName = selectedEntry.gotoMenu;
			Selection = 0;

			if (CurrentMenuName == "weapons") {
				MenuCount = MenuWeaponsCount;
			}
			else if (CurrentMenuName == "helpers") {
				MenuCount = MenuHelpersCount;
			}
			else {
				MenuCount = MenuHomeCount;
			}

			SDK->ClearWriteDebugOutput();
		}
		else if (selectedEntry.type == Types::TOGGLE) {
			if (selectedEntry.originalLabel == "") selectedEntry.originalLabel = selectedEntry.label;
			selectedEntry.label = selectedEntry.originalLabel;

			selectedEntry.toggleActive ^= 1;

			if (selectedEntry.toggleActive) selectedEntry.label.append( " ~red~ON~colour~" );

			if (selectedEntry.entityName == "TestFunction") SDK->TestFunction();


			else if (selectedEntry.entityName == "GodMode") {
				godMode ^= 1;

			}
			else if (selectedEntry.entityName == "neverDead") {
				if (selectedEntry.toggleActive == 0) {
					Memory::VP::Patch<char>(0x5A8165, 0x74);
				}
				else {
					Memory::VP::Patch<char>(0x5A8165, 0x75);

				}
					
			}
			else if (selectedEntry.entityName == "freecam") {
				if (selectedEntry.toggleActive == 0) {
					SDK->TeleportToCamera();
				}
				else SDK->SetFreeCamera(true);
			}
		}
		else if (selectedEntry.type == Types::SET_PLAYER_POS) {

			if (selectedEntry.entityName == "Jumpscare") {

				CSDKEntity* player = SDK->GetEntity("player(player)");

				CSDKVector3 pos;

				pos.x = -17.1411;
				pos.y = 6.69318;
				pos.z = 26.8479;

				SDK->MoveEntity(player, pos);
			}
		}
		else if (selectedEntry.type == Types::TRIGGER) {
			if (selectedEntry.entityName == "spawn") {
				printf("spawn");
				SDK->SpawnHunterNearByPlayer("TVLoonie01(hunter)");
			}

		}
		else if (selectedEntry.type == Types::WEAPON) {
			SDK->Spawn(selectedEntry.id, selectedEntry.needAmmo, selectedEntry.entityName.c_str());
			/*
			CEntity* tmp = SDK->GetEntityInstance(selectedEntry.entityName);

			char buffer[256];
			sprintf(buffer, " PTR: %X", tmp);
			SDK->WriteDebug(21, buffer);

			
			std::ofstream ofs("debug.txt");
			ofs.bad();
			ofs << "PTR + i = " << buffer << "\n";
			ofs.close();
		

			Sleep(5000);
			*/

		}

		NavigationChanged = true;
	}

	if (NavigationChanged) {

		CurrentStart = CurrentPage * MENU_ENTRIES_PER_PAGE;
	
		//create a pagination loop
		//if (CurrentPage >= MenuPages) CurrentPage = 0;
		//if (CurrentPage < 0) CurrentPage = MenuPages;

		//create a selection loop
		if (Selection >= MENU_ENTRIES_PER_PAGE || Selection >= MenuCount) Selection = 0;
		if (Selection < 0) {
			if (MenuCount > MENU_ENTRIES_PER_PAGE) {
				Selection = MENU_ENTRIES_PER_PAGE - 1; // - 1 because we start at zero
			}
			else {
				Selection = MenuCount - 1;  // - 1 because we start at zero

			}
		}

	}

}

void CMenu::PrintMenu() {

	//loop over the elements
	for (int i = 0; i < MENU_ENTRIES_PER_PAGE; i++)
	{
		// we can not go over the limit
		if (CurrentStart + i >= MenuCount) break;
		

		// Build the label 
		std::string label;
		if (i == Selection) label.append("~right~");
		else label.append("   ");


		if (CurrentMenuName == "weapons") {
			label.append(MenuWeapons[CurrentStart + i].label);
		}else if (CurrentMenuName == "helpers") {
			label.append(MenuHelpers[CurrentStart + i].label);
		} else {
			label.append(MenuHome[CurrentStart + i].label);
		}

		int missed = 20 - label.length();
		for (int i = 0; i <= missed; i++) {
			label.append(" ");
		}

		SDK->WriteDebug(i, label.c_str());

	}



}

MenuEntry& CMenu::GetSelectedEntry() {

	if (CurrentMenuName == "weapons") {
		return MenuWeapons[CurrentStart + Selection];
	}else if (CurrentMenuName == "helpers") {
		return MenuHelpers[CurrentStart + Selection];
	}else {
		return MenuHome[CurrentStart + Selection];
	}
}


