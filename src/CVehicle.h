#ifndef _H_CVEHICLE
#define _H_CVEHICLE
#include "typedef.h"

namespace CVehicle {
	void GetPosition ( VEHICLEID playerID, float *fX, float *fY, float *fZ ) ;
	void GetVelocity ( VEHICLEID playerID, float *fX, float *fY, float *fZ ) ;
}
#endif