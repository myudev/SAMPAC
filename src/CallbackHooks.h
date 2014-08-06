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

#ifndef CHOOKS_H
#define CHOOKS_H

#define SAMPAC_OPC (0)
#define SAMPAC_OPDC (1)
#define SAMPAC_OPSC (2)
#define SAMPAC_OPPP (3)
#define SAMPAC_OPD (4)
#define SAMPAC_OPKSC (5)

namespace CallbackHooks 
{
	bool OnPlayerConnect(int playerid);
	bool OnPlayerDisconnect(int playerid, int reason);
	bool OnPlayerStateChange(int playerid, int newstate, int oldstate);
	bool OnPlayerPickUpPickup(int playerid, int pickupid);
	bool OnPlayerDeath(int playerid, int killerid, int reason);
	bool OnPlayerUpdate(int playerid);
	bool OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys);
}

#endif