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
	SAMP_03Z_R2,
	SAMP_03Z_R3,
	SAMP_03Z_R4
};



// Here belongs memory h4xoring stuff.


#define PAD(a, b)			char a[b]
//#define BOOL				bool // im dumb lol...
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



// -- RAKNET

#ifdef WIN32
struct PlayerID
{
	unsigned int binaryAddress;
	unsigned short port;
};
typedef unsigned int RakNetTime;
typedef unsigned short PlayerIndex;

struct Packet
{
	PlayerIndex playerIndex;
	PlayerID playerId;
	unsigned int length;
	unsigned int bitSize;
	unsigned char* data;
	bool deleteData;
};

struct RPCParameters
{
	unsigned char *input;
	unsigned int numberOfBitsOfData;
	PlayerID sender;
	void *recipient;
	RakNet::BitStream *replyToSender;
};

enum PacketPriority
{
    SYSTEM_PRIORITY,
    HIGH_PRIORITY,  
    MEDIUM_PRIORITY,
    LOW_PRIORITY,  
    NUMBER_OF_PRIORITIES
};

enum PacketReliability
{
	UNRELIABLE = 6,   /// Same as regular UDP, except that it will also discard duplicate datagrams.  RakNet adds (6 to 17) + 21 bits of overhead, 16 of which is used to detect duplicate packets and 6 to 17 of which is used for message length.
	UNRELIABLE_SEQUENCED,  /// Regular UDP with a sequence counter.  Out of order messages will be discarded.  This adds an additional 13 bits on top what is used for UNRELIABLE.
	RELIABLE,   /// The message is sent reliably, but not necessarily in any order.  Same overhead as UNRELIABLE.
	RELIABLE_ORDERED,   /// This message is reliable and will arrive in the order you sent it.  Messages will be delayed while waiting for out of order messages.  Same overhead as UNRELIABLE_SEQUENCED.
	RELIABLE_SEQUENCED /// This message is reliable and will arrive in the sequence you sent it.  Out or order messages will be dropped.  Same overhead as UNRELIABLE_SEQUENCED.
};

class RakServer
{
public:
	~RakServer();
	virtual bool Start( unsigned short AllowedPlayers, unsigned int depreciated, int threadSleepTimer, unsigned short port, const char *forceHostAddress=0 );
	virtual void InitializeSecurity( const char *privateKeyE, const char *privateKeyN );
	virtual void DisableSecurity( void );
	virtual void SetPassword( const char *_password );
	virtual bool HasPassword( void );
	virtual void Disconnect( unsigned int blockDuration, unsigned char orderingChannel=0 );
	virtual bool Send(const char *data, const int length, int priority, int reliability, char orderingChannel, PlayerID playerId, bool broadcast);
	virtual bool Send(RakNet::BitStream* parameters, int priority, int reliability, unsigned orderingChannel, PlayerID playerId, bool broadcast);
	virtual void _20(); // Packet* Receive( void );
	virtual void Kick( const PlayerID playerId );
	virtual void _28();
	virtual void _2C();
	virtual void _30();
	virtual void _34();
	virtual void _38();
	virtual void _3C();
	virtual void _40();
	virtual void _44();
	virtual void _48();
	virtual int GetLastPing( const PlayerID playerId );
	virtual void _50();
	virtual void _54();
	virtual void _58();
	virtual void _5C();
	virtual void _60();
	virtual void _64();
	virtual void _68();
	virtual void _6C();
	virtual void anyad();
	virtual void RegisterAsRemoteProcedureCall( int* uniqueID, void ( *functionPointer ) ( RPCParameters *rpcParms ) );
	virtual void RegisterClassMemberRPC( int* uniqueID, void *functionPointer );
	virtual void UnregisterAsRemoteProcedureCall( int* uniqueID );
	virtual bool RPC(int* uniqueID, RakNet::BitStream* parameters, int priority, int reliability, unsigned orderingChannel, PlayerID playerId, bool broadcast, bool shiftTimestamp);
	virtual void _84();
	virtual void _88();
	virtual void _8C();
	virtual void _90();
	virtual void _94();
	virtual void _98();
	virtual void _9C();
	virtual void _A0();
	virtual void _A4();
	virtual void _A8();
	virtual void _AC();
	virtual void _B0();
	virtual void _B4();
	virtual void _B8();
	virtual void _BC();
	virtual void _C0();
	virtual void _C4();
	virtual void _C8();
	virtual void _CC();
	virtual const char* GetLocalIP( unsigned int index );
	virtual PlayerID GetInternalID( void ) const;
	virtual void PushBackPacket( Packet *packet, bool pushAtHead );
	virtual void SetRouterInterface( void *routerInterface );
	virtual void RemoveRouterInterface( void *routerInterface );
	virtual int GetIndexFromPlayerID( PlayerID playerId ); // E4
	virtual PlayerID GetPlayerIDFromIndex( int index ); // E8
	virtual void AddToBanList( const char *IP, unsigned int milliseconds=0 );
	virtual void RemoveFromBanList( const char *IP );
	virtual void ClearBanList( void );
	virtual bool IsBanned( const char *IP );
	virtual bool IsActivePlayerID( const PlayerID playerId );
	virtual void SetTimeoutTime( RakNetTime timeMS, const PlayerID target );
	virtual bool SetMTUSize( int size );
	virtual int GetMTUSize( void ) const;
	virtual void AdvertiseSystem( const char *host, unsigned short remotePort, const char *data, int dataLength );
	virtual void * const GetStatistics( const PlayerID playerId ); /* retn RakNetStatisticsStruct */
	virtual void ApplyNetworkSimulator( double maxSendBPS, unsigned short minExtraPing, unsigned short extraPingVariance);

};


