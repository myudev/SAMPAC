#include "main.h"
#include "CPlayer.h"
#include <sampgdk/a_samp.h>
#include <sampgdk/a_players.h>

void CPlayer::SetPosition ( PLAYERID playerID, float fX, float fY, float fZ ) 
{ // No Fallback to sampgdk, theres actually no way of position setting via. pure data
	sampgdk_SetPlayerPos(playerID, fX, fY, fZ);
}

void CPlayer::GetPosition ( PLAYERID playerID, float *fX, float *fY, float *fZ ) 
{
	if ( set.m_bSAMPHooks ) {
		
	} 
	else { // Fallback SAMPGDK :'(
		sampgdk_GetPlayerPos(playerID, fX, fY, fZ);
	}
}

void CPlayer::SetVelocity ( PLAYERID playerID, float fX, float fY, float fZ ) 
{  // No Fallback to sampgdk, theres actually no way of position setting via. pure data
	sampgdk_SetPlayerVelocity(playerID, fX, fY, fZ);
}

void CPlayer::GetVelocity ( PLAYERID playerID, float *fX, float *fY, float *fZ ) 
{
	if ( set.m_bSAMPHooks ) {
		
	} 
	else { // Fallback SAMPGDK :'(
		sampgdk_GetPlayerVelocity(playerID, fX, fY, fZ);
	}
}

void CPlayer::GetWeaponData ( PLAYERID playerID, short sIndex, int *iWeap, int *iAmmo ) 
{ 
	if ( set.m_bSAMPHooks ) {
		
	} 
	else { // Fallback SAMPGDK :'(
		sampgdk_GetPlayerWeaponData(playerID, sIndex, iWeap, iAmmo);
	}
}


bool CPlayer::IsNPC ( PLAYERID playerID ) 
{ 
	if ( set.m_bSAMPHooks ) {
		return 0;
	} 
	else { // Fallback SAMPGDK :'(
		return sampgdk_IsPlayerNPC(playerID);
	}
	return 0;
}


VEHICLEID CPlayer::GetVehicle ( PLAYERID playerID ) 
{ 
	if ( set.m_bSAMPHooks ) {
		return INVALID_VEHICLE_ID;	
	} 
	else { // Fallback SAMPGDK :'(
		return sampgdk_GetPlayerVehicleID(playerID);
	}
	return INVALID_VEHICLE_ID;
}


int CPlayer::GetMoney ( PLAYERID playerID ) 
{ 
	if ( set.m_bSAMPHooks ) {
		return 0;
	} 
	else { // Fallback SAMPGDK :'(
		return sampgdk_GetPlayerMoney(playerID);
	}
	return 0;
}


void CPlayer::SetMoney ( PLAYERID playerID, int iMoney ) 
{ 
	if ( set.m_bSAMPHooks ) {
		
	} 
	else { // Fallback SAMPGDK :'(
		sampgdk_ResetPlayerMoney(playerID);
		sampgdk_GivePlayerMoney(playerID, iMoney);
	}
}


int CPlayer::GetState ( PLAYERID playerID ) 
{ 
	if ( set.m_bSAMPHooks ) {
		return 0;
	} 
	else { // Fallback SAMPGDK :'(
		return sampgdk_GetPlayerState(playerID);
	}
}
