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
#include "CPlayer.h"
#include <sampgdk/a_players.h>

void CPlayer::SetPosition ( PLAYERID playerID, float fX, float fY, float fZ ) 
{ // No Fallback to sampgdk, theres actually no way of position setting via. pure data
	sampgdk_SetPlayerPos(playerID, fX, fY, fZ);
}

void CPlayer::GetPosition ( PLAYERID playerID, float *fX, float *fY, float *fZ ) 
{
	if ( CSampServer::i_SAMPVersion != INVALID_VERSION ) {
		CSAMPPlayer *player;
		if ( (player=CSampServer::GetCPlayer(playerID)) == NULL )	return logprintf("Error, structures may be incorrect contact the Author(s)");

		*fX = player->vecPosition.fX;
		*fY = player->vecPosition.fY;
		*fZ = player->vecPosition.fZ;
	} 
	else { // Fallback SAMPGDK :'(
		sampgdk_GetPlayerPos(playerID, fX, fY, fZ);
	}
}

void CPlayer::SetVelocity ( PLAYERID playerID, float fX, float fY, float fZ ) 
{  // No Fallback to sampgdk, theres actually no way of position setting via. pure data (ok there kinda is)
	sampgdk_SetPlayerVelocity(playerID, fX, fY, fZ);
}

void CPlayer::GetVelocity ( PLAYERID playerID, float *fX, float *fY, float *fZ ) 
{
	if ( CSampServer::i_SAMPVersion != INVALID_VERSION ) {
		CSAMPPlayer *player;
		if ( (player=CSampServer::GetCPlayer(playerID)) == NULL )	return logprintf("Error, structures may be incorrect contact the Author(s)");

		*fX = player->vecVelocity.fX;
		*fY = player->vecVelocity.fY;
		*fZ = player->vecVelocity.fZ;		
	} 
	else { // Fallback SAMPGDK :'(
		sampgdk_GetPlayerVelocity(playerID, fX, fY, fZ);
	}
}

void CPlayer::GetWeaponData ( PLAYERID playerID, short sIndex, int *iWeap, int *iAmmo ) 
{ 
	if ( CSampServer::i_SAMPVersion != INVALID_VERSION ) {
		CSAMPPlayer *player;
		if ( (player=CSampServer::GetCPlayer(playerID)) == NULL )	return logprintf("Error, structures may be incorrect contact the Author(s)");

		*iWeap = player->byteWeaponId[sIndex];
		*iAmmo = player->wWeaponAmmo[sIndex];
	} 
	else { // Fallback SAMPGDK :'(
		sampgdk_GetPlayerWeaponData(playerID, sIndex, iWeap, iAmmo);
	}
}


bool CPlayer::IsNPC ( PLAYERID playerID ) 
{ 
	if ( CSampServer::i_SAMPVersion != INVALID_VERSION ) {
		return 0;
	} 
	else { // Fallback SAMPGDK :'(
		return sampgdk_IsPlayerNPC(playerID);
	}
	return 0;
}


VEHICLEID CPlayer::GetVehicle ( PLAYERID playerID ) 
{ 
	if ( CSampServer::i_SAMPVersion != INVALID_VERSION ) {
		return INVALID_VEHICLE_ID;	
	} 
	else { // Fallback SAMPGDK :'(
		return sampgdk_GetPlayerVehicleID(playerID);
	}
	return INVALID_VEHICLE_ID;
}


bool CPlayer::IsInVehicle(PLAYERID playerID)
{
	if (CSampServer::i_SAMPVersion != INVALID_VERSION) {
		return false;
	}
	else { // Fallback SAMPGDK :'(
		return sampgdk_IsPlayerInAnyVehicle(playerID);
	}
	return false;
}


int CPlayer::GetMoney ( PLAYERID playerID ) 
{ 
	if ( CSampServer::i_SAMPVersion != INVALID_VERSION ) {
		return 0;
	} 
	else { // Fallback SAMPGDK :'(
		return sampgdk_GetPlayerMoney(playerID);
	}
	return 0;
}


void CPlayer::SetMoney ( PLAYERID playerID, int iMoney ) 
{ 
	if ( CSampServer::i_SAMPVersion != INVALID_VERSION ) {
		
	} 
	else { // Fallback SAMPGDK :'(
		sampgdk_ResetPlayerMoney(playerID);
		sampgdk_GivePlayerMoney(playerID, iMoney);
	}
}


int CPlayer::GetState ( PLAYERID playerID ) 
{ 
	if ( CSampServer::i_SAMPVersion != INVALID_VERSION ) {
		return 0;
	} 
	else { // Fallback SAMPGDK :'(
		return sampgdk_GetPlayerState(playerID);
	}
}

int CPlayer::GetPing ( PLAYERID playerID )
{
	if (CSampServer::i_SAMPVersion != INVALID_VERSION) {
		return 0xFFFF;
	}
	else { // Fallback SAMPGDK :'(
		return sampgdk_GetPlayerPing(playerID);
	}
}