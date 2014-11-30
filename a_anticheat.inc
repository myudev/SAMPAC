/*
	PROJECT		<>	SA:MP Anticheat Plug-in
	LICENSE		<>	See LICENSE in the top level directory.
	AUTHOR(S)	<>	Lorenc_ (zeelorenc@hotmail.com)
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

#include 							< a_samp >

// Enumerator
enum
{
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

// Natives (Global)

native SAMPAC_SetTickRate(maxticks);
native SAMPAC_SetDetectionState(detection, bool: bState);
native SAMPAC_SetServerPingLimit(timems = -1);

// Natives (Include Only)

native SAMPAC_CallbackHook(callback, {Float,_}:...);

// Callbacks

forward SAMPAC_OnCheatDetect(playerid, detection, extrainfo[]);

// Callback Hook Section

#define SAMPAC_OPC 					( 0 )
#define SAMPAC_OPDC 				( 1 )
#define SAMPAC_OPSC 				( 2 )
#define SAMPAC_OPPP 				( 3 )
#define SAMPAC_OPD 					( 4 )
#define SAMPAC_OPKSC 				( 5 )
#define SAMPAC_OPRC  				( 6 )
#define SAMPAC_OPTD  				( 7 )
#define SAMPAC_OPS 					( 8 )
#define SAMPAC_OPU 					( 9 )

// Hook (OnPlayerConnect)

public OnPlayerConnect(playerid)
{
	SAMPAC_CallbackHook(SAMPAC_OPC, playerid);
	#if defined SAMPAC_OnPlayerConnect
		return SAMPAC_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}

#if defined SAMPAC_OnPlayerConnect
	forward SAMPAC_OnPlayerConnect(playerid);
#endif
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect SAMPAC_OnPlayerConnect

// Hook (OnPlayerDisconnect)

public OnPlayerDisconnect(playerid, reason)
{
	SAMPAC_CallbackHook(SAMPAC_OPDC, playerid, reason);
	#if defined SAMPAC_OnPlayerDisconnect
		return SAMPAC_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}

#if defined SAMPAC_OnPlayerDisconnect
	forward SAMPAC_OnPlayerDisconnect(playerid, reason);
#endif
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect SAMPAC_OnPlayerDisconnect

// Hook (OnPlayerSpawn)

public OnPlayerSpawn(playerid)
{
	SAMPAC_CallbackHook(SAMPAC_OPS, playerid);
	#if defined SAMPAC_OnPlayerSpawn
		return SAMPAC_OnPlayerSpawn(playerid);
	#else
		return 1;
	#endif
}

#if defined SAMPAC_OnPlayerSpawn
	forward SAMPAC_OnPlayerSpawn(playerid);
#endif
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn SAMPAC_OnPlayerSpawn

// Hook (OnPlayerUpdate)

public OnPlayerUpdate(playerid)
{
	SAMPAC_CallbackHook(SAMPAC_OPU, playerid);
	#if defined SAMPAC_OnPlayerUpdate
		return SAMPAC_OnPlayerUpdate(playerid);
	#else
		return 1;
	#endif
}

#if defined SAMPAC_OnPlayerUpdate
	forward SAMPAC_OnPlayerUpdate(playerid);
#endif
#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate SAMPAC_OnPlayerUpdate

// Hook (OnPlayerStateChange)

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	SAMPAC_CallbackHook(SAMPAC_OPSC, playerid, newstate, oldstate);
	#if defined SAMPAC_OnPlayerStateChange
		return SAMPAC_OnPlayerStateChange(playerid, newstate, oldstate);
	#else
		return 1;
	#endif
}

#if defined SAMPAC_OnPlayerStateChange
	forward SAMPAC_OnPlayerStateChange(playerid, newstate, oldstate);
#endif
#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange SAMPAC_OnPlayerStateChange

// Hook (OnPlayerPickUpPickup)

public OnPlayerPickUpPickup(playerid, pickupid)
{
	SAMPAC_CallbackHook(SAMPAC_OPPP, playerid, pickupid);
	#if defined SAMPAC_OnPlayerPickUpPickup
		return SAMPAC_OnPlayerPickUpPickup(playerid, pickupid);
	#else
		return 1;
	#endif
}

#if defined SAMPAC_OnPlayerPickUpPickup
	forward SAMPAC_OnPlayerPickUpPickup(playerid, pickupid);
#endif
#if defined _ALS_OnPlayerPickUpPickup
	#undef OnPlayerPickUpPickup
#else
	#define _ALS_OnPlayerPickUpPickup
#endif
#define OnPlayerPickUpPickup SAMPAC_OnPlayerPickUpPickup

// Hook (OnPlayerDeath)

public OnPlayerDeath(playerid, killerid, reason)
{
	SAMPAC_CallbackHook(SAMPAC_OPD, playerid, killerid, reason);
	#if defined SAMPAC_OnPlayerDeath
		return SAMPAC_OnPlayerDeath(playerid, killerid, reason);
	#else
		return 1;
	#endif
}

#if defined SAMPAC_OnPlayerDeath
	forward SAMPAC_OnPlayerDeath(playerid, killerid, reason);
#endif
#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath SAMPAC_OnPlayerDeath

// Hook (OnPlayerKeyStateChange)

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	SAMPAC_CallbackHook(SAMPAC_OPKSC, playerid, newkeys, oldkeys);
	#if defined SAMPAC_OnPlayerKeyStateChange
		return SAMPAC_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}

#if defined SAMPAC_OnPlayerKeyStateChange
	forward SAMPAC_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif
#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange SAMPAC_OnPlayerKeyStateChange

// Hook (OnPlayerRequestClass)

public OnPlayerRequestClass(playerid, classid)
{
	SAMPAC_CallbackHook(SAMPAC_OPRC, playerid, classid);
	#if defined SAMPAC_OnPlayerRequestClass
		return SAMPAC_OnPlayerRequestClass(playerid, classid);
	#else
		return 1;
	#endif
}

#if defined SAMPAC_OnPlayerRequestClass
	forward SAMPAC_OnPlayerRequestClass(playerid, classid);
#endif
#if defined _ALS_OnPlayerRequestClass
	#undef OnPlayerRequestClass
#else
	#define _ALS_OnPlayerRequestClass
#endif
#define OnPlayerRequestClass SAMPAC_OnPlayerRequestClass

// Hook (OnPlayerTakeDamage)

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	SAMPAC_CallbackHook(SAMPAC_OPTD, playerid, issuerid, amount, weaponid, bodypart);
	#if defined SAMPAC_OnPlayerTakeDamage
		return SAMPAC_OnPlayerTakeDamage(playerid, issuerid, amount, weaponid, bodypart);
	#else
		return 1;
	#endif
}

#if defined SAMPAC_OnPlayerTakeDamage
	forward SAMPAC_OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart);
#endif
#if defined _ALS_OnPlayerTakeDamage
	#undef OnPlayerTakeDamage
#else
	#define _ALS_OnPlayerTakeDamage
#endif
#define OnPlayerTakeDamage SAMPAC_OnPlayerTakeDamage

// Testing

public SAMPAC_OnCheatDetect(playerid, detection, extrainfo[])
{
	new 
		string[256]; // I just put 256 because lol

	printf("%d, %d, \"%s\"\n", playerid, detection, extrainfo);
	format( string, 256, "DETECTED :: %d, %d, \"%s\"\n", playerid, detection, extrainfo);
	SendClientMessageToAll( 0xFF0000FF, string );
	return 1;
}
