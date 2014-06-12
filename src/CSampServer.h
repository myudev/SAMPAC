/*
	PROJECT		<>	SA:MP Anticheat Plug-in
	LICENSE		<>	See LICENSE in the top level directory.
	AUTHOR(S)	<>	MyU (myudev0@gmail.com), OrMiscL (insert mail here)
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

#ifndef _H_CSampServer
#define _H_CSampServer

enum eSampVersion {
	INVALID_VERSION,
	SAMP_03Z,
	SAMP_03Z_R2
};




// Here belongs memory h4xoring stuff.
#define PAD(a, b)			char a[b]
#define BOOL				bool
#define WORD				unsigned int
#define BYTE				byte
/*
SAMPGDK defines them but we should define them somewhere too (1000p version)
#define MAX_PLAYERS			500
#define MAX_VEHICLES		2000
#define MAX_NAME_LENGTH		24
#define NO_TEAM				255
*/
#define MAX_CLASSES			300
#define SAMP_IS_VALID_PLAYERID(pid) ((pid < MAX_PLAYERS && pid > -1)?true:false)

#pragma pack(push, 1)
class CSyncData
{
	public:
		WORD			wUDAnalog;				// 0x0076 - 0x0078
		WORD			wLRAnalog;				// 0x0078 - 0x007A
		WORD			wKeys;					// 0x007A - 0x007C
		Vec3		vecPosition;			// 0x007C - 0x0088
		float			fQuaternionAngle;		// 0x0088 - 0x008C
		Vec3		vecQuaternion;			// 0x008C - 0x0098
		BYTE			byteHealth;				// 0x0098 - 0x0099
		BYTE			byteArmour;				// 0x0099 - 0x009A
		BYTE			byteWeapon;				// 0x009A - 0x009B
		BYTE			byteSpecialAction;		// 0x009B - 0x009C
		Vec3		vecVelocity;			// 0x009C - 0x00A8
		Vec3		vecSurfing;				// 0x00A8 - 0x00B4
		WORD			wSurfingInfo;			// 0x00B4 - 0x00B6
		int				iAnimationId;			// 0x00B6 - 0x00BA
		// Size = 0x44

};
#pragma pack(pop)

#pragma pack(push, 1)
class CAimSyncData
{
	public:
		BYTE			byteCameraMode;			// 0x0000 - 0x0001
		Vec3		vecFront;				// 0x0001 - 0x000D
		Vec3		vecPosition;			// 0x000D - 0x0019
		float			fZAim;					// 0x0019 - 0x001D
		BYTE			byteWeaponState;		// 0x001D - 0x001E
		PAD(pad0, 1);							// 0x001E - 0x001F
		// Size = 0x1F

};
#pragma pack(pop)

#pragma pack(push, 1)
class CVehicleSyncData
{
	public:
		WORD			wVehicleId;				// 0x001F - 0x0021
		WORD			wUDAnalog;				// 0x0021 - 0x0023
		WORD			wLRAnalog;				// 0x0023 - 0x0025
		WORD			wKeys;					// 0x0025 - 0x0027
		float			fQuaternionAngle;		// 0x0027 - 0x002B
		Vec3		vecQuaternion;			// 0x002B - 0x0037
		Vec3		vecPosition;			// 0x0037 - 0x0043
		Vec3		vecVelocity;			// 0x0043 - 0x004F
		float			fHealth;				// 0x004F - 0x0053
		BYTE			bytePlayerHealth;		// 0x0053 - 0x0054
		BYTE			bytePlayerArmour;		// 0x0054 - 0x0055
		BYTE			bytePlayerWeapon;		// 0x0055 - 0x0056
		BYTE			byteSirenState;			// 0x0056 - 0x0057
		PAD(pad0, 7);							// 0x0057 - 0x005E
		// Size = 0x3F

};
#pragma pack(pop)

#pragma pack(push, 1)
class CPassengerSyncData
{
	public:
		WORD			wVehicleId;				// 0x005E - 0x0060
		BYTE			byteSeatId;				// 0x0060 - 0x0061
		BYTE			bytePlayerWeapon;		// 0x0061 - 0x0062
		BYTE			bytePlayerHealth;		// 0x0062 - 0x0063
		BYTE			bytePlayerArmour;		// 0x0063 - 0x0064
		WORD			wUDAnalog;				// 0x0064 - 0x0066
		WORD			wLRAnalog;				// 0x0066 - 0x0068
		WORD			wKeys;					// 0x0068 - 0x006A
		Vec3		vecPosition;			// 0x006A - 0x0076
		// Size = 0x18

};
#pragma pack(pop)

