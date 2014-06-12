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

	if (  strcmp(((char*)0x4B1BBC),  "0.3z")  ) // 0.3z SA:MP Server (0x4B1BBC is the SA:MP Version string).
	{
		i_SAMPVersion = SAMP_03Z;	
		pServer = *(CNetGame**)0x4F234C;
	}
	else if (  strcmp(((char*)0x4B1CF4),  "0.3z-R2")  )
	{
		i_SAMPVersion = SAMP_03Z_R2;
		pServer = *(CNetGame**)0x4F2370;
	}
	else { i_SAMPVersion = INVALID_VERSION; }


#else
	if (  strcmp(((char*)0x814F973),  "0.3z")  ) // 0.3z SA:MP Server (0x4B1BBC is the SA:MP Version string).
	{
		i_SAMPVersion = SAMP_03Z;	
		pServer = *(CNetGame**)0x819A564;
	}
	else if (  strcmp(((char*)0x814FCF9),  "0.3z-R2")  )
	{
		i_SAMPVersion = SAMP_03Z_R2;
		pServer = *(CNetGame**)0x819B8E4;
	}
	else { i_SAMPVersion = INVALID_VERSION; }
#endif
}


CSAMPPlayer* CSampServer::GetCPlayer(PLAYERID playerID)
{
	if ( !SAMP_IS_VALID_PLAYERID(playerID) ) return NULL;

	return pServer->pPlayerPool->pPlayer[playerID];
}