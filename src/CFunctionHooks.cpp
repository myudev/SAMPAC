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

#include <sampgdk/a_samp.h>
#include <sampgdk/a_players.h>

cell AMX_NATIVE_CALL CFunctionHooks::HookedGivePlayerWeapon(AMX* amx, cell* params)
{
	PLAYERID playerID = (PLAYERID)params[1];

	ePlayerData *player;
	if ((player = CAntiCheat::GetPlayerByID(playerID)) == NULL) return NULL;

	player->bHasWeapon[params[2]] = true;
	return sampgdk_GivePlayerWeapon(playerID, params[2], params[3]);
}

cell AMX_NATIVE_CALL CFunctionHooks::HookedSetSpawnInfo(AMX* amx, cell* params)
{
	PLAYERID playerID = (PLAYERID)params[1];

	ePlayerData *player;
	if ((player = CAntiCheat::GetPlayerByID(playerID)) == NULL) return NULL;

	if (params[8] != -1) player->bHasWeapon[params[8]] = true;
	if (params[10] != -1) player->bHasWeapon[params[10]] = true;
	if (params[12] != -1) player->bHasWeapon[params[12]] = true;

	return sampgdk_SetSpawnInfo(params[1], params[2], params[3], amx_ctof(params[4]), amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7]), params[8], params[9], params[10], params[11], params[12], params[13]);
}

cell AMX_NATIVE_CALL CFunctionHooks::HookedAddPlayerClass(AMX* amx, cell* params)
{
	int
		classid;

	if ( CSampServer::i_SAMPVersion != INVALID_VERSION )
	{
		for ( classid = 0; classid != MAX_CLASSES; classid ++ )
		{
			if ( CSampServer::pServer->m_AvailableSpawns[classid].vecPos.fX == 0.0 )
			{
				CSampServer::pServer->m_AvailableSpawns [ classid ].iSkin = static_cast<int>(params[1]);

				CSampServer::pServer->m_AvailableSpawns [ classid ].vecPos.fX = amx_ctof(params[2]);
				CSampServer::pServer->m_AvailableSpawns [ classid ].vecPos.fY = amx_ctof(params[3]);
				CSampServer::pServer->m_AvailableSpawns [ classid ].vecPos.fZ = amx_ctof(params[4]);
				CSampServer::pServer->m_AvailableSpawns [ classid ].fRotation = amx_ctof(params[5]);

				CSampServer::pServer->m_AvailableSpawns [ classid ].iSpawnWeapons[0] = static_cast<int>(params[6]);
				CSampServer::pServer->m_AvailableSpawns [ classid ].iSpawnWeaponsAmmo[0] = static_cast<int>(params[7]);

				CSampServer::pServer->m_AvailableSpawns [ classid ].iSpawnWeapons[1] = static_cast<int>(params[8]);
				CSampServer::pServer->m_AvailableSpawns [ classid ].iSpawnWeaponsAmmo[1] = static_cast<int>(params[9]);

				CSampServer::pServer->m_AvailableSpawns [ classid ].iSpawnWeapons[2] = static_cast<int>(params[10]);
				CSampServer::pServer->m_AvailableSpawns [ classid ].iSpawnWeaponsAmmo[2] = static_cast<int>(params[11]);
				CSampServer::pServer->iSpawnAvailable ++;
				break;
			}
		}
	}
	else 
		return sampgdk_AddPlayerClass(params[1], amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]), params[6], params[7], params[8], params[9], params[10], params[11]);

	return classid;
}

cell AMX_NATIVE_CALL CFunctionHooks::HookedAddPlayerClassEx(AMX* amx, cell* params)
{
int
		classid;

	if ( CSampServer::i_SAMPVersion != INVALID_VERSION )
	{
		for ( classid = 0; classid != MAX_CLASSES; classid ++ )
		{
			if ( CSampServer::pServer->m_AvailableSpawns[classid].vecPos.fX == 0.0 )
			{
				CSampServer::pServer->m_AvailableSpawns [ classid ].bTeam = static_cast<int>(params[1]);
				CSampServer::pServer->m_AvailableSpawns [ classid ].iSkin = static_cast<int>(params[2]);

				CSampServer::pServer->m_AvailableSpawns [ classid ].vecPos.fX = amx_ctof(params[3]);
				CSampServer::pServer->m_AvailableSpawns [ classid ].vecPos.fY = amx_ctof(params[4]);
				CSampServer::pServer->m_AvailableSpawns [ classid ].vecPos.fZ = amx_ctof(params[5]);
				CSampServer::pServer->m_AvailableSpawns [ classid ].fRotation = amx_ctof(params[6]);

				CSampServer::pServer->m_AvailableSpawns [ classid ].iSpawnWeapons[0] = static_cast<int>(params[7]);
				CSampServer::pServer->m_AvailableSpawns [ classid ].iSpawnWeaponsAmmo[0] = static_cast<int>(params[8]);

				CSampServer::pServer->m_AvailableSpawns [ classid ].iSpawnWeapons[1] = static_cast<int>(params[9]);
				CSampServer::pServer->m_AvailableSpawns [ classid ].iSpawnWeaponsAmmo[1] = static_cast<int>(params[10]);

				CSampServer::pServer->m_AvailableSpawns [ classid ].iSpawnWeapons[2] = static_cast<int>(params[11]);
				CSampServer::pServer->m_AvailableSpawns [ classid ].iSpawnWeaponsAmmo[2] = static_cast<int>(params[12]);
				CSampServer::pServer->iSpawnAvailable ++;
				break;
			}
		}
	}
	else 
		return sampgdk_AddPlayerClassEx(params[1], params[2], amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]), amx_ctof(params[6]), params[7], params[8], params[9], params[10], params[11], params[12]);

	return classid;
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

cell AMX_NATIVE_CALL CFunctionHooks::HookedSetPlayerSpecialAction(AMX* amx, cell* params)
{
	PLAYERID playerID = (PLAYERID)params[1];
	ePlayerData *player;
	if ((player = CAntiCheat::GetPlayerByID(playerID)) == NULL) return NULL;
	int specialAction = (int)params[2];
	player->iSpecialAction = specialAction;
	return sampgdk_SetPlayerSpecialAction(playerID, specialAction);
}

cell AMX_NATIVE_CALL CFunctionHooks::HookedSetPlayerHealth(AMX* amx, cell* params)
{
	PLAYERID playerID = (PLAYERID)params[1];
	float	 fHealth = (float)params[2];
	ePlayerData *player;
	if ((player = CAntiCheat::GetPlayerByID(playerID)) == NULL) return NULL;

	if (fHealth > 99.0) fHealth = 99.0;
	if (fHealth < 0.0) fHealth = 0.0;

	player->bHealthSynced = false;
	player->fHealth = fHealth;
	return sampgdk_SetPlayerHealth(playerID, fHealth);
}

cell AMX_NATIVE_CALL CFunctionHooks::HookedSetPlayerArmour(AMX* amx, cell* params)
{
	PLAYERID playerID = (PLAYERID)params[1];
	float	 fArmour = (float)params[2];
	ePlayerData *player;
	if ((player = CAntiCheat::GetPlayerByID(playerID)) == NULL) return NULL;

	if (fArmour > 99.0) fArmour = 99.0;
	if (fArmour < 0.0) fArmour = 0.0;

	player->bArmourSynced = false;
	player->fArmour = fArmour;
	return sampgdk_SetPlayerHealth(playerID, fArmour);
}