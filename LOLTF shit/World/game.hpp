#pragma once
#include <dwmapi.h>
#include "../imgui/imgui_internal.h"
#include <stdio.h>
#include "../Includes/settings.h"
#include "../Includes/sdk.hpp"
#include "../Gui/gui.h"
#include <string>
#include "../Includes/sdk.hpp"
#include "../Includes/includes.hpp"
#include "../aimbot/aimbot.h"
#include "../Gui/gui.h"
#include "../Includes/includes.hpp"
#include "../Includes/overlay.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx9.h"
#include "offsets.h"
#include "../Includes/Word.h"


DWORD_PTR Uworlds;
DWORD_PTR LocalPawns;
DWORD_PTR PlayerStates;
DWORD_PTR Localplayers;
DWORD_PTR Rootcomps;
DWORD_PTR PlayerControllers;
DWORD_PTR Persistentlevels;
DWORD_PTR Ulevels;
Vector3 lactorpossssition;

namespace Identifier {

	HANDLE DRIVERHANDLE;
	uint64_t ADDRESS;
	int PID;
}

std::string decrypt_fname(int key) {
	uint64_t NamePoolChunk = Rpm<uint64_t>(base_address + 0x1036B740 + (8 * (uint32_t)((int)(key) >> 16)) + 16) + (unsigned int)(4 * (uint16_t)key);
	uint16_t nameEntry = Rpm<uint16_t>(NamePoolChunk);
	char buff[1024];

	int nameLength = nameEntry >> 6;

	if ((uint32_t)nameLength)
	{
		for (int x = 0; x < nameLength; ++x)
		{
			buff[x] = Rpm<char>(NamePoolChunk + 4 + x);

		}

		char* v2; // rdi
		int v4; // ebx
		int v5; // edx
		int v6; // ecx
		int v7; // ecx
		__int16 v8; // ax

		v2 = buff;
		v4 = nameLength;
		v8 = Rpm<_QWORD>(base_address + 0x102C3168);
		v5 = 0;
		v6 = 38;
		if (v4)
		{
			do
			{
				v7 = v5++ | v6;
				v8 = v7;
				v6 = 2 * v7;
				*v2++ ^= ~v8;
			} while (v5 < v4);
		}

		buff[nameLength] = '\0';
		return std::string(buff);
	}
	else {
		return "";
	}
}

std::string FNAME(int key) {
	uint64_t NamePoolChunk = Rpm<uint64_t>(base_address + 0x1036B740 + (8 * (uint32_t)((int)(key) >> 16)) + 16) + (unsigned int)(4 * (uint16_t)key);
	if (Rpm<uint16_t>(NamePoolChunk) < 64)
	{
		auto a1 = Rpm<DWORD>(NamePoolChunk + 4);
		return decrypt_fname(a1);
	}
	else
	{
		return decrypt_fname(key);
	}
}


bool IsHoldingAssaultRifle(std::string WeaponName) {
	if (WeaponName == "Combat Assault Rifle" ||
		WeaponName == "Assault Rifle  " ||
		WeaponName == "Light Machine Gun" ||
		WeaponName == "Scoped Assault Rifle" ||
		WeaponName == "Makeshift Rifle" ||
		WeaponName == "Sideways Rifle" ||
		WeaponName == "Heavy Assault Rifle" ||
		WeaponName == "Infantry Rifle" ||
		WeaponName == "Suppressed Assault Rifle" ||
		WeaponName == "Ranger Assault Rifle" ||
		WeaponName == "Burst Assault Rifle" ||
		WeaponName == "Primal Rifle" ||
		WeaponName == "Striker Burst Rifle" ||
		WeaponName == "Tactical Assault Rifle" ||
		WeaponName == "Sideways Minigun" ||
		WeaponName == "Burst Pulse Rifle" ||
		WeaponName == "Jules' Drum Gun" ||
		WeaponName == "Brutus' Minigun" ||
		WeaponName == "Spire Guardian's Primal Assault Rifle" ||
		WeaponName == "Drum Gun" ||
		WeaponName == "Shadow Midas' Drum Gun" ||
		WeaponName == "MK-Seven Assault Rifle" ||
		WeaponName == "Slone's Burst Assault Rifle" ||
		WeaponName == "Thermal Scoped Assault Rifle" ||
		WeaponName == "Skye's Assault Rifle" ||
		WeaponName == "Minigun" ||
		WeaponName == "Meowscle's Peow Peow Rifle" ||
		WeaponName == "Slone's Pulse Rifle" ||
		WeaponName == "Combat Assault Rifle" ||
		WeaponName == "Ocean's Burst Assault Rifle")
		return true;

	return false;
}

bool IsHoldingShotgun(std::string WeaponName) {
	if (WeaponName == "Lever Action Shotgun" ||
		WeaponName == "Combat Shotgun" ||
		WeaponName == "Striker Pump Shotgun" ||
		WeaponName == "Tactical Shotgun" ||
		WeaponName == "Ranger Shotgun" ||
		WeaponName == "Primal Shotgun" ||
		WeaponName == "Pump Shotgun" ||
		WeaponName == "Auto Shotgun" ||
		WeaponName == "Charge Shotgun" ||
		WeaponName == "Drum Shotgun" ||
		WeaponName == "Dragon's Breath Shotgun" ||
		WeaponName == "Spire Assassin's Primal Shotgun" ||
		WeaponName == "Kit's Charge Shotgun")
		return true;

	return false;
}

