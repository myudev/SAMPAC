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
#include "CNatives.h"
#include "CAntiCheat.h"
#include "CallbackHooks.h"

/*
	enum eCheatTypes {
		CHEAT_TYPE_WEAPON,
		CHEAT_TYPE_CARWARP,
		CHEAT_TYPE_MONEY,
		CHEAT_TYPE_PLAYERBUGGER,
		CHEAT_TYPE_PICKUP_SPAM,
		CHEAT_TYPE_SPECTATE
	};
	

	Native(s) List (Include):
		native SAMPAC_SetTickRate(maxticks); // set's the maxium of ticks for the cycle lower value means faster higher means slower but also less resources.
		native SAMPAC_SetDetectionState(eCheatTypes:detection, bool:bState); // enables / disables an detection (detection names are above).
		native SAMPAC_CallbackHook(callback, {Float,_}:...); // allows us to hook callbacks easily without so much mess

		native SAMPAC_SetServerPingLimit(timems = -1); // set the server ping limit, -1 for disabled

	Callbacks:
		forward SAMPAC_OnCheatDetect(playerid, detection, extrainfo[]);

	Extra Info (Detect Callback:)
		DETECTION_TYPE_WEAPON - Integer (Weapon ID that he has but dont was given by the Script.)
		DETECTION_TYPE_CARWARP - Integer (Vehicle ID he warped in (!! it does not detect every vehicle he warped in just the last vehicle))
*/

cell AMX_NATIVE_CALL CNatives::SAMPAC_SetTickRate(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "SAMPAC_SetTickRate");

	int iTicks = params[1];
	if ( iTicks < 50 || iTicks >= INT_MAX )
		return logprintf("[SAMPAC]: SetTickRate: Can't set Tickrate (Min: 50, Max: %d)", INT_MAX), 1;
	set.g_iTicksMax = iTicks;
	return 1;
}

cell AMX_NATIVE_CALL CNatives::SAMPAC_SetDetectionState(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "SAMPAC_SetDetectionState");
	
	int iDetection = params[1];
	bool bState = !!params[2];
	if ( iDetection < 1 || iDetection > MAX_DETECTIONS )
		return logprintf("[SAMPAC]: SetDetectionState: Can't set State of unknown Detection (Min: 0, Max: %d)", MAX_DETECTIONS), 1;

	bIsDetectionEnabled[iDetection] = bState;

	return 1;
}

// Thanks Incognito for the technique, meh.
cell AMX_NATIVE_CALL CNatives::SAMPAC_CallbackHook(AMX *amx, cell *params)
{
	switch (static_cast<int>(params[1]))
	{
		case SAMPAC_OPC:
		{
			CHECK_PARAMS(2, "SAMPAC_CallbackHook");
			cell *playerid = NULL;
			amx_GetAddr(amx, params[2], &playerid);

			return static_cast<cell>(CallbackHooks::OnPlayerConnect(static_cast<int>(*playerid)));
		}
		case SAMPAC_OPDC:
		{
			CHECK_PARAMS(3, "SAMPAC_CallbackHook");
			cell *playerid = NULL, *reason = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &reason);
			
			return static_cast<cell>(CallbackHooks::OnPlayerDisconnect(static_cast<int>(*playerid), static_cast<int>(*reason)));
		}
		case SAMPAC_OPSC:
		{
			CHECK_PARAMS(4, "SAMPAC_CallbackHook");

			cell *playerid = NULL, *newstate = NULL, *oldstate = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &newstate);
			amx_GetAddr(amx, params[4], &oldstate);

			return static_cast<cell>(CallbackHooks::OnPlayerStateChange(static_cast<int>(*playerid), static_cast<int>(*newstate), static_cast<int>(*oldstate)));
		}
		case SAMPAC_OPPP:
		{
			CHECK_PARAMS(3, "SAMPAC_CallbackHook");

			cell *playerid = NULL, *pickupid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &pickupid);

			return static_cast<cell>(CallbackHooks::OnPlayerPickUpPickup(static_cast<int>(*playerid), static_cast<int>(*pickupid)));
		}
		case SAMPAC_OPD:
		{
			CHECK_PARAMS(4, "SAMPAC_CallbackHook");

			cell *playerid = NULL, *killerid = NULL, *reason = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &killerid);
			amx_GetAddr(amx, params[4], &reason);

			return static_cast<cell>(CallbackHooks::OnPlayerDeath(static_cast<int>(*playerid), static_cast<int>(*killerid), static_cast<int>(*reason)));
		}
		case SAMPAC_OPKSC:
		{
			CHECK_PARAMS(4, "SAMPAC_CallbackHook");

			cell *playerid = NULL, *keystateNew = NULL, *keystateOld = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[4], &keystateNew);
			amx_GetAddr(amx, params[3], &keystateOld);

			return static_cast<cell>(CallbackHooks::OnPlayerKeyStateChange(static_cast<int>(*playerid), static_cast<int>(*keystateNew), static_cast<int>(*keystateOld)));
		}
		case SAMPAC_OPRC:
		{
			CHECK_PARAMS(3, "SAMPAC_CallbackHook");

			cell *playerid = NULL, *classid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &classid);

			return static_cast<cell>(CallbackHooks::OnPlayerRequestClass(static_cast<int>(*playerid), static_cast<int>(*classid)));
		}
		case SAMPAC_OPTD:
		{							
			CHECK_PARAMS(6, "SAMPAC_CallbackHook");

			cell *playerid = NULL, *issuerid = NULL, *amount = NULL, *weaponid = NULL, *bodypart = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &issuerid);
			amx_GetAddr(amx, params[4], &amount);
			amx_GetAddr(amx, params[5], &weaponid);
			amx_GetAddr(amx, params[6], &bodypart);

			return static_cast<cell>(CallbackHooks::OnPlayerTakeDamage(static_cast<int>(*playerid), static_cast<int>(*issuerid), static_cast<float>(*amount), static_cast<int>(*weaponid), static_cast<int>(*bodypart)));
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL CNatives::SAMPAC_SetServerPingLimit(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "SAMPAC_SetServerPingLimit");

	int iTicks = params[1];
	if (iTicks < 50 || iTicks >= MAX_PING)
		return logprintf("[SAMPAC]: SetServerPingLimit: Can't set Tickrate (Min: 50, Max: %d)", 0xFFFF), 1;

	set.g_iTicksMax = iTicks;
	return 1;
}