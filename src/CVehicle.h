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

#ifndef _H_CVEHICLE
#define _H_CVEHICLE
#include "typedef.h"

namespace CVehicle {
	void GetPosition ( VEHICLEID playerID, float *fX, float *fY, float *fZ ) ;
	void GetVelocity ( VEHICLEID playerID, float *fX, float *fY, float *fZ ) ;

	float GetDistanceFromPoint(VEHICLEID vehicleID, float fX, float fY, float fZ);
	float GetSpeedInKPH(VEHICLEID vehicleID);

	int GetModel( VEHICLEID vehicleID ) ;
}
#endif