#pragma pack(push, 1)
class CSAMPPlayer
{
	public:
		CAimSyncData		aimSyncData;		// 0x0000 - 0x001F
		CVehicleSyncData	vehicleSyncData;	// 0x001F - 0x005E
		CPassengerSyncData	passengerSyncData;	// 0x005E - 0x0076
		CSyncData			syncData;			// 0x0076 - 0x00BA
		PAD(pad1, 8803);						// 0x00BA - 0x231D
		BOOL				bUpdateKeys;		// 0x231D - 0x2321
		Vec3			vecPosition;		// 0x2321 - 0x232D
		float				fHealth;			// 0x232D - 0x2331
		float				fArmour;			// 0x2331 - 0x2335
		PAD(pad2, 16);							// 0x2335 - 0x2345
		float				fAngle;				// 0x2345 - 0x2349
		Vec3			vecVelocity;		// 0x2349 - 0x2355
		WORD				wUDAnalog;			// 0x2355 - 0x2357
		WORD				wLRAnalog;			// 0x2357 - 0x2359
		DWORD				dwKeys;				// 0x2359 - 0x235D
		DWORD				dwOldKeys;			// 0x235D - 0x2361
		PAD(pad3, 18);							// 0x2361 - 0x2373
		WORD				wPlayerId;			// 0x2373 - 0x2375 
		int					iUpdateState;		// 0x2375 - 0x2379 
		PAD(pad4, 564);							// 0x2379 - 0x25AD
		BOOL				bHasAimSync;		// 0x25AD - 0x25B1
		BOOL				bHasUnkSync;		// 0x25B1 - 0x25B5
		BOOL				bHasUnk2Sync;		// 0x25B5 - 0x25B9
		BYTE				byteState;			// 0x25B9 - 0x25BA
		PAD(pad5, 84);							// 0x25BA - 0x260E
		int					iSkinId;			// 0x260E - 0x2612
		PAD(pad6, 1);							// 0x2612 - 0x2613
		Vec3			vecSpawnPosition;	// 0x2613 - 0x261F
		PAD(pad7, 28);							// 0x261F - 0x263B
		BOOL				bReadyToSpawn;		// 0x263B - 0x263F
		PAD(pad8, 2);							// 0x263F - 0x2641
		BYTE				byteSeatId;			// 0x2641 - 0x2642
		WORD				wVehicleId;			// 0x2642 - 0x2644
		PAD(pad9, 12);							// 0x2644 - 0x2650
		int					iInteriorId;		// 0x2650 - 0x2654
		WORD				wWeaponAmmo[12];	// 0x2654 - 0x266C
		PAD(pad10, 28);							// 0x266C - 0x2688
		BYTE				byteWeaponId[12];	// 0x2688 - 0x2694
		PAD(pad11, 2);							// 0x2694 - 0x2696
		WORD				wTargetId;			// 0x2696 - 0x2698
		PAD(pad12, 31);							// 0x2698 - 0x26B7
		// Size = 0x26B7

};
#pragma pack(pop)

#pragma pack(push, 1)
class CSAMPVehicle
{
	public:
		Vec3		vecPosition;		// 0x0000 - 0x000C
		float			fQuaternionAngle;	// 0x000C - 0x0010
		Vec3		vecQuaternion;		// 0x0010 - 0x001C
		PAD(pad0, 48);						// 0x001C - 0x004C
		Vec3		vecVelocity;		// 0x004C - 0x0058
		PAD(pad1, 42);						// 0x0058 - 0x0082
		int				iModelId;			// 0x0082 - 0x0086
		PAD(pad2, 32);						// 0x0086 - 0x00A6
		float			fHealth;			// 0x00A6 - 0x00AA


};
#pragma pack(pop)

#pragma pack(push, 1)
class CSAMPVehiclePool
{
	public:
		PAD(pad0, 16212);										// 0x0000 - 0x3F54
		CSAMPVehicle		*pVehicle[MAX_VEHICLES];			// 0x3F54 - 0x5E94
};
#pragma pack(pop)

#pragma pack(push, 1)
class CSAMPPlayerPool
{
public:
	char	_pad[75012]; //0x0000 
	BOOL bIsPlayerConnected[MAX_PLAYERS]; //0x12504 
	CSAMPPlayer *pPlayer[MAX_PLAYERS]; //0x12CD4 
	char szName[MAX_PLAYERS][MAX_PLAYER_NAME]; //0x134A4 
	BOOL bUnk[MAX_PLAYERS]; // 0x16384
	BOOL bIsAdmin[MAX_PLAYERS]; //0x16578 
	BOOL mIsNPC[MAX_PLAYERS]; //0x16D48 

};//Size=0x17518
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct SPAWN_INFO
{
	BYTE bTeam;
	int iSkin;
	BYTE byteUnk; // something releated to ???
	Vec3 vecPos[3];
	float fRotation;
	int iSpawnWeapons[3];
	int iSpawnWeaponsAmmo[3];
} PLAYER_SPAWN_INFO;
#pragma pack(pop)

#pragma pack(push, 1)
class CNetGame
{
	public:
		void					*pGameModePool;					// 0x0000 - 0x0004
		void					*pFilterScriptPool;				// 0x0004 - 0x0008
		CSAMPPlayerPool			*pPlayerPool;					// 0x0008 - 0x000C
		CSAMPVehiclePool		*pVehiclePool;					// 0x000C - 0x0010
		PAD(pad1,0x6D);											// 0x0010 - 0x007D
		int						iSpawnAvailable;				// 0x007D - 0x0081
		SPAWN_INFO				m_AvailableSpawns[MAX_CLASSES]; // 0x0081 - 0x3669
};
#pragma pack(pop)


namespace CSampServer {
	void			TryInitzializeSAMP();
	CSAMPPlayer*	GetCPlayer(PLAYERID playerID);

	extern CNetGame*		pServer;
	extern eSampVersion		i_SAMPVersion;
};

#endif