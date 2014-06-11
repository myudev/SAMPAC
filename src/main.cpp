#include "main.h"
#include "CAntiCheat.h"
#include "CPlayer.h"
#include "CNatives.h"
#include "typedef.h"
#include <sampgdk/core.h>
#include <sampgdk/plugin.h>

logprintf_t logprintf;
std::set<AMX*> pLAMXList;

eSettings set;

int g_iTicksDone;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppPluginData)
{
	sampgdk_initialize_plugin(ppPluginData);
	logprintf = (logprintf_t)ppPluginData[PLUGIN_DATA_LOGPRINTF];
	CAntiCheat::Init();

	// Lazy Check by Version check
	// TODO: Move it to an more advanced Version Support System (backward compatiblity)
	// Reserach abit, you can find CNetGame here: 0x4F23C4 (0.3x R2 Patch 1)
	if ( strcmp(((char*)0x4AD374),  "0.3x-R2") ) {
		// set.m_bSAMPHooks = true; // not for now.
	} 
	else set.m_bSAMPHooks = false;

	set.g_iTicksMax = 100; // Default Tick(s)

	for ( int it = 0; it != MAX_DETECTIONS; it ++ )
		bIsDetectionEnabled[it] = true; // default enabled.

	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{

}

AMX_NATIVE_INFO sNatives[] =
{
	{ "SAMPAC_SetTickRate", CNatives::SAMPAC_SetTickRate },
	{ "SAMPAC_SetDetectionState", CNatives::SAMPAC_SetDetectionState },
	{ 0, 0 }
};

#define USENAMETABLE(hdr) \
	((hdr)->defsize==sizeof(AMX_FUNCSTUBNT))

#define NUMENTRIES(hdr,field,nextfield) \
	(unsigned)(((hdr)->nextfield - (hdr)->field) / (hdr)->defsize)

#define GETENTRY(hdr,table,index) \
	(AMX_FUNCSTUB *)((unsigned char*)(hdr) + (unsigned)(hdr)->table + (unsigned)index*(hdr)->defsize)

#define GETENTRYNAME(hdr,entry) \
	(USENAMETABLE(hdr) ? \
		(char *)((unsigned char*)(hdr) + (unsigned)((AMX_FUNCSTUBNT*)(entry))->nameofs) : \
		((AMX_FUNCSTUB*)(entry))->name)

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	pLAMXList.insert(amx);

	// Code (C) Y_LESS in his SSCANF
	int num,idx;
	AMX_HEADER *
		hdr = (AMX_HEADER *)amx->base;
	AMX_FUNCSTUB *
		func;
	num = NUMENTRIES(hdr, natives, libraries);
	for (idx = 0; idx != num; ++idx)
	{
		func = GETENTRY(hdr, natives, idx);
		
		if ( bIsDetectionEnabled[CHEAT_TYPE_WEAPON] ) {
			if (!strcmp("GivePlayerWeapon", GETENTRYNAME(hdr, func)))
				func->address = (ucell)CAntiCheat::HookedGivePlayerWeapon;

			if (!strcmp("ResetPlayerWeapons", GETENTRYNAME(hdr, func)))
				func->address = (ucell)CAntiCheat::HookedResetPlayerWeapons;
		}

		if ( bIsDetectionEnabled[CHEAT_TYPE_MONEY] ) {
			if (!strcmp("GivePlayerMoney", GETENTRYNAME(hdr, func)))
				func->address = (ucell)CAntiCheat::HookedGivePlayerMoney;

			if (!strcmp("GetPlayerMoney", GETENTRYNAME(hdr, func)))
				func->address = (ucell)CAntiCheat::HookedGetPlayerMoney;

			if (!strcmp("ResetPlayerMoney", GETENTRYNAME(hdr, func)))
				func->address = (ucell)CAntiCheat::HookedResetPlayerMoney;
			
		}

		if ( bIsDetectionEnabled[CHEAT_TYPE_SPECTATE] ) {
			if (!strcmp("TogglePlayerSpectating", GETENTRYNAME(hdr, func)))
				func->address = (ucell)CAntiCheat::HookedTogglePlayerSpectating;			
		}

	}

	return amx_Register(amx, sNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	pLAMXList.erase(amx);
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	// 0x: Server works in ticks, so this is the best solution for delay.
	if ( g_iTicksDone >= set.g_iTicksMax ) {
		CAntiCheat::Tick();
		g_iTicksDone = 0;
	}
	g_iTicksDone++;
}

// Dirty dirty.
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid)
{
	if ( !CPlayer::IsNPC(playerid) )
		return CAntiCheat::AddPlayer(playerid);

	return true;
}
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid,int reason)
{
	if ( !CPlayer::IsNPC(playerid) ) {
		CAntiCheat::RemovePlayer(playerid);
		return true;
	}

	return true;
}
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStateChange(int playerid, int newstate, int oldstate)
{
	if ( !CPlayer::IsNPC(playerid) ) {
		CAntiCheat::CarWarpCheck(playerid, newstate);
		return true;
	}

	return true;
}
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerPickUpPickup(int playerid, int pickupid)
{
	if ( !CPlayer::IsNPC(playerid) ) {
		CAntiCheat::RapidPickupSpam( playerid, pickupid );
		return true;
	}
	return true;
}