bool IsHoldingSMG(std::string WeaponName) {
	if (WeaponName == "Combat SMG" ||
		WeaponName == "Burst SMG" ||
		WeaponName == "Primal SMG" ||
		WeaponName == "Tactical Submachine Gun" ||
		WeaponName == "Rapid Fire SMG" ||
		WeaponName == "Suppressed Submachine Gun" ||
		WeaponName == "Makeshift Submachine Gun" ||
		WeaponName == "Compact SMG" ||
		WeaponName == "Kymera Ray Gun" ||
		WeaponName == "Zyg and Choppy's Ray Gun")
		return true;

	return false;
}

bool IsHoldingPistol(std::string WeaponName) {
	if (WeaponName == "Hand Cannon" ||
		WeaponName == "Sidearm Pistol" ||
		WeaponName == "Revolver" ||
		WeaponName == "Scoped Revolver" ||
		WeaponName == "Dual Pistols" ||
		WeaponName == "Suppressed Pistol" ||
		WeaponName == "Flint-Knock Pistol" ||
		WeaponName == "Tactical Pistol")
		return true;

	return false;
}

bool IsHoldingSniper(std::string WeaponName) {
	if (WeaponName == "Storm Scout" ||
		WeaponName == "Dragon's Breath Sniper" ||
		WeaponName == "Boom Sniper Rifle" ||
		WeaponName == "Storm Scout Sniper Rifle" ||
		WeaponName == "Hunter Bolt-Action Sniper" ||
		WeaponName == "Rail Gun" ||
		WeaponName == "Heavy Sniper Rifle" ||
		WeaponName == "Suppressed Sniper Rifle" ||
		WeaponName == "Bolt-Action Sniper Rifle" ||
		WeaponName == "Lever Action Rifle" ||
		WeaponName == "Automatic Sniper Rifle" ||
		WeaponName == "Semi-Auto Sniper Rifle   ")
		return true;

	return false;
}

std::string GetPlayerName(__int64 PlayerState)
{
	__int64 FString = Rpm<__int64>(PlayerState + 0xac0);
	int Length = Rpm<int>(FString + 16i64);
	__int64 v6 = Length; // rbx
	if (!v6) return std::string("");
	uintptr_t FText = Rpm<__int64>(FString + 8);

	wchar_t* NameBuffer = new wchar_t[Length];
	ReadMemoryFromKernel(KM_PID, FText, NameBuffer, (Length * 2));

	char v21; // al
	int v22; // r8d
	int i; // ecx
	int v25; // eax
	_WORD* v23;

	v21 = v6 - 1;
	if (!(_DWORD)v6)
		v21 = 0;
	v22 = 0;
	v23 = (_WORD*)NameBuffer;
	for (i = (v21) & 3; ; *v23++ += i & 7)
	{
		v25 = v6 - 1;
		if (!(_DWORD)v6)
			v25 = 0;
		if (v22 >= v25)
			break;
		i += 3;
		++v22;
	}

	std::wstring Temp{ NameBuffer };
	return std::string(Temp.begin(), Temp.end());
}

