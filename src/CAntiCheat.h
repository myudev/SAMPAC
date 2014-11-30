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

#ifndef _H_ANTICHEAT
#define _H_ANTICHEAT
#include "typedef.h"

#define MAX_PING ( 0xFFFF )
#define MAX_WEAPS ( 55 )
#define SAMP_MAX_PLAYERS	( 1000 )

#define ResetPlayerServerWeapons(player) \
	for (int i = 0; i < MAX_WEAPS; i++) player.bHasWeapon[i] = false;

// TODO: Cleanup
#define MAX_DETECTIONS 12
enum eCheatType {
	CHEAT_TYPE_WEAPON,
	CHEAT_TYPE_CARWARP,
	CHEAT_TYPE_MONEY,
	CHEAT_TYPE_PLAYERBUGGER,
	CHEAT_TYPE_PICKUP_SPAM,
	CHEAT_TYPE_SPECTATE,
	CHEAT_TYPE_FAKEKILL,
	CHEAT_TYPE_REMOTE_JACK,
	CHEAT_TYPE_PING_LIMIT,
	CHEAT_TYPE_SPEED_HACK,
	CHEAT_TYPE_JETPACK,
	CHEAT_TYPE_IMMUNITY
};
extern bool bIsDetectionEnabled[MAX_DETECTIONS];

struct ePlayerHitPointsData {
	float fPoints;
	float fCurrentPoints;
	int iUpdateTime;
	int iUpdateFail;
	bool bSynced;
};

struct ePlayerData {
	int iPlayerID;
	bool bHasWeapon[ MAX_WEAPS ];	

	int iPlayerMoney;
	int iSelectedClass;
	int iSpecialAction;

	int iCarWarpVehicleID;
	int iCarWarpTimeStamp;
	int iState;

	int iLastDeathTimestamp;
	int iDeathCounts;

	int iLastPickupID;
	int iPickupTimestamp;
	bool bHasPermissionToSpectate;

	Vec3 vLastCarjackData;
	int iLastEnteredVehicle;

	Vec3 vLastPickupPos;
	Vec3 vLastValidPos;

	ePlayerHitPointsData pHealth;
	ePlayerHitPointsData pArmour;
};

namespace CAntiCheat {
	void	Init( void );
	void	Tick( void );
	void	OnDetect(ePlayerData *pPlayer, eCheatType eCheatType, const char *fmt, ...);

	bool	AddPlayer(PLAYERID playerID);
	bool	RemovePlayer(PLAYERID playerID);

	void 	CarWarpCheck(PLAYERID playerID, NEWSTATE stateNEW);
	void 	RapidPickupSpam(PLAYERID playerID, PICKUPID pickupID);
	void	FakeKillCheck(PLAYERID playerid);
	void	RemoteJackingCheck(PLAYERID playerID);
	void	WeaponHackCheck(PLAYERID playerID);
	bool	WeaponHackStateFix(PLAYERID playerID, NEWSTATE stateNEW);
	bool	HealthHackCheck(PLAYERID playerID, int iTime);
	bool	ArmourHackCheck(PLAYERID playerID, int iTime);

	ePlayerData* GetPlayerByID(PLAYERID playerID);
};

#endif