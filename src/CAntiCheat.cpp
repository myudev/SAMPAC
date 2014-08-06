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
#include <sampgdk/a_players.h>
#include "CAntiCheat.h"
#include "CPlayer.h"
#include "CVehicle.h"
#include <set>
#include <vector>
#include <math.h>
#include <stdarg.h> // va_*
#include <time.h>
#include <boost/unordered_map.hpp>

boost::unordered_map<PLAYERID, ePlayerData*> p_PlayerList;
bool bIsDetectionEnabled[MAX_DETECTIONS];

// Init stuff here. (prereserving array etc.)
void CAntiCheat::Init() 
{
	for (int i = 0; i != MAX_DETECTIONS; i++)
		bIsDetectionEnabled[i] = true;
}

// Invoked by ProcessTick
void CAntiCheat::Tick()
{
	logprintf("CAntiCheat::Tick()");
	Vec3 tVec; // Temporary 3D Vector
	for (boost::unordered_map<PLAYERID, ePlayerData*>::iterator p = p_PlayerList.begin(); p != p_PlayerList.end(); ++p)
	{
		p->second->iPlayerID = p->first; // Bug fix
		p->second->iState = CPlayer::GetState(p->first) ; // Save State for Later processing.

		// Anti-Weapon Hack
		if (bIsDetectionEnabled[CHEAT_TYPE_WEAPON]) {
			CAntiCheat::WeaponHackCheck(p->second->iPlayerID);
			continue;
		}

		// Money Cheat ( just the reset )
		if ( bIsDetectionEnabled[CHEAT_TYPE_MONEY] ) {
			if (CPlayer::GetMoney(p->second->iPlayerID) != p->second->iPlayerMoney)  {
				CPlayer::SetMoney(p->second->iPlayerID, p->second->iPlayerMoney);
				continue;
			}
		}

		// Player Bugger
		if ( bIsDetectionEnabled[CHEAT_TYPE_PLAYERBUGGER] ) {
			if( p->second->iState == PLAYER_STATE_ONFOOT ) 
			{
				CPlayer::GetPosition( p->second->iPlayerID, &tVec.fX, &tVec.fY, &tVec.fZ );
		
				if( tVec.fX >= 99999.0 || tVec.fY >= 99999.0 || tVec.fZ >= 99999.0 || tVec.fX <= -99999.0 || tVec.fY <= -99999.0 || tVec.fZ <= -99999.0 ) {
					CPlayer::SetPosition( p->second->iPlayerID, p->second->vLastValidPos.fX, p->second->vLastValidPos.fY, p->second->vLastValidPos.fZ );
					continue;
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
			if (p->second->iState == PLAYER_STATE_SPECTATING && !p->second->bHasPermissionToSpectate) {
				OnDetect(p->second, CHEAT_TYPE_SPECTATE, "\0"); // Cheater !
				continue;
			}
		}

		// Ping Limit
		if (bIsDetectionEnabled[CHEAT_TYPE_PING_LIMIT]) {
			if (CPlayer::GetPing(p->second->iPlayerID) > set.g_iMaxPing) {
				OnDetect(p->second, CHEAT_TYPE_PING_LIMIT, "\0");
				continue;
			}
		}

		CAntiCheat::RemoteJackingCheck(p->second->iPlayerID);
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
	if ( !SAMP_IS_VALID_PLAYERID(playerID) )
		return false;

	logprintf("CAntiCheat::AddPlayer(%d)", playerID);
	boost::unordered_map<int, ePlayerData*>::iterator p = p_PlayerList.find(playerID);

	ePlayerData p_PlayerData;

	p_PlayerData.bHasPermissionToSpectate = false; // shall we ?
	p_PlayerData.bHasWeapon[46] = true; // ignore parachute for now later a advanced detection with vehicles
	p_PlayerData.iPlayerID = playerID;

	if (p == p_PlayerList.end())
	{
		p_PlayerList.insert(std::make_pair(playerID, &p_PlayerData));
	}
	return true;
}

bool CAntiCheat::RemovePlayer(PLAYERID playerID)
{
	if ( !SAMP_IS_VALID_PLAYERID(playerID) )
		return false;

	boost::unordered_map<int, ePlayerData*>::iterator p = p_PlayerList.find(playerID);


	if (p != p_PlayerList.end())
	{
		delete p->second;
		p_PlayerList.erase(p);
	}
	return true;
}

ePlayerData* CAntiCheat::GetPlayerByID(PLAYERID playerID)
{
	boost::unordered_map<int, ePlayerData*>::iterator p = p_PlayerList.find(playerID);
	if (p != p_PlayerList.end())
	{
		return p->second;
	}
	return NULL;
}

void CAntiCheat::CarWarpCheck(PLAYERID playerID, NEWSTATE stateNEW)
{
	if( bIsDetectionEnabled[ CHEAT_TYPE_CARWARP ] )
	{		
		ePlayerData *player;
		if ( (player=GetPlayerByID(playerID)) == NULL ) return;

		if( CPlayer::GetVehicle( playerID ) != player->iCarWarpVehicleID )
        {
	        if( player->iCarWarpTimeStamp > time(NULL) )
	        {
				OnDetect(player, CHEAT_TYPE_CARWARP, "%d", player->iCarWarpVehicleID);
	            return;
	        }
			player->iCarWarpTimeStamp = ((int)time(NULL)) + 1;
			player->iCarWarpVehicleID = CPlayer::GetVehicle( playerID );
		}
	}
}

void CAntiCheat::RapidPickupSpam(PLAYERID playerID, PICKUPID pickupID)
{
	ePlayerData *player;
	if ( (player=GetPlayerByID(playerID)) == NULL ) return;
	if( bIsDetectionEnabled[ CHEAT_TYPE_PICKUP_SPAM ] )
	{
		if( pickupID != player->iLastPickupID )
		{
			int iTickCount = (int)GetTickCount( ); // Call it once, because swag
	        if( player->iPickupTimestamp > iTickCount )
	        {
				Vec3 curPos;
				CPlayer::GetPosition(player->iPlayerID, &curPos.fX,&curPos.fY,&curPos.fZ);
	        	// He entered very fast, bad boy!!! Let's see how far it is though
	        	float distance = player->vLastPickupPos.DistanceTo( &curPos );

	        	if( distance < 100.0 ) logprintf("[AC WARN] Player ID %d has entered a pickup near him really fast. (distance: %0.2fm, time: %d)", (int)playerID, distance, player->iPickupTimestamp - iTickCount );
	        	else 
	        	{
					OnDetect(player, CHEAT_TYPE_PICKUP_SPAM, "%d:%f:%d", pickupID, distance, player->iPickupTimestamp - iTickCount );
		            return;
	        	}
	        }
	        player->iPickupTimestamp = iTickCount + 1000;
			player->iLastPickupID = pickupID;		
		}		
	}
	CPlayer::GetPosition( player->iPlayerID, &player->vLastPickupPos.fX, &player->vLastPickupPos.fY, &player->vLastPickupPos.fZ );
}

void CAntiCheat::FakeKillCheck(PLAYERID playerID)
{
	ePlayerData *player;
	if ((player = GetPlayerByID(playerID)) == NULL) return;
	if (bIsDetectionEnabled[CHEAT_TYPE_FAKEKILL])
	{
		int iTime = (int)time(NULL);

		if ((iTime - player->iLastDeathTimestamp) <= 3)
		{
			if (player->iDeathCounts++ >= 3)
			{
				OnDetect(player, CHEAT_TYPE_FAKEKILL, "%d:%d", player->iDeathCounts, iTime - player->iLastDeathTimestamp);
				return;
			}
		}
		else player->iDeathCounts = 0;

		player->iLastDeathTimestamp = iTime;
	}
}

void CAntiCheat::RemoteJackingCheck(PLAYERID playerID)
{
	ePlayerData *player;
	if ((player = GetPlayerByID(playerID)) == NULL) return;

	if (bIsDetectionEnabled[CHEAT_TYPE_REMOTE_JACK])
	{
		int iVehicle = CPlayer::GetVehicle(playerID);

		if (!CPlayer::IsInVehicle(playerID))
			CPlayer::GetPosition(player->iPlayerID, &player->vLastCarjackData.fX, &player->vLastCarjackData.fY, &player->vLastCarjackData.fZ);

		if ((iVehicle != player->iLastEnteredVehicle) && (iVehicle != 0) && (CPlayer::GetState(playerID) == PLAYER_STATE_DRIVER))
		{
			float 
				fDistance = CVehicle::GetDistanceFromPoint(iVehicle, player->vLastCarjackData.fX, player->vLastCarjackData.fY, player->vLastCarjackData.fZ),
				fOffset = 10.0;

			int vModel = CVehicle::GetModel(iVehicle);

			if ((vModel == 577) || (vModel == 592))
				fOffset = 25.0; // Andromanda | AT-400

			if (fDistance > fOffset) {
				OnDetect(player, CHEAT_TYPE_REMOTE_JACK, "%f:%f:%d", fDistance, fOffset, iVehicle);
			}

			CPlayer::GetPosition(player->iPlayerID, &player->vLastCarjackData.fX, &player->vLastCarjackData.fY, &player->vLastCarjackData.fZ);
			player->iLastEnteredVehicle = iVehicle;
		}
	}
}

void CAntiCheat::WeaponHackCheck(PLAYERID playerID)
{
	if (!bIsDetectionEnabled[CHEAT_TYPE_WEAPON])
		return;

	if (!SAMP_IS_VALID_PLAYERID(playerID))
		return;

	ePlayerData *player;
	if ((player = GetPlayerByID(playerID)) == NULL) return;

	int iWeapon = NULL, iAmmo = NULL;

	for (int iSlot = 0; iSlot != 13; iSlot++)
	{
		CPlayer::GetWeaponData(player->iPlayerID, iSlot, &iWeapon, &iAmmo);
		if (!player->bHasWeapon[iWeapon] && (iAmmo > 0 && iWeapon != 0 && iWeapon != 40)) {
			OnDetect(player, CHEAT_TYPE_WEAPON, "%d", iWeapon);
			break;
		}
	}

	// can be used under onplayerkeystatechange (we'll review later)
	/*if ((newKeys & KEY_FIRE) == KEY_FIRE)
	{
		logprintf("[WeaponHackCheck] LOL %d == %d", (int)player->iState, PLAYER_STATE_ONFOOT);
		if (player->iState == PLAYER_STATE_ONFOOT)
		{
			weaponID = CPlayer::GetWeapon(playerID);

			if (!player->bHasWeapon[weaponID] && weaponID != 40 && weaponID != 0) OnDetect(player, CHEAT_TYPE_WEAPON, "%d", weaponID);
		}
	}*/
}