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

CNetGame*			CSampServer::pServer = NULL;
eSampVersion		CSampServer::i_SAMPVersion = INVALID_VERSION;

void CSampServer::TryInitzializeSAMP()
{
	/* Before anyone asks, i am not using any patterns or SA:MP export as they can be removed also with this checking we ensure that we don't call free space and cause a corruption. */

	if ( pServer != NULL ) return;

	#ifdef WIN32
		#define ADDR_VERSION_03Z	(0x4B1BBC)
		#define ADDR_CNETGAME_03Z	(0x4F234C)

		#define ADDR_VERSION_03ZR2	(0x4B1CF4)
		#define ADDR_CNETGAME_03ZR2	(0x4F2370)

		#define ADDR_VERSION_03ZR3	(0x4B1B04)
		#define ADDR_CNETGAME_03ZR3	(0x4F339C)	
	#else
		#define ADDR_VERSION_03Z	(0x814F973)
		#define ADDR_CNETGAME_03Z	(0x819A564)

		#define ADDR_VERSION_03ZR2	(0x814FCF9)
		#define ADDR_CNETGAME_03ZR2	(0x819B8E4)

		#define ADDR_VERSION_03ZR3	(0x8150BCC)
		#define ADDR_CNETGAME_03ZR3	(0x819C9EC)
	#endif


#ifdef WIN32

	if (  strstr(((char*)ADDR_VERSION_03Z),  "0.3z") != NULL   ) // 0.3z SA:MP Server (0x4B1BBC is the SA:MP Version string).
	{
		pServer = *(CNetGame**)ADDR_CNETGAME_03Z;
		if ( pServer != NULL ) i_SAMPVersion = SAMP_03Z;
		logprintf ( "[ANTICHEAT:] Running in SA-MP 0.3z compatible mode.");
	}
	else if (  strstr(((char*)ADDR_VERSION_03ZR2),  "0.3z-R2") != NULL   )
	{
		pServer = *(CNetGame**)ADDR_CNETGAME_03ZR2;
		if ( pServer != NULL ) i_SAMPVersion = SAMP_03Z_R2;
		logprintf ( "[ANTICHEAT:] Running in SA-MP 0.3z-R2 compatible mode.");
	}
	else if (  strstr(((char*)ADDR_VERSION_03ZR3),  "0.3z-R3") != NULL  )
	{
		pServer = *(CNetGame**)ADDR_CNETGAME_03ZR3;

		if ( pServer != NULL ) i_SAMPVersion = SAMP_03Z_R3;
		logprintf ( "[ANTICHEAT:] Running in SA-MP 0.3z-R3 compatible mode.");
	}
	else { i_SAMPVersion = INVALID_VERSION; }

	//logprintf("%d = %d", i_SAMPVersion, INVALID_VERSION);
#else
	if (  strstr(((char*)ADDR_VERSION_03Z),  "0.3z") != NULL  ) // 0.3z SA:MP Server (0x4B1BBC is the SA:MP Version string).
	{
		pServer = *(CNetGame**)ADDR_CNETGAME_03Z;
		if ( pServer != NULL ) i_SAMPVersion = SAMP_03Z;
		logprintf ( "[ANTICHEAT:] Running in SA-MP 0.3z compatible mode.");
	}
	else if (  strstr(((char*)ADDR_VERSION_03ZR2),  "0.3z-R2") != NULL )
	{
		pServer = *(CNetGame**)ADDR_CNETGAME_03ZR2;
		if ( pServer != NULL ) i_SAMPVersion = SAMP_03Z_R2;
		logprintf ( "[ANTICHEAT:] Running in SA-MP 0.3z-R2 compatible mode.");
	}
	else if (  strstr(((char*)ADDR_VERSION_03ZR3),  "0.3z-R3") != NULL )
	{
		pServer = *(CNetGame**)ADDR_CNETGAME_03ZR3;
		if ( pServer != NULL ) i_SAMPVersion = SAMP_03Z_R3;
		logprintf ( "[ANTICHEAT:] Running in SA-MP 0.3z-R3 compatible mode.");
	}
	else { i_SAMPVersion = INVALID_VERSION; }
#endif
}


CSAMPPlayer* CSampServer::GetCPlayer(PLAYERID playerID)
{
	if ( !SAMP_IS_VALID_PLAYERID(playerID) ) return NULL;
	if ( pServer == NULL )					 return NULL;
	if ( pServer->pPlayerPool == NULL )      return NULL;
	
	return pServer->pPlayerPool->pPlayer[playerID];
}
