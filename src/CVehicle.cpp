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

#include "main.h"
#include "CVehicle.h"
#include <sampgdk/a_samp.h>
#include <sampgdk/a_vehicles.h>


void CVehicle::GetPosition ( VEHICLEID vehicleID, float *fX, float *fY, float *fZ ) 
{
	if ( CSampServer::i_SAMPVersion != INVALID_VERSION ) {
		
	} 
	else { // Fallback SAMPGDK :'(
		sampgdk_GetVehiclePos(vehicleID, fX, fY, fZ);
	}
}

void CVehicle::GetVelocity ( VEHICLEID vehicleID, float *fX, float *fY, float *fZ ) 
{
	if ( CSampServer::i_SAMPVersion != INVALID_VERSION ) {
		
	} 
	else { // Fallback SAMPGDK :'(
		sampgdk_GetVehicleVelocity(vehicleID, fX, fY, fZ);
	}
}

float CVehicle::GetDistanceFromPoint(VEHICLEID vehicleID, float fX, float fY, float fZ)
{
	if (CSampServer::i_SAMPVersion != INVALID_VERSION) {
		return 0.0f;
	}
	else { // Fallback SAMPGDK :'(
		return sampgdk_GetVehicleDistanceFromPoint(vehicleID, fX, fY, fZ);
	}
}

int CVehicle::GetModel(VEHICLEID vehicleID)
{
	if (CSampServer::i_SAMPVersion != INVALID_VERSION) {
		return INVALID_VEHICLE_ID;
	}
	else { // Fallback SAMPGDK :'(
		return sampgdk_GetVehicleModel(vehicleID);
	}
}