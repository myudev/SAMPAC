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
		return logprintf("[SAMPAC:] SetTickRate: Can't set Tickrate (Min: 50, Max: %d)", INT_MAX), 1;
	set.g_iTicksMax = iTicks;
	return 1;
}

cell AMX_NATIVE_CALL CNatives::SAMPAC_SetDetectionState(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "SAMPAC_SetDetectionState");
	
	int iDetection = params[1];
	bool bState = !!params[2];
	if ( iDetection < 1 || iDetection > MAX_DETECTIONS )
		return logprintf("[SAMPAC:] SetDetectionState: Can't set State of unknown Detection (Min: 0, Max: %d)", MAX_DETECTIONS), 1;

	bIsDetectionEnabled[iDetection] = bState;

	return 1;
}

// Thanks Incognito for the technique
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
			CHECK_PARAMS(3, "Streamer_CallbackHook");
			cell *playerid = NULL, *reason = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &reason);
			
			return static_cast<cell>(CallbackHooks::OnPlayerDisconnect(static_cast<int>(*playerid), static_cast<int>(*reason)));
		}
		case SAMPAC_OPSC:
		{
			CHECK_PARAMS(4, "Streamer_CallbackHook");

			cell *playerid = NULL, *newstate = NULL, *oldstate = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &newstate);
			amx_GetAddr(amx, params[4], &oldstate);

			return static_cast<cell>(CallbackHooks::OnPlayerStateChange(static_cast<int>(*playerid), static_cast<int>(*newstate), static_cast<int>(*oldstate)));
		}
		case SAMPAC_OPPP:
		{
			CHECK_PARAMS(3, "Streamer_CallbackHook");

			cell *playerid = NULL, *pickupid = NULL;
			amx_GetAddr(amx, params[2], &playerid);
			amx_GetAddr(amx, params[3], &pickupid);

			return static_cast<cell>(CallbackHooks::OnPlayerPickUpPickup(static_cast<int>(*playerid), static_cast<int>(*pickupid)));
		}
	}
	return 0;
}