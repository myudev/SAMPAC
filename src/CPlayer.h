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

#ifndef _H_CPLAYER
#define _H_CPLAYER
#include "typedef.h"

namespace CPlayer {
	// Getting Data
	void GetPosition		(PLAYERID playerID, float *fX, float *fY, float *fZ);
	void GetVelocity		(PLAYERID playerID, float *fX, float *fY, float *fZ);

	void GetWeaponData		(PLAYERID playerID, short sIndex, int *iWeap, int *iAmmo);

	bool IsNPC				(PLAYERID playerID);

	VEHICLEID GetVehicle	(PLAYERID playerID);
	bool IsInVehicle		(PLAYERID playerID);

	void SetMoney			(PLAYERID playerID, int iMoney);
	void SetTeam			(PLAYERID playerID, int iTeam);
	int GetMoney			(PLAYERID playerID);
	int GetPing				(PLAYERID playerID);
	int GetState			(PLAYERID playerID);
	int GetWeapon			(PLAYERID playerID);
	int GetAnimationIndex	(PLAYERID playerID);
	int GetSpecialAction	(PLAYERID playerID);

	bool SetHealth			(PLAYERID playerID, float fHealth);
	bool SetArmour			(PLAYERID playerID, float fArmour);
	float GetHealth			(PLAYERID playerID);
	float GetArmour			(PLAYERID playerID);

	// Settings Data
	void SetPosition		(PLAYERID playerID, float fX, float fY, float fZ);
	void SetVelocity		(PLAYERID playerID, float fX, float fY, float fZ);
}
#endif