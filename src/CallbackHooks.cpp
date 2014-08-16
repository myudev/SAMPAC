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
		CAntiCheat::FakeKillCheck(playerid);
		return true;
	}
	return true;
}

bool CallbackHooks::OnPlayerUpdate(int playerid)
{
	if (!CPlayer::IsNPC(playerid)) {
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

bool CallbackHooks::OnPlayerTakeDamage(int playerid, int issuerid, float amount, int weaponid)
{
	if (!CPlayer::IsNPC(playerid)) {
		ePlayerData *player;
		if ((player = CAntiCheat::GetPlayerByID(playerid)) != NULL) {
			if (bIsDetectionEnabled[CHEAT_TYPE_HEALTH_HACK]) {
				if ((player->fHealth -= amount) < 0.0)
					player->fHealth = 0.0;
			}
		}
		return true;
	}
	return true;
}