void game_loop()
{
	CamewaDescwipsion TempCamera = UndetectedCamera(pointer::root_component);

	gui::render();

	if (LeProxy::settings::prediction)
		ImGui::GetBackgroundDrawList()->AddText(bold_segu, 30, ImVec2(200, 200), ImColor(0.60f, 0.60f, 0.60f, 0.70f), "Prediction");

	if (LeProxy::settings::show_fov)
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(Width / 2, Height / 2), (LeProxy::settings::fov * center_x / TempCamera.FieldOfView) / 4, ImColor(0, 0, 0, 255), 2000, 0.9f);

	pointer::uworld = Rpm<uintptr_t>(baseaddy + offsets::Uworld);
	pointer::game_instance = Rpm<uintptr_t>(pointer::uworld + offsets::OwningGameInstance);
	pointer::local_players = Rpm<uintptr_t>(Rpm<uintptr_t>(pointer::game_instance + 0x38));
	pointer::player_controller = Rpm<uintptr_t>(pointer::local_players + 0x30);
	pointer::local_pawn = Rpm<uintptr_t>(pointer::player_controller + offsets::AcknowledgedPawn);
	pointer::root_component = Rpm<uintptr_t>(pointer::local_pawn + offsets::RootComponent);
	pointer::player_state = Rpm<uintptr_t>(pointer::local_pawn + offsets::PlayerState);
	pointer::game_state = Rpm<uintptr_t>(pointer::uworld + offsets::GameState);
	pointer::player_array = Rpm<uintptr_t>(pointer::game_state + offsets::PlayerArray);
	pointer::AFortPlayerState = Rpm<uint64_t>(pointer::local_pawn + offsets::PlayerState);
	pointer::local_relative_location = Rpm<Vector3>(pointer::root_component + offsets::RelativeLocation);

	int count = Rpm<int>(pointer::game_state + (0x2A0 + sizeof(uintptr_t)));
	for (int i = 0; i < count; i++)
	{
		uintptr_t current_player_state = Rpm<uintptr_t>(pointer::player_array + (i * sizeof(uintptr_t)));
		if (!current_player_state) continue;
		std::cout << current_player_state;
		int my_team_id = Rpm<int>(pointer::player_state + offsets::TeamID); //TeamIndex
		int current_actor_team_id = Rpm<int>(current_player_state + offsets::TeamID); //TeamIndex

		uintptr_t current_local_pawn_private = Rpm<uintptr_t>(current_player_state + 0x300);
		if (!current_local_pawn_private) continue;
		if (current_local_pawn_private == pointer::local_pawn) continue;

		INT32 PlayerID = Rpm<int>(pointer::local_pawn + 0x18);
		INT32 ObjectID = Rpm<int>(current_local_pawn_private + 0x18);
		if (!ObjectID || ObjectID == PlayerID)
			continue;

		std::string ActorFName = FNAME(ObjectID);

		uintptr_t current_mesh = Rpm<uintptr_t>(current_local_pawn_private + offsets::mesh);
		if (!current_mesh) continue;
		std::cout << "current_mesh: " << current_mesh;
		if (LeProxy::settings::WeaponESP) {
			uintptr_t current_weapon = Rpm<uintptr_t>(pointer::local_pawn + offsets::CurrentWeapon);
			if (current_weapon) {
				uintptr_t weapon_data = Rpm<uintptr_t>(current_weapon + offsets::WeaponData);
				if (weapon_data) {
					uintptr_t DisplayName = Rpm<uintptr_t>(WeaponData + 0x90);
					uint32_t WeaponLength = Rpm<uint32_t>(DisplayName + 0x38);
					wchar_t* WeaponName = new wchar_t[uintptr_t(WeaponLength) + 1];
					std::wstring wWeaponName(WeaponName);
					std::string InventoryWeapon(wWeaponName.begin(), wWeaponName.end());
					if (!InventoryWeapon.empty() || InventoryWeapon.length() <= FLT_MAX) {
						if (IsHoldingAssaultRifle(InventoryWeapon))
							std::cout << "IsHoldingAssaultRifle" << std::endl;
						else if (IsHoldingShotgun(InventoryWeapon))
							std::cout << "IsHoldingShotgun" << std::endl;
						else if (IsHoldingSMG(InventoryWeapon))
							std::cout << "IsHoldingSMG" << std::endl;
						else if (IsHoldingPistol(InventoryWeapon))
							std::cout << "IsHoldingPistol" << std::endl;
						else if (IsHoldingSniper(InventoryWeapon))
							std::cout << "IsHoldingSniper" << std::endl;
					}
				}
			}

		}

		if (strstr(ActorFName.c_str(), "PlayerPawn_Athena_Phoebe_C") || strstr(ActorFName.c_str(), "BP_PlayerPawn") || strstr(ActorFName.c_str(), "PlayerPawn_Athena_C")) {
			std::cout << " egebe is men omg fortnite vbuckl" << std::endl;
		}

		if (LeProxy::settings::bIgnoreHidden) {
			if (IsVisible(current_mesh))
				continue;
		}

		if (LeProxy::settings::bIgnoreTeam) {
			if (my_team_id == current_actor_team_id)
				continue;
		}

		if (LeProxy::settings::bIgnoreBots) {
			bool IsBot = Rpm<BYTE>(current_player_state + 0x292);
			if (!IsBot)
				continue;
		}

		if (LeProxy::settings::bIgnoreDead) {
			bool bIsDyingasd = (Rpm<BYTE>(current_local_pawn_private + 0x710) & 0x10);
			bool isDBNO = (Rpm<BYTE>(current_local_pawn_private + 0x832) >> 4) & 1; // (Rpm<BYTE>(current_local_pawn_private + 0x832) & 0x10);
			if (isDBNO || bIsDyingasd)
				continue;
		}

		Vector3 head3d = GetBoneWithRotation(current_mesh, 106);
		Vector3 head2d = ProjectWorldToScreen(head3d);
		Vector3 bottom3d = GetBoneWithRotation(current_mesh, 88); // 0
		Vector3 bottom2d = ProjectWorldToScreen(bottom3d);
		Vector3 Headbox = ProjectWorldToScreen(Vector3(head3d.x, head3d.y, head3d.z + 19));
		Vector3 Rootbox = ProjectWorldToScreen(Vector3(bottom3d.x, bottom3d.y, bottom3d.z - 10));

		double distance = pointer::local_relative_location.Distance(bottom3d) / 100;

		if (IsInScreen(bottom2d))
		{

			auto ColorBox = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			auto ColorSkeleton = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			auto ColorSnapline = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

			if (IsVisible(current_mesh))
			{
				if (my_team_id != current_actor_team_id)
					ColorBox = ImVec4(LeProxy::settings::color::TeamboxVisible[0], LeProxy::settings::color::TeamboxVisible[1], LeProxy::settings::color::TeamboxVisible[2], 1.0f);
				else if (my_team_id == current_actor_team_id)
					ColorBox = ImVec4(LeProxy::settings::color::PlayerboxVisible[0], LeProxy::settings::color::PlayerboxVisible[1], LeProxy::settings::color::PlayerboxVisible[2], 1.0f);

				ColorSkeleton = ImVec4(LeProxy::settings::color::SkeletonVisible[0], LeProxy::settings::color::SkeletonVisible[1], LeProxy::settings::color::SkeletonVisible[2], 1.0f);
				ColorSnapline = ImVec4(LeProxy::settings::color::SnaplinesVisible[0], LeProxy::settings::color::SnaplinesVisible[1], LeProxy::settings::color::SnaplinesVisible[2], 1.0f);
			}
			else
			{
				if (my_team_id != current_actor_team_id)
					ColorBox = ImVec4(LeProxy::settings::color::PlayerboxNotVisible[0], LeProxy::settings::color::PlayerboxNotVisible[1], LeProxy::settings::color::PlayerboxNotVisible[2], 1.0f);
				else if (my_team_id == current_actor_team_id)
					ColorBox = ImVec4(LeProxy::settings::color::TeamboxNotVisible[0], LeProxy::settings::color::TeamboxNotVisible[1], LeProxy::settings::color::TeamboxNotVisible[2], 1.0f);

				ColorSkeleton = ImVec4(LeProxy::settings::color::SkeletonNotVisible[0], LeProxy::settings::color::SkeletonNotVisible[1], LeProxy::settings::color::SkeletonNotVisible[2], 1.0f);
				ColorSnapline = ImVec4(LeProxy::settings::color::SnaplinesNotVisible[0], LeProxy::settings::color::SnaplinesNotVisible[1], LeProxy::settings::color::SnaplinesNotVisible[2], 1.0f);
			}
			if (jump) {

				Wpm<float>(pointer::local_pawn + 0x1C80, 150.0f); // Increase movement speed
				Wpm<bool>(pointer::local_pawn + 0xB35, 0); // Disable targeting mode
				Wpm<float>(pointer::local_pawn + 0x2058, .001); // Instant revive from DBNO state
				Wpm<float>(pointer::local_pawn + 0x1BF8, .001);
				Wpm<float>(pointer::local_pawn + 0x2010, .001); // Instant Revive
				Wpm<float>(pointer::local_pawn + 0x168, 100.0f); // Increase network update frequency
				Wpm<float>(pointer::local_pawn + 0x60, .001); // Reduce character lifespan
				Wpm<float>(pointer::local_pawn + 0x28, 0.1f); // Slow motion
				uintptr_t currentVehicle = Rpm<uintptr_t>(pointer::local_pawn + 0x2488);
				if (GetAsyncKeyState(VK_SPACE)) {
					Wpm<char>(currentVehicle + 0x2498, 1);
				}
				uint64_t aba = Rpm<float>(pointer::local_pawn + 0x1BBA); // Super Acceleration

				Wpm<float>(pointer::local_pawn + 0x1BBA, 10000.0f); // Super Acceleration
				Wpm<float>(pointer::local_pawn + 0x1F24, 10000.0f); // Super Launch Speed
				Wpm<float>(pointer::local_pawn + 0x324C, 10.0f);
				Wpm<bool>(pointer::local_pawn + 0x1C8F, 1); // Always skydiving

				uint64_t  caca = Rpm<float>(pointer::local_pawn + 0x324C);
				Wpm<bool>(pointer::local_pawn + 0x363D, true); // Enable DBNO Carry Enemies
				Wpm<float>(pointer::local_pawn + 0x3638, 1000.0f); // Super Carried Player Drop Trace Height
				Wpm<float>(pointer::local_pawn + 0x1B98, 0.0f); // VehicleInputStateReliable
				Wpm<float>(pointer::local_pawn + 0x1BFC, 0.0f); // MinimumTimeBetweenSteps for speedi
				// removed this bc it was useless (just wepondata)
				Wpm<bool>(pointer::local_pawn + 0x1C84, false);  // bIsInWaterVolume
				Wpm<int>(pointer::local_pawn + 0x1C8D, 5); //  BalloonActiveCount
				Wpm<float>(pointer::local_pawn + 0x1B98, 0.0f); // VehicleInputStateReliable
				Wpm<float>(pointer::local_pawn + 0x1BFC, 0.0f); // MinimumTimeBetweenSteps


			}
			if (LeProxy::settings::box)
			{
				float BoxHeight = Rootbox.y - Headbox.y;
				float BoxWidth = BoxHeight / 1.9f;
				box_esp(4, 4, Rootbox.x - (BoxWidth / 2), Headbox.y,
					BoxWidth, BoxHeight, ImColor(255, 255, 255), 1.f,
					LeProxy::settings::fill, LeProxy::settings::outline);
			}
			else if (LeProxy::settings::cornered_box)
			{
				float BoxHeight = Rootbox.y - Headbox.y;
				float BoxWidth = BoxHeight / 1.9f;
				corner_esp(4, 4, Rootbox.x - (BoxWidth / 2), Headbox.y,
					BoxWidth, BoxHeight, ImGui::GetColorU32(ColorBox), 1.f,
					LeProxy::settings::fill, LeProxy::settings::outline);
			}
			else if (LeProxy::settings::threed)
			{
				Vector3 headrender = Vector3(Headbox.x, Headbox.y, Headbox.z - 7);
				ThreeD_Box(false, 40, 2.0f, ImGui::GetColorU32(ColorBox), Rootbox, Headbox.z);
			}

			if (LeProxy::settings::distance)
			{
				std::string text_distance = "(" + std::to_string(distance) + "m)";
				ImVec2 text_size = ImGui::CalcTextSize(text_distance.c_str());
				ADrawText(FN, ImVec2(Headbox.x - (text_size.x / 2), Headbox.y - 20), ImColor(255, 255, 255), text_distance.c_str(), LeProxy::settings::size, false);
			}

			if (LeProxy::settings::WeaponESP)
			{
				// Ading this later
			}

			if (LeProxy::settings::name)
			{
				// Wating for renox
				std::string name_buff = GetPlayerName(current_player_state);
				if (!name_buff.empty() || name_buff.length() < FLT_MAX) {
					ImVec2 text_size = ImGui::CalcTextSize(name_buff.c_str());
					ADrawText(FN, ImVec2(Rootbox.x - (text_size.x / 2), Rootbox.y + 10), ImColor(255, 255, 255), name_buff.c_str(), LeProxy::settings::size, false);
				}
			}

			if (LeProxy::settings::gayskeleton)
			{
				SkeletonESP(current_mesh, ImGui::GetColorU32(ColorSkeleton), LeProxy::settings::fingy);
			}

			if (LeProxy::settings::line)
			{
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center_x, Height), ImVec2(bottom2d.x, bottom2d.y), ImColor(255, 255, 255), 0.5f);
			}

		}

		if (LeProxy::settings::bWeapon) {
			uintptr_t Weapon = Rpm<uintptr_t>(pointer::local_pawn + offsets::CurrentWeapon);
			if (!Weapon)
				continue;
		}

		Vector3 rootHeadOut = { Vector3(0, 0, 0) };
		static int BindedKeybind = VK_RBUTTON;

		if (LeProxy::settings::hitbox == 0) {
			Vector3 rootHead = GetBoneWithRotation(current_mesh, 106);
			rootHeadOut = ProjectWorldToScreen(rootHead);
		}
		else if (LeProxy::settings::hitbox == 1) {
			Vector3 rootHead = GetBoneWithRotation(current_mesh, 66);
			rootHeadOut = ProjectWorldToScreen(rootHead);
		}
		else if (LeProxy::settings::hitbox == 2) {
			Vector3 rootHead = GetBoneWithRotation(current_mesh, 7);
			rootHeadOut = ProjectWorldToScreen(rootHead);
		}

		if (LeProxy::settings::bAimbot)
		{
			if (GetAsyncKeyState(BindedKeybind)) {
				if ((int)rootHeadOut.x != 0 && (int)rootHeadOut.y != 0) {
					if (bIsInRectangle(center_x, center_y, (float)(LeProxy::settings::fov * center_x / TempCamera.FieldOfView), rootHeadOut.x, rootHeadOut.y)) {
						if (GetDistance(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z, center_x, center_y) <= LeProxy::settings::fov) {
							mouse(rootHeadOut.x, rootHeadOut.y, LeProxy::settings::smoothness);
							if (LeProxy::settings::Aimline) {
								ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center_x, center_y), ImVec2(rootHeadOut.x, rootHeadOut.y), ImColor(255, 0, 0), 0.5f);
							}
						}
					}
				}
			}
		}

		if (LeProxy::settings::triggerbot)
		{
			if (IsVisible(current_mesh)) {
				if ((int)rootHeadOut.x != 0 && (int)rootHeadOut.x != 0) {
					if (bIsInRectangle(center_x, center_y, (float)(LeProxy::settings::fov * center_x / TempCamera.FieldOfView), rootHeadOut.x, rootHeadOut.y)) {
						if (GetDistance(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z, center_x, center_y) <= LeProxy::settings::fov) {
							mouse_event(MOUSEEVENTF_LEFTDOWN, DWORD(NULL), DWORD(NULL), DWORD(0x0002), ULONG_PTR(NULL));
							mouse_event(MOUSEEVENTF_LEFTUP, DWORD(NULL), DWORD(NULL), DWORD(0x0004), ULONG_PTR(NULL));
						}
					}
				}
			}
		}
	}
}

