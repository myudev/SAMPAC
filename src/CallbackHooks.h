#ifndef CHOOKS_H
#define CHOOKS_H

#define SAMPAC_OPC (0)
#define SAMPAC_OPDC (1)
#define SAMPAC_OPSC (2)
#define SAMPAC_OPPP (3)

namespace CallbackHooks 
{
	bool OnPlayerConnect(int playerid);
	bool OnPlayerDisconnect(int playerid, int reason);
	bool OnPlayerStateChange(int playerid, int newstate, int oldstate);
	bool OnPlayerPickUpPickup(int playerid, int pickupid);
}

#endif