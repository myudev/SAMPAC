#include "main.h"
#include <sampgdk/a_players.h>
#include "CAntiCheat.h"
#include "CPlayer.h"
#include <set>
#include <vector>
#include <math.h>
#include <stdarg.h> // va_*
#include <time.h>
#include <boost/unordered_map.hpp>

boost::unordered_map<PLAYERID, ePlayerData*> p_PlayerList; /* Fcking useless to have a array if we have this need to change this one day.*/
bool bIsDetectionEnabled[MAX_DETECTIONS];
ePlayerData p_PlayerData [ SAMP_MAX_PLAYERS ] ; // TODO: Add SA:MP Limits and some more structure :P


void CAntiCheat::Init() 
{ // Init stuff here. (prereserving array etc.)
	int iterator = 0;

	for (iterator = 0; iterator < SAMP_MAX_PLAYERS; iterator++ ) 
	{
		p_PlayerData[iterator].bHasPermissionToSpectate = false; // shall we ?
		p_PlayerData[iterator].bHasWeapon[46] = true; // ignore parachute for now later a advanced detection with vehicles
	}
}

void CAntiCheat::Tick()
{ // Invoked by ProcessTick
	logprintf("CAntiCheat::Tick()");
	int i_iIt = 0, i_It2 = 0; // Iterator (Base);
	int integers [ 2 ]; // no need for double allocation
	Vec3 tVec; // Temporary 3D Vector
	for (boost::unordered_map<PLAYERID, ePlayerData*>::iterator p = p_PlayerList.begin(); p != p_PlayerList.end(); ++p)
	{
		p->second->iState = CPlayer::GetState(p->second->iPlayerID) ; // Save State for Later processing.
		// Weapon Cheat
		if ( bIsDetectionEnabled[CHEAT_TYPE_WEAPON] ) {
			for(i_iIt = 0; i_iIt != 13; i_iIt++)
			{
				CPlayer::GetWeaponData(p->second->iPlayerID,i_iIt,&integers[0],&integers[1]);
				if(integers[1] > 0 && integers[0] != 0)
					if ( p->second->bHasWeapon[integers[0]] ) continue; else OnDetect(p->second, CHEAT_TYPE_WEAPON, "%d", integers[0]);
			}
		}

		// Money Cheat ( just the reset )
		if ( bIsDetectionEnabled[CHEAT_TYPE_MONEY] ) {
			if ( CPlayer::GetMoney(p->second->iPlayerID) != p->second->iPlayerMoney ) 
				CPlayer::SetMoney(p->second->iPlayerID, p->second->iPlayerMoney);
		}

		// Player Bugger
		if ( bIsDetectionEnabled[CHEAT_TYPE_PLAYERBUGGER] ) {
			if( p->second->iState == PLAYER_STATE_ONFOOT ) 
			{
				CPlayer::GetPosition( p->second->iPlayerID, &tVec.fX, &tVec.fY, &tVec.fZ );
		
				if( tVec.fX >= 99999.0 || tVec.fY >= 99999.0 || tVec.fZ >= 99999.0 || tVec.fX <= -99999.0 || tVec.fY <= -99999.0 || tVec.fZ <= -99999.0 ) {
					CPlayer::SetPosition( p->second->iPlayerID, p->second->vLastValidPos.fX, p->second->vLastValidPos.fY, p->second->vLastValidPos.fZ );
				}
				else
				{
					p->second->vLastValidPos.fX = tVec.fX;
					p->second->vLastValidPos.fY = tVec.fY;
					p->second->vLastValidPos.fZ = tVec.fZ;
				}
			}
		}

		// Spectate
		if ( bIsDetectionEnabled[CHEAT_TYPE_SPECTATE] ) {
			if ( p->second->iState == PLAYER_STATE_SPECTATING && !p->second->bHasPermissionToSpectate )
				OnDetect(p->second, CHEAT_TYPE_SPECTATE, "\0"); // Cheater !
		}
		
	}
}

char g_DetectBuffer [ 512 ];
void CAntiCheat::OnDetect(ePlayerData *pPlayer, eCheatType eCheatType, const char *fmt, ...) 
{
	int iAmxIndex = 0;

	va_list pVaArgs;
	va_start(pVaArgs, g_DetectBuffer);
	vsnprintf_s(g_DetectBuffer, 512-1, 512, fmt, pVaArgs);
	va_end(pVaArgs);
	
	cell tmp_addr, *tmp_physaddr;

	for (std::set<AMX*>::iterator a = pLAMXList.begin(); a != pLAMXList.end(); ++a)
	{
		if (!amx_FindPublic(*a, "SAMPAC_OnCheatDetect", &iAmxIndex ))
		{
			amx_PushString(*a, &tmp_addr, &tmp_physaddr, g_DetectBuffer, 0, 0);
			amx_Push(*a, static_cast<cell>(eCheatType));
			amx_Push(*a, static_cast<cell>(pPlayer->iPlayerID));
			amx_Exec(*a, NULL, iAmxIndex);
		}
	}  
}

bool CAntiCheat::AddPlayer(PLAYERID playerID)
{
	if (playerID >= 0 && playerID < SAMP_MAX_PLAYERS)
	{
		logprintf("CAntiCheat::AddPlayer(%d)", playerID);
		boost::unordered_map<int, ePlayerData*>::iterator p = p_PlayerList.find(playerID);
		p_PlayerData[playerID].iPlayerID = playerID;
		if (p == p_PlayerList.end())
		{
			p_PlayerList.insert(std::make_pair(playerID, &p_PlayerData[playerID]));
		}
	}
	return true;
}