VOID World()
{

	while (true)
	{
		ImDrawList* Draw = ImGui::GetBackgroundDrawList();

		uintptr_t levels_array = Rpm<uintptr_t>(pointer::uworld + 0x170);// iterating uworld->ulevels

		if (levels_array)
		{

			for (auto i = 0UL; i < Rpm<DWORD>(pointer::uworld + (0x170 + sizeof(PVOID))); ++i)
			{
				if (i >= Rpm<int>(pointer::uworld + 0x178))
					break;

				uintptr_t persistent_level = Rpm<uintptr_t>(levels_array + (i * sizeof(uintptr_t)));

				if (persistent_level)
				{
					if (Rpm<int>(persistent_level + 0xA0) <= 0x2328)
					{
						for (int j = 0; Rpm<DWORD>(persistent_level + (0xA0 + sizeof(PVOID))); ++j)
						{
							if (j >= Rpm<int>(persistent_level + 0xA0))
								break;

							uintptr_t actor_array = Rpm<uintptr_t>(persistent_level + 0x98);
							if (actor_array)
							{
								uintptr_t actor_addr = Rpm<uintptr_t>(actor_array + (j * sizeof(uintptr_t)));
								if (actor_addr)
								{
									uintptr_t actor_rootcomponent = Rpm<uintptr_t>(offsets::RootComponent + actor_addr);
									if (actor_rootcomponent)
										break;

									Vector3 Position = Rpm<Vector3>(actor_rootcomponent + 0x128);
									Vector3 ScreenPosition = ProjectWorldToScreen(Position);

									INT32 objectID = Rpm<int>(actor_addr + 0x18);
									std::string actor_fname = FNAME(objectID);

									if (LeProxy::settings::loot)
									{

										/*
										if (strstr(actor_fname.c_str(), "Tiered_Chest"))
										{
										*/

										std::string DisplayName = "Chest";
										auto Size = ImGui::CalcTextSize(DisplayName.c_str());
										int ScreenX = ScreenPosition.x - (Size.x / 2);
										int ScreenY = ScreenPosition.y;

										Draw->AddText(ImVec2(ScreenX, ScreenY), ImColor(255, 255, 255), DisplayName.c_str());
										Draw->AddLine(ImVec2(center_x, center_y), ImVec2(ScreenPosition.x, ScreenPosition.y + 14), ImColor(255, 255, 255), 1.f);
									}

									if (LeProxy::settings::testing) {
										if (strstr(actor_fname.c_str(), "B_Prj_Bullet_Cosmos_AR_C") ||
											strstr(actor_fname.c_str(), "B_Prj_Bullet_Sniper_Heavy_C") ||
											strstr(actor_fname.c_str(), "B_Prj_Bullet_DMR_C") ||
											strstr(actor_fname.c_str(), "B_Prj_Bullet_Sniper_C") ||
											strstr(actor_fname.c_str(), "B_Prj_Bullet_Sniper")) {

											std::string text_bullet = "Bullet nigga";
											ImVec2 Size = ImGui::CalcTextSize(text_bullet.c_str());
											int ScreenX = ScreenPosition.x - (Size.x / 2);
											int ScreenY = ScreenPosition.y;

											Draw->AddText(ImVec2(ScreenX, ScreenY), ImColor(255, 255, 255), text_bullet.c_str());

										}

									}
								}
							}

						}
					}
				}
			}

		}

		//	uint64_t CurrentWeapon = Rpm<uintptr_t>(pointer::local_pawn + offsets::CurrentWeapon);
		//	// std::cout << " CurrentWeapon " << CurrentWeapon << std::endl;
		//	if (CurrentWeapon)
		//		continue;

		//	uintptr_t WeaponData = Rpm<uintptr_t>(CurrentWeapon + offsets::WeaponData);
		//	// std::cout << " WeaponData " << WeaponData << std::endl;
		//	if (!WeaponData)
		//		continue;

		//	uintptr_t DisplayName = Rpm<uintptr_t>(WeaponData + 0x90);
		//	// std::cout << " DisplayName " << DisplayName << std::endl;
		//	if (!DisplayName)
		//		continue;

		//	int Tier = Rpm<BYTE>(WeaponData + 0x73); // DisplayTier 0xbfe
		//	uint32_t WeaponLength = Rpm<uint32_t>(DisplayName + 0x38);
		//	wchar_t* WeaponName = new wchar_t[uintptr_t(WeaponLength) + 1];
		//	std::wstring wWeaponName(WeaponName);
		//	std::string InventoryWeapon(wWeaponName.begin(), wWeaponName.end());

		//	for (unsigned long x = 0; x <= WeaponLength; x++)
		//	{
		//		uintptr_t WorldLevels = Rpm<uintptr_t>(fn::gl + 0x170); // levels
		//		// std::cout << " WorldLevels " << WorldLevels << std::endl;
		//		if (!WorldLevels)
		//			continue;

		//		uintptr_t ItemLevels = Rpm<uintptr_t>(WorldLevels + (x * sizeof(uintptr_t)));
		//		// std::cout << " ItemLevels " << ItemLevels << std::endl;
		//		if (!ItemLevels)
		//			continue;

		//		for (unsigned long a = 0; a < Rpm<DWORD>(ItemLevels + (0x98 + sizeof(PVOID))); ++a)
		//		{
		//			uintptr_t ItemsPawns = Rpm<uintptr_t>(ItemLevels + 0x98);
		//			// std::cout << " ItemsPawns " << ItemsPawns << std::endl;
		//			if (!ItemsPawns)
		//				continue;

		//			uintptr_t CurrentActor = Rpm<uintptr_t>(ItemsPawns + (a * sizeof(uintptr_t)));
		//			// std::cout << " CurrentActor " << CurrentActor << std::endl;
		//			if (!CurrentActor)
		//				continue;

		//			INT32 ObjectID = Rpm<INT32>(CurrentActor + 0x18);
		//			// std::cout << " ObjectID " << ObjectID << std::endl;
		//			if (!ObjectID)
		//				continue;

		//			std::string ItemFName = find_object_name(ObjectID);
		//			if (ItemFName == "") continue;

		//			// Basic Object names
		//			if (ItemFName.find("Tiered_Chest") != std::string::npos ||
		//				ItemFName.find("Tiered_Ammo") != std::string::npos ||
		//				ItemFName.find("FortPickupAthena") != std::string::npos ||
		//				ItemFName.find("AthenaSupplyDrop_Llama") != std::string::npos ||
		//				ItemFName.find("AthenaSupplyDrop_C") != std::string::npos ||
		//				ItemFName.find("Valet_BasicCar_") != std::string::npos ||
		//				ItemFName.find("BGA_Athena_FlopperSpawn_World_C") != std::string::npos ||
		//				ItemFName.find("CBGA_ShieldsSmall_C") != std::string::npos ||
		//				ItemFName.find("Athena_Prop_SilkyBingo_C") != std::string::npos)
		//			{

		//				BOOL bHidden = ((Rpm<int>(CurrentActor + 0x58) >> 7) & 1);
		//				BOOL bPickedUp = Rpm<BOOL>(CurrentActor + 0x5c8);
		//				FLOAT DespawnTime = Rpm<FLOAT>(CurrentActor + 0x720);
		//				FColor ItemColor;

		//				if (!bHidden && !bPickedUp)
		//					continue;

		//				uint64_t RootComponent = Rpm<uintptr_t>(CurrentActor + fn::offsets::RootComponent);
		//				fn::fvector RelativeLocation = Rpm <fn::fvector>(RootComponent + fn::offsets::RelativeLocation);
		//				double ItemDistance = VirtualCamera.Location.Distance(RelativeLocation);
		//				fn::fvector ScreenPosition = w2s(RelativeLocation);

		//				switch (Tier)
		//				{
		//				case 0: // Invalid
		//					ItemColor.R = 0;
		//					ItemColor.G = 0;
		//					ItemColor.B = 0;
		//					break;
		//				case 1: // Common
		//					ItemColor.R = 129;
		//					ItemColor.G = 137;
		//					ItemColor.B = 145;
		//					break;
		//				case 2: // Uncommon
		//					ItemColor.R = 115;
		//					ItemColor.G = 175;
		//					ItemColor.B = 57;
		//					break;
		//				case 3: // Rare
		//					ItemColor.R = 111;
		//					ItemColor.G = 171;
		//					ItemColor.B = 54;
		//					break;
		//				case 4: // Epic
		//					ItemColor.R = 141;
		//					ItemColor.G = 62;
		//					ItemColor.B = 188;
		//					break;
		//				case 5: // Legendary
		//					ItemColor.R = 230;
		//					ItemColor.G = 167;
		//					ItemColor.B = 76;
		//					break;
		//				case 6: // Mythic
		//					ItemColor.R = 224;
		//					ItemColor.G = 202;
		//					ItemColor.B = 88;
		//					break;
		//				case 7: // Exotic
		//					ItemColor.R = 132;
		//					ItemColor.G = 211;
		//					ItemColor.B = 178;
		//					break;
		//				default: // Other
		//					ItemColor.R = 254;
		//					ItemColor.G = 255;
		//					ItemColor.B = 255;
		//					break;
		//				}

		//				std::string TextItem = DisplayName + " [" + std::to_string(ItemDistance) + "m]";
		//				ImVec2 ItemSize = ImGui::CalcTextSize(TextItem.c_str());
		//				ImGui::GetOverlayDrawList()->AddLine(ImVec2(ScreenPosition.x, ScreenPosition.y), ImVec2(center_x, Height), ImColor(255, 255, 255), 0.5f);
		//				ImGui::GetOverlayDrawList()->AddText(ImVec2(ScreenPosition.x - (ItemSize.x / 2), ScreenPosition.y), ImColor(ItemColor.R, ItemColor.G, ItemColor.B, 255), TextItem.c_str());

		//				// testing
		//				std::string TextDespawn = "Despawn Time (" + std::to_string(DespawnTime) + ")";
		//				ImVec2 DespawnSize = ImGui::CalcTextSize(TextDespawn.c_str());
		//				ImGui::GetOverlayDrawList()->AddText(ImVec2(ScreenPosition.x - (DespawnSize.x / 2), ScreenPosition.y + 20), ImColor(255, 255, 255), TextDespawn.c_str());

		//				if (settings::WeaponConfigs)
		//				{

		//					if (IsHoldingAssaultRifle(InventoryWeapon))
		//					{
		//						settings::AimFOV = settings::configs::fov_AR;
		//						settings::smooth = settings::configs::smoothness_AR;
		//					}

		//					else if (IsHoldingShotgun(InventoryWeapon))
		//					{
		//						settings::AimFOV = settings::configs::fov_SHOTGUN;
		//						settings::smooth = settings::configs::smoothness_SHOTGUN;
		//					}

		//					else if (IsHoldingSMG(InventoryWeapon))
		//					{
		//						settings::AimFOV = settings::configs::fov_SMG;
		//						settings::smooth = settings::configs::smoothness_SMG;
		//					}

		//					else if (IsHoldingPistol(InventoryWeapon))
		//					{
		//						settings::AimFOV = settings::configs::fov_PISTOL;
		//						settings::smooth = settings::configs::smoothness_PISTOL;
		//					}

		//					else if (IsHoldingSniper(InventoryWeapon))
		//					{
		//						settings::AimFOV = settings::configs::fov_SNIPER;
		//						settings::smooth = settings::configs::smoothness_SNIPER;
		//					}

		//				}
		//			}

		//		}

		//		std::this_thread::sleep_for(std::chrono::milliseconds(800));

		//	}

		//}
	}

}