#else

class RakServer
{
public:
	~RakServer();
	virtual void _0();
	virtual void _4();
	virtual void _8();
	virtual void _C();
	virtual void _10();
	virtual void _14();
	virtual void _18();
	virtual void _1C();
	virtual void _20();
	virtual bool Send(RakNet::BitStream* parameters, int priority, int reliability, unsigned orderingChannel, PlayerID playerId, bool broadcast);
	virtual void _28();
	virtual void _2C();
	virtual void _30();
	virtual void _34();
	virtual void _38();
	virtual void _3C();
	virtual void _40();
	virtual void _44();
	virtual void _48();
	virtual void _4C();
	virtual int GetLastPing( const PlayerID playerId );
	virtual void _54();
	virtual void _58();
	virtual void _5C();
	virtual void _60();
	virtual void _64();
	virtual void _68();
	virtual void _6C();
	virtual void _70();
	virtual void _74();
	virtual void _78();
	virtual void _7C();
	virtual void _80();
	virtual void _84();
	virtual void _88();
	virtual bool RPC(int* uniqueID, RakNet::BitStream* parameters, int priority, int reliability, unsigned orderingChannel, PlayerID playerId, bool broadcast, bool shiftTimestamp);
	virtual void _90();
	virtual void _94();
	virtual void _98();
	virtual void _9C();
	virtual void _A0();
	virtual void _A4();
	virtual void _A8();
	virtual void _AC();
	virtual void _B0();
	virtual void _B4();
	virtual void _B8();
	virtual void _BC();
	virtual void _C0();
	virtual void _C4();
	virtual void _C8();
	virtual void _CC();
	virtual void _D0();
	virtual void _D4();
	virtual void _D8();
	virtual void _DC();
	virtual void _E0();
	virtual void _E8();
	virtual int GetIndexFromPlayerID( PlayerID playerId );
	virtual PlayerID GetPlayerIDFromIndex( int index );
	virtual void AddToBanList( const char *IP, unsigned int milliseconds=0 );
	virtual void RemoveFromBanList( const char *IP );
	virtual void ClearBanList( void );
	virtual bool IsBanned( const char *IP );
};
#endif

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
	Vec3 vecPos;
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
		PAD(pad1,44);											// 0x0010 - 0x003C
		RakServer				*pRakServer;					// 0x002C - 0x003C
		PAD(pad2,60);											// 0x003C - 0x007C
		BYTE					pad3;							// 0x007C - 0x007D
		#ifndef WIN32 
			double pad3; 
		#endif
		int						iSpawnAvailable;				// 0x007D - 0x0081
		SPAWN_INFO				m_AvailableSpawns[MAX_CLASSES]; // 0x0081 - 0x3669
};
#pragma pack(pop)

struct RPCS {
	int RPC_SET_POS;
	int RPC_SET_VELOCITY;
};

namespace CSampServer {
	void			TryInitzializeSAMP();
	CSAMPPlayer*	GetCPlayer(PLAYERID playerID);

	extern RPCS				rpcIDS;
	extern CNetGame*		pServer;
	extern eSampVersion		i_SAMPVersion;
};

#endif