bool CAntiCheat::RemovePlayer(PLAYERID playerID)
{
	if (playerID >= 0 && playerID < SAMP_MAX_PLAYERS) 
	{
		logprintf("CAntiCheat::RemovePlayer(%d)", playerID);
		p_PlayerList.erase(playerID);
	}
	return true;
}

void CAntiCheat::CarWarpCheck(PLAYERID playerID, NEWSTATE stateNEW)
{
	if( bIsDetectionEnabled[ CHEAT_TYPE_CARWARP ] )
	{		
		if( CPlayer::GetVehicle( playerID ) != p_PlayerData[ playerID ].iCarWarpVehicleID )
        {
	        if( p_PlayerData[ playerID ].iCarWarpTimeStamp > time(NULL) )
	        {
				OnDetect(&p_PlayerData[ playerID ], CHEAT_TYPE_CARWARP, "%d", p_PlayerData[ playerID ].iCarWarpVehicleID);
	            return;
	        }
	        p_PlayerData[ playerID ].iCarWarpTimeStamp = ((int)time(NULL)) + 1;
			p_PlayerData[ playerID ].iCarWarpVehicleID = CPlayer::GetVehicle( playerID );
		}
	}
}

void CAntiCheat::RapidPickupSpam(PLAYERID playerID, PICKUPID pickupID)
{
	if( bIsDetectionEnabled[ CHEAT_TYPE_PICKUP_SPAM ] )
	{
		if( pickupID != p_PlayerData[ playerID ].iLastPickupID )
		{
			int iTickCount = (int)GetTickCount( ); // Call it once, because swag
	        if( p_PlayerData[ playerID ].iPickupTimestamp > iTickCount )
	        {
				Vec3 curPos;
				CPlayer::GetPosition(p_PlayerData[ playerID ].iPlayerID, &curPos.fX,&curPos.fY,&curPos.fZ);
	        	// He entered very fast, bad boy!!! Let's see how far it is though
	        	float distance = p_PlayerData[ playerID ].vLastPickupPos.DistanceTo( &curPos );

	        	if( distance < 100.0 ) logprintf("[AC WARN] Player ID %d has entered a pickup near him really fast. (distance: %0.2fm, time: %d)", (int)playerID, distance, p_PlayerData[ playerID ].iPickupTimestamp - iTickCount );
	        	else 
	        	{
					OnDetect(&p_PlayerData[ playerID ], CHEAT_TYPE_PICKUP_SPAM, "%d:%f:%d", pickupID, distance, p_PlayerData[ playerID ].iPickupTimestamp - iTickCount );
		            return;
	        	}
	        }
	        p_PlayerData[ playerID ].iPickupTimestamp = iTickCount + 1000;
			p_PlayerData[ playerID ].iLastPickupID = pickupID;		
		}		
	}
	CPlayer::GetPosition( p_PlayerData[ playerID ].iPlayerID, &p_PlayerData[ playerID ].vLastPickupPos.fX, &p_PlayerData[ playerID ].vLastPickupPos.fY, &p_PlayerData[ playerID ].vLastPickupPos.fZ );
}

cell AMX_NATIVE_CALL CAntiCheat::HookedGivePlayerWeapon( AMX* amx, cell* params )
{
	PLAYERID playerID = (PLAYERID)params[1];
	p_PlayerData[playerID].bHasWeapon[params[2]] = true;
	return sampgdk_GivePlayerWeapon(playerID,params[2],params[3]);
}

cell AMX_NATIVE_CALL CAntiCheat::HookedResetPlayerWeapons( AMX* amx, cell* params )
{
	PLAYERID playerID = (PLAYERID)params[1];
	sampgdk_ResetPlayerWeapons(playerID);;

	for (int it = 0; it != MAX_WEAPS; it++ ) 
		p_PlayerData[playerID].bHasWeapon[it] = false;

	return true;
}

cell AMX_NATIVE_CALL CAntiCheat::HookedGivePlayerMoney( AMX* amx, cell* params )
{
	PLAYERID playerID = (PLAYERID)params[1];
	int iMoney = (int)params[2];
	p_PlayerData[playerID].iPlayerMoney += iMoney;

	return sampgdk_GivePlayerMoney(playerID,iMoney);
}

cell AMX_NATIVE_CALL CAntiCheat::HookedGetPlayerMoney( AMX* amx, cell* params )
{
	PLAYERID playerID = (PLAYERID)params[1];
	return p_PlayerData[playerID].iPlayerMoney;
}

cell AMX_NATIVE_CALL CAntiCheat::HookedResetPlayerMoney( AMX* amx, cell* params )
{
	PLAYERID playerID = (PLAYERID)params[1];
	CPlayer::SetMoney(playerID, 0);
	return true;
}

cell AMX_NATIVE_CALL CAntiCheat::HookedTogglePlayerSpectating( AMX* amx, cell* params )
{
	PLAYERID playerID = (PLAYERID)params[1];
	bool	 bToggle  = !!params[2];
	p_PlayerData[playerID].bHasPermissionToSpectate = bToggle;
	return true;
}
