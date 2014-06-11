#include "main.h"
#include "CVehicle.h"
#include <sampgdk/a_samp.h>
#include <sampgdk/a_vehicles.h>


void CVehicle::GetPosition ( VEHICLEID vehicleID, float *fX, float *fY, float *fZ ) 
{
	if ( set.m_bSAMPHooks ) {
		
	} 
	else { // Fallback SAMPGDK :'(
		sampgdk_GetVehiclePos(vehicleID, fX, fY, fZ);
	}
}

void CVehicle::GetVelocity ( VEHICLEID vehicleID, float *fX, float *fY, float *fZ ) 
{
	if ( set.m_bSAMPHooks ) {
		
	} 
	else { // Fallback SAMPGDK :'(
		sampgdk_GetVehicleVelocity(vehicleID, fX, fY, fZ);
	}
}