WPARAM render_loop()
{
	static RECT old_rc;
	ZeroMemory(&messager, sizeof(MSG));
	while (messager.message != WM_QUIT)
	{
		if (PeekMessage(&messager, win, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&messager);
			DispatchMessage(&messager);
		}
		HWND hwnd_active = GetForegroundWindow();
		if (GetAsyncKeyState(VK_END) & 1)
			exit(8);
		if (hwnd_active == game_wnd)
		{
			HWND hwnd_test = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(win, hwnd_test, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		RECT rc;
		POINT xy;
		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(game_wnd, &rc);
		ClientToScreen(game_wnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;
		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = game_wnd;
		io.DeltaTime = 1.0f / 60.0f;
		Width = io.DisplaySize.x;
		Height = io.DisplaySize.y;
		center_x = io.DisplaySize.x / 2;
		center_y = io.DisplaySize.y / 2;
		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;
		if (GetAsyncKeyState(0x1))
		{
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
		{
			io.MouseDown[0] = false;
		}
		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{
			old_rc = rc;
			p_params.BackBufferWidth = Width;
			p_params.BackBufferHeight = Height;
			SetWindowPos(win, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			p_device->Reset(&p_params);
		}

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		game_loop();

		ImGui::EndFrame();

		p_device->SetRenderState(D3DRS_ZENABLE, false);
		p_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		p_device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
		p_device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
		if (p_device->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			p_device->EndScene();
		}
		HRESULT result = p_device->Present(NULL, NULL, NULL, NULL);
		if (result == D3DERR_DEVICELOST && p_device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			p_device->Reset(&p_params);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	cleanup_d3d();
	DestroyWindow(win);
	return messager.wParam;
}

//
//void render_loop()
//{
//	ZeroMemory(&messager, sizeof(MSG));
//
//	while (messager.message != WM_QUIT)
//	{
//
//		if (PeekMessage(&messager, win, 0, 0, PM_REMOVE))
//		{
//			TranslateMessage(&messager);
//			DispatchMessage(&messager);
//		}
//
//		HWND hwnd_active = GetForegroundWindow();
//
//		if (hwnd_active == game_wnd) {
//			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
//			SetWindowPos(win, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
//		}
//
//		RECT rc;
//		POINT xy;
//
//		ZeroMemory(&rc, sizeof(RECT));
//		ZeroMemory(&xy, sizeof(POINT));
//		GetClientRect(game_wnd, &rc);
//		ClientToScreen(game_wnd, &xy);
//		rc.left = xy.x;
//		rc.top = xy.y;
//
//		ImGuiIO& io = ImGui::GetIO();
//		io.IniFilename = NULL;
//		io.ImeWindowHandle = game_wnd;
//		io.DeltaTime = 1.0f / 60.f;
//		center_x = Width / 2;
//		center_y = Height / 2;
//
//		POINT p;
//		GetCursorPos(&p);
//		io.MousePos.x = p.x - xy.x;
//		io.MousePos.y = p.y - xy.y;
//
//		if (GetAsyncKeyState(VK_LBUTTON)) {
//			io.MouseDown[0] = true;
//			io.MouseClicked[0] = true;
//			io.MouseClickedPos[0].x = io.MousePos.x;
//			io.MouseClickedPos[0].x = io.MousePos.y;
//		}
//		else
//			io.MouseDown[0] = false;
//
//		ImGui_ImplDX9_NewFrame();
//		ImGui_ImplWin32_NewFrame();
//		ImGui::NewFrame();
//
//		game_loop();
//
//		ImGui::EndFrame();
//
//		p_device->SetRenderState(D3DRS_ZENABLE, false);
//		p_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
//		p_device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
//		p_device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
//		if (p_device->BeginScene() >= 0)
//		{
//			ImGui::Render();
//			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
//			p_device->EndScene();
//		}
//		HRESULT result = p_device->Present(NULL, NULL, NULL, NULL);
//		if (result == D3DERR_DEVICELOST && p_device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
//		{
//			ImGui_ImplDX9_InvalidateDeviceObjects();
//			p_device->Reset(&p_params);
//			ImGui_ImplDX9_CreateDeviceObjects();
//		}
//	}
//
//	ImGui_ImplDX9_Shutdown();
//	ImGui_ImplWin32_Shutdown();
//	ImGui::DestroyContext();
//	DestroyWindow(win);
//}