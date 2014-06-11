#ifndef _H_CPLAYER
#define _H_CPLAYER
#include "typedef.h"

namespace CPlayer {
	// Getting Data
	void GetPosition ( PLAYERID playerID, float *fX, float *fY, float *fZ ) ;
	void GetVelocity ( PLAYERID playerID, float *fX, float *fY, float *fZ ) ;

	void GetWeaponData ( PLAYERID playerID, short sIndex, int *iWeap, int *iAmmo ) ;

	bool IsNPC ( PLAYERID playerID ) ;

	VEHICLEID GetVehicle ( PLAYERID playerID ) ;

	void SetMoney ( PLAYERID playerID, int iMoney ) ;
	int GetMoney ( PLAYERID playerID ) ;

	int GetState ( PLAYERID playerID );

	// Settings Data
	void SetPosition ( PLAYERID playerID, float fX, float fY, float fZ ) ;
	void SetVelocity ( PLAYERID playerID, float fX, float fY, float fZ ) ;
}
#endif