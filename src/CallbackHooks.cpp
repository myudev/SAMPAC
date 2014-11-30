/*
	PROJECT		<>	SA:MP Anticheat Plug-in
	LICENSE		<>	See LICENSE in the top level directory.
	AUTHOR(S)	<>	MyU (myudev0@gmail.com), Lorenc_ (zeelorenc@hotmail.com)
	PURPOSE		<>  Providing datastructures for the internal SA:MP Server.


	Copyright (C) 2014 SA:MP Anticheat Plug-in.

	The Project is available on https://github.com/myudev/SAMPAC

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include "main.h"
#include "CallbackHooks.h"
#include "CNatives.h"
#include "CAntiCheat.h"
#include "CPlayer.h"

#include <time.h>

bool CallbackHooks::OnPlayerConnect(int playerid)
{
	if (!CPlayer::IsNPC(playerid))
		return CAntiCheat::AddPlayer(playerid);

	return true;
}

bool CallbackHooks::OnPlayerDisconnect(int playerid, int reason)
{
	if (!CPlayer::IsNPC(playerid)) {
		return CAntiCheat::RemovePlayer(playerid);
	}

	return true;
}

bool CallbackHooks::OnPlayerSpawn(int playerid)
{
	if (!CPlayer::IsNPC(playerid))
	{
		ePlayerData *player;
		if ((player = CAntiCheat::GetPlayerByID(playerid)) != NULL) {
			player->pHealth.fPoints = 100.0f;
			player->pArmour.fPoints = 0.0f;
			
			if (bIsDetectionEnabled[CHEAT_TYPE_IMMUNITY])
				CPlayer::SetTeam(playerid, 128); // Must ensure everyone can't shoot eachother for anti-HH/AH

			player->bSpawned = true;
		}
		return true;
	}
	return true;
}

bool CallbackHooks::OnPlayerStateChange(int playerid, int newstate, int oldstate)
{
	if (!CPlayer::IsNPC(playerid)) {
		CAntiCheat::CarWarpCheck(playerid, newstate);
		CAntiCheat::WeaponHackStateFix(playerid, newstate);
		return true;
	}
	return true;
}

bool CallbackHooks::OnPlayerPickUpPickup(int playerid, int pickupid)
{
	if (!CPlayer::IsNPC(playerid)) {
		CAntiCheat::RapidPickupSpam(playerid, pickupid);
		return true;
	}
	return true;
}

bool CallbackHooks::OnPlayerDeath(int playerid, int killerid, int reason)
{
	if (!CPlayer::IsNPC(playerid)) {
		ePlayerData *player;
		if ((player = CAntiCheat::GetPlayerByID(playerid)) != NULL) {
			player->bSpawned = false;
		}
		CAntiCheat::FakeKillCheck(playerid);
		return true;
	}
	return true;
}

bool CallbackHooks::OnPlayerUpdate(int playerid)
{
	if (!CPlayer::IsNPC(playerid)) {
		int iTime = (int)time(NULL); // Store time in a variable once

		ePlayerData *player;
		if ((player = CAntiCheat::GetPlayerByID(playerid)) != NULL) {
			// Health Hack/Armour Hack
			if (bIsDetectionEnabled[CHEAT_TYPE_IMMUNITY]) {
				if (player->bSpawned) {
					CAntiCheat::HealthHackCheck(player->iPlayerID, iTime);
					CAntiCheat::ArmourHackCheck(player->iPlayerID, iTime);
				}
			}
		}
		return true;
	}
	return true;
}

bool CallbackHooks::OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys)
{
	if (!CPlayer::IsNPC(playerid)) {
		return true;
	}
	return true;
}

bool CallbackHooks::OnPlayerRequestClass(int playerid, int classid)
{
	if (!CPlayer::IsNPC(playerid)) {
		ePlayerData *player;
		if ((player = CAntiCheat::GetPlayerByID(playerid)) != NULL) player->iSelectedClass = classid; // Needed to get the class weapons.
		return true;
	}
	return true;
}

bool CallbackHooks::OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid, int bodypart)
{
	logprintf("OnPlayerTakeDamage(%d, %d, %f, %d, %d)", playerid, issuerid, amount, weaponid, bodypart);
	if (!CPlayer::IsNPC(playerid)) 
	{
		if (bIsDetectionEnabled[CHEAT_TYPE_IMMUNITY])
		{
			ePlayerData *player;
			if ((player = CAntiCheat::GetPlayerByID(playerid)) != NULL) 
			{
				float
					fHealth = player->pHealth.fPoints, //CPlayer::GetHealth(playerid),
					fArmour = player->pHealth.fPoints  //CPlayer::GetArmour(playerid)
				;

				if (issuerid != INVALID_PLAYER_ID)
				{
					float tmp;
					float tmp_amount = amount;

					if (fArmour) {
						if ((tmp = fArmour - tmp_amount) < 0.0)  {
							tmp_amount -= fArmour;
							fArmour = 0.0;
						}
						else  {
							fArmour = tmp;
							tmp_amount = 0.0;
						}
					}

					if ((fHealth -= tmp_amount) < 0.0) {
						fHealth = 0.0;
					}
					
					CPlayer::SetHealth(playerid, fHealth);
					CPlayer::SetArmour(playerid, fArmour);

					if (fHealth <= 0.0 && player->bSpawned) {
						// Call death server-sided
						logprintf("[ACDEATH] %d has been killed by %d (reason %d)", playerid, issuerid, weaponid);
					}
				}
				else
				{
					if ((player->pHealth.fPoints -= amount) < 0.0)
						player->pHealth.fPoints = 0.0;

					if ((fHealth - amount) <= 0.0 && player->bSpawned) {
						logprintf("[ACDEATH] %d has been killed themselves.", playerid);
						// Call death server-sided
					}
				}
			}
		}
	}
	return false;
}