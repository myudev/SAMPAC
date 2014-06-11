#ifndef _H_ANTICHEAT
#define _H_ANTICHEAT
#include "typedef.h"


#define MAX_WEAPS ( 55 )
#define SAMP_MAX_PLAYERS	( 1000 )

// TODO: Cleanup
#define MAX_DETECTIONS 5
enum eCheatType {
	CHEAT_TYPE_WEAPON,
	CHEAT_TYPE_CARWARP,
	CHEAT_TYPE_MONEY,
	CHEAT_TYPE_PLAYERBUGGER,
	CHEAT_TYPE_PICKUP_SPAM,
	CHEAT_TYPE_SPECTATE
};
extern bool bIsDetectionEnabled[MAX_DETECTIONS];

struct ePlayerData {
	int iPlayerID;
	bool bHasWeapon [ MAX_WEAPS ];	

	int iPlayerMoney;

	int iCarWarpVehicleID;
	int iCarWarpTimeStamp;
	int iState;

	int iLastPickupID;
	int iPickupTimestamp;
	bool bHasPermissionToSpectate;

	Vec3 vLastPickupPos;
	Vec3 vLastValidPos;

};

namespace CAntiCheat {
	void	Init ( void );
	void	Tick ( void );
	void	OnDetect(ePlayerData *pPlayer, eCheatType eCheatType, const char *fmt, ...);

	bool	AddPlayer(PLAYERID playerID);
	bool	RemovePlayer(PLAYERID playerID);

	void 	CarWarpCheck(PLAYERID playerID, NEWSTATE stateNEW);
	void 	RapidPickupSpam(PLAYERID playerID, PICKUPID pickupID);
	ePlayerData* GetPlayerByID(PLAYERID playerID);
	// Hooked Things
	cell AMX_NATIVE_CALL HookedGivePlayerWeapon( AMX* amx, cell* params );
	cell AMX_NATIVE_CALL HookedResetPlayerWeapons( AMX* amx, cell* params );

	cell AMX_NATIVE_CALL HookedGivePlayerMoney( AMX* amx, cell* params );
	cell AMX_NATIVE_CALL HookedGetPlayerMoney( AMX* amx, cell* params );
	cell AMX_NATIVE_CALL HookedResetPlayerMoney( AMX* amx, cell* params );

	cell AMX_NATIVE_CALL HookedTogglePlayerSpectating( AMX* amx, cell* params );
	

};

#endif