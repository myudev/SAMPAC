/*
	PROJECT		<>	SA:MP Anticheat Plug-in
	LICENSE		<>	See LICENSE in the top level directory.
	AUTHOR(S)	<>	MyU (myudev0@gmail.com)
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
	{ "SAMPAC_CallbackHook", CNatives::SAMPAC_CallbackHook },
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

		CSampServer::TryInitzializeSAMP();

		g_iTicksDone = 0;
	}
	g_iTicksDone++;
}