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

#include "typedef.h"
// SA:MP Structures ( :P )
// Needs research:
// - Player Pool
// - Vehicle Pool


#define SAMP_MAX_CLASSES ( 300 )

#pragma pack(1)
typedef struct _CLASS_INFO {
	BYTE unk; // everytime 0 ?
	int p_iSkin; // yep, actual skin of  that class
	BYTE unk1;
	Vec3 p_vSpawnPos;
	FLOAT p_fRotation;
	int m_iSpawnWeap[3];
	int m_iSpawnWeapAmmo[3];
} CLASS_INFO;

#pragma pack(push, 1) // otherwise it would not align like it should.
class CNetGame {
	void *p_GameModeSmth; // has something todo with gamemodes (pool?)
	void *p_FilterScriptSmth; // has something todo with filterscripts (pool?)
	void *p_PlayerPool; // That's is what we needing :P
	void *p_VehiclePool; // also
	char unk[0x6D]; // overjump some crap
	int  p_iSpawnsAvailable; // aka Classes
	_CLASS_INFO m_cClasses[SAMP_MAX_CLASSES];
};
#pragma pack(pop)