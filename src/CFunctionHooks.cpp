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
#include "CFunctionHooks.h"
#include "CNatives.h"
#include "CAntiCheat.h"
#include "CPlayer.h"

#include <sampgdk/a_players.h>

cell AMX_NATIVE_CALL CFunctionHooks::HookedGivePlayerWeapon(AMX* amx, cell* params)
{
	PLAYERID playerID = (PLAYERID)params[1];

	ePlayerData *player;
	if ((player = CAntiCheat::GetPlayerByID(playerID)) == NULL) return NULL;

	player->bHasWeapon[params[2]] = true;
	return sampgdk_GivePlayerWeapon(playerID, params[2], params[3]);
}

cell AMX_NATIVE_CALL CFunctionHooks::HookedResetPlayerWeapons(AMX* amx, cell* params)
{
	PLAYERID playerID = (PLAYERID)params[1];
	ePlayerData *player;
	if ((player = CAntiCheat::GetPlayerByID(playerID)) == NULL) return NULL;

	sampgdk_ResetPlayerWeapons(playerID);

	for (int it = 0; it != MAX_WEAPS; it++)
		player->bHasWeapon[it] = false;

	return true;
}

cell AMX_NATIVE_CALL CFunctionHooks::HookedGivePlayerMoney(AMX* amx, cell* params)
{
	PLAYERID playerID = (PLAYERID)params[1];
	ePlayerData *player;
	if ((player = CAntiCheat::GetPlayerByID(playerID)) == NULL) return NULL;
	int iMoney = (int)params[2];
	player->iPlayerMoney += iMoney;

	return sampgdk_GivePlayerMoney(playerID, iMoney);
}

cell AMX_NATIVE_CALL CFunctionHooks::HookedGetPlayerMoney(AMX* amx, cell* params)
{
	PLAYERID playerID = (PLAYERID)params[1];
	ePlayerData *player;
	if ((player = CAntiCheat::GetPlayerByID(playerID)) == NULL) return NULL;
	return player->iPlayerMoney;
}

cell AMX_NATIVE_CALL CFunctionHooks::HookedResetPlayerMoney(AMX* amx, cell* params)
{
	PLAYERID playerID = (PLAYERID)params[1];
	ePlayerData *player;
	if ((player = CAntiCheat::GetPlayerByID(playerID)) == NULL) return NULL;
	player->iPlayerMoney = 0;
	CPlayer::SetMoney(playerID, 0);
	return true;
}

cell AMX_NATIVE_CALL CFunctionHooks::HookedTogglePlayerSpectating(AMX* amx, cell* params)
{
	PLAYERID playerID = (PLAYERID)params[1];
	bool	 bToggle = !!params[2];
	ePlayerData *player;
	if ((player = CAntiCheat::GetPlayerByID(playerID)) == NULL) return NULL;
	player->bHasPermissionToSpectate = bToggle;
	return true;
}