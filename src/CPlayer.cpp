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
#include "CAntiCheat.h"
#include <sampgdk/a_players.h>

#define STURCT_INVALID(caller)	logprintf("Structs maybe incorrect - Caller: %s", caller);

void CPlayer::SetPosition ( PLAYERID playerID, float fX, float fY, float fZ ) 
{
	if ( CSampServer::i_SAMPVersion != INVALID_VERSION ) 
	{
		RakNet::BitStream bs;
		bs.Write ( fX );
		bs.Write ( fY );
		bs.Write ( fZ );
		PlayerID playerId = CSampServer::pServer->pRakServer->GetPlayerIDFromIndex ( playerID );
		if ( playerId.binaryAddress != 0xFFFFFFFF )
			CSampServer::pServer->pRakServer->RPC ( &CSampServer::rpcIDS.RPC_SET_POS, &bs, HIGH_PRIORITY, RELIABLE_ORDERED, 2, playerId, 0, 0 );
	}
	else
		sampgdk_SetPlayerPos(playerID, fX, fY, fZ);
}

void CPlayer::GetPosition ( PLAYERID playerID, float *fX, float *fY, float *fZ ) 
{
	if ( CSampServer::i_SAMPVersion != INVALID_VERSION ) {
		CSAMPPlayer *player;
		if ( (player=CSampServer::GetCPlayer(playerID)) == NULL )
		{
			STURCT_INVALID("CPlayer::GetPosition");
			return;
		}

		*fX = player->vecPosition.fX;
		*fY = player->vecPosition.fY;
		*fZ = player->vecPosition.fZ;
	} 
	else { // Fallback SAMPGDK :'(
		sampgdk_GetPlayerPos(playerID, fX, fY, fZ);
	}
}

void CPlayer::SetVelocity ( PLAYERID playerID, float fX, float fY, float fZ ) 
{
	if ( CSampServer::i_SAMPVersion != INVALID_VERSION ) 
	{
		RakNet::BitStream bs;
		bs.Write ( fX );
		bs.Write ( fY );
		bs.Write ( fZ );
		PlayerID playerId = CSampServer::pServer->pRakServer->GetPlayerIDFromIndex ( playerID );
		if ( playerId.binaryAddress != 0xFFFFFFFF )
			CSampServer::pServer->pRakServer->RPC ( &CSampServer::rpcIDS.RPC_SET_VELOCITY, &bs, HIGH_PRIORITY, RELIABLE_ORDERED, 2, playerId, 0, 0 );
	}
	else
		sampgdk_SetPlayerVelocity(playerID, fX, fY, fZ);
}

void CPlayer::GetVelocity ( PLAYERID playerID, float *fX, float *fY, float *fZ ) 
{
	if ( CSampServer::i_SAMPVersion != INVALID_VERSION ) {
		CSAMPPlayer *player;
		if ( (player=CSampServer::GetCPlayer(playerID)) == NULL )
		{
			STURCT_INVALID("CPlayer::GetVelocity");
			return;
		}

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
		if ( (player=CSampServer::GetCPlayer(playerID)) == NULL )
		{
			STURCT_INVALID("CPlayer::GetWeaponData");
			return;
		}

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
		return !!CSampServer::pServer->pPlayerPool->mIsNPC [ playerID ];
	} 
	else { // Fallback SAMPGDK :'(
		return sampgdk_IsPlayerNPC(playerID);//
	}
	return 0;
}

VEHICLEID CPlayer::GetVehicle ( PLAYERID playerID ) 
{ 
	if ( CSampServer::i_SAMPVersion != INVALID_VERSION ) {
		CSAMPPlayer *player;
		if ( (player=CSampServer::GetCPlayer(playerID)) == NULL )
		{
			STURCT_INVALID("CPlayer::GetVehicle");
			return -1;
		}

		return player->wVehicleId;	
	} 
	else { // Fallback SAMPGDK :'(
		return sampgdk_GetPlayerVehicleID(playerID);
	}
	return INVALID_VEHICLE_ID;
}

bool CPlayer::IsInVehicle(PLAYERID playerID)
{
	if (CSampServer::i_SAMPVersion != INVALID_VERSION) {
		CSAMPPlayer *player;
		if ( (player=CSampServer::GetCPlayer(playerID)) == NULL )
		{
			STURCT_INVALID("CPlayer::IsInVehicle");
			return false;
		}

		return ( player->wVehicleId > 0 && player->wVehicleId < 1000 );	
	}
	else { // Fallback SAMPGDK :'(
		return sampgdk_IsPlayerInAnyVehicle(playerID);
	}
	return false;
}

int CPlayer::GetMoney ( PLAYERID playerID ) 
{ 
	if ( CSampServer::i_SAMPVersion != INVALID_VERSION ) {
		return CAntiCheat::GetPlayerByID ( playerID )->iPlayerMoney;
	} 
	else { // Fallback SAMPGDK :'(
		return sampgdk_GetPlayerMoney(playerID);
	}
	return 0;
}

void CPlayer::SetMoney ( PLAYERID playerID, int iMoney ) 
{ 
	if ( CSampServer::i_SAMPVersion != INVALID_VERSION ) {
		PlayerID playerId = CSampServer::pServer->pRakServer->GetPlayerIDFromIndex ( playerID );
		if ( playerId.binaryAddress != 0xFFFFFFFF )
		{
			RakNet::BitStream bs;
			CSampServer::pServer->pRakServer->RPC ( &CSampServer::rpcIDS.RPC_RESET_MONEY, &bs, HIGH_PRIORITY, RELIABLE_ORDERED, 2, playerId, 0, 0 );
			bs.Write ( iMoney );
			CSampServer::pServer->pRakServer->RPC ( &CSampServer::rpcIDS.RPC_GIVE_MONEY, &bs, HIGH_PRIORITY, RELIABLE_ORDERED, 2, playerId, 0, 0 );
		}
	} 
	else { // Fallback SAMPGDK :'(
		sampgdk_ResetPlayerMoney(playerID);
		sampgdk_GivePlayerMoney(playerID, iMoney);
	}
}

int CPlayer::GetState ( PLAYERID playerID ) 
{
	if (CSampServer::i_SAMPVersion != INVALID_VERSION) {
		CSAMPPlayer *player;
		if ( (player=CSampServer::GetCPlayer(playerID)) == NULL )
		{
			STURCT_INVALID("CPlayer::GetState");
			return PLAYER_STATE_NONE;
		}
		return player->byteState;
	} 
	else { // Fallback SAMPGDK :'(
		return sampgdk_GetPlayerState(playerID);
	}
}

int CPlayer::GetPing ( PLAYERID playerID )
{
	if (CSampServer::i_SAMPVersion != INVALID_VERSION) {
		PlayerID playerId = CSampServer::pServer->pRakServer->GetPlayerIDFromIndex ( playerID );
		if ( playerId.binaryAddress != 0xFFFFFFFF )
			return CSampServer::pServer->pRakServer->GetLastPing ( playerId );
		else
			return 0xFFFF;
	}
	else { // Fallback SAMPGDK :'(
		return sampgdk_GetPlayerPing(playerID);
	}
}

int CPlayer::GetWeapon(PLAYERID playerID)
{
	if (CSampServer::i_SAMPVersion != INVALID_VERSION) {

		CSAMPPlayer *player;
		if ( (player=CSampServer::GetCPlayer(playerID)) == NULL )
		{
			STURCT_INVALID("CPlayer::GetWeapon");
			return 0;
		}
		return player->syncData.byteWeapon;
	}
	else { // Fallback SAMPGDK :'(
		return sampgdk_GetPlayerWeapon(playerID);
	}
}

int CPlayer::GetAnimationIndex(PLAYERID playerID)
{
	if (CSampServer::i_SAMPVersion != INVALID_VERSION) {
		CSAMPPlayer *player;
		if ( (player=CSampServer::GetCPlayer(playerID)) == NULL )
		{
			STURCT_INVALID("CPlayer::GetAnimationIndex");
			return 0;
		}
		return player->syncData.iAnimationId;
	}
	else { // Fallback SAMPGDK :'(
		return sampgdk_GetPlayerAnimationIndex(playerID);
	}
}

int CPlayer::GetSpecialAction(PLAYERID playerID)
{
	if (CSampServer::i_SAMPVersion != INVALID_VERSION) {
		CSAMPPlayer *player;
		if ( (player=CSampServer::GetCPlayer(playerID)) == NULL )
		{
			STURCT_INVALID("CPlayer::GetSpecialAction");
			return 0;
		}
		return player->syncData.byteSpecialAction;
	}
	else { // Fallback SAMPGDK :'(
		return sampgdk_GetPlayerSpecialAction(playerID);
	}
}

bool CPlayer::SetHealth(PLAYERID playerID, float fHealth)
{
	if (CSampServer::i_SAMPVersion != INVALID_VERSION) {
		RakNet::BitStream bs;
		bs.Write ( fHealth );
		PlayerID playerId = CSampServer::pServer->pRakServer->GetPlayerIDFromIndex ( playerID );
		if ( playerId.binaryAddress != 0xFFFFFFFF )
			CSampServer::pServer->pRakServer->RPC ( &CSampServer::rpcIDS.RPC_SET_POS, &bs, HIGH_PRIORITY, RELIABLE_ORDERED, 2, playerId, 0, 0 );
		return false;
	}
	else { // Fallback SAMPGDK :'(
		return sampgdk_SetPlayerHealth(playerID, fHealth);
	}
}

float CPlayer::GetHealth(PLAYERID playerID)
{
	if (CSampServer::i_SAMPVersion != INVALID_VERSION) {
		CSAMPPlayer *player;
		if ( (player=CSampServer::GetCPlayer(playerID)) == NULL )
		{
			STURCT_INVALID("CPlayer::GetHealth");
			return 0;
		}
		return player->syncData.byteHealth;
	}
	else { // Fallback SAMPGDK :'(
		float fHealth;
		return sampgdk_GetPlayerHealth(playerID, &fHealth) ? fHealth : 0.0f;
	}
}