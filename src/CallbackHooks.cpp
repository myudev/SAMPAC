#include "main.h"
#include "CallbackHooks.h"
#include "CNatives.h"
#include "CAntiCheat.h"
#include "CPlayer.h"

bool CallbackHooks::OnPlayerConnect(int playerid)
{
	if (!CPlayer::IsNPC(playerid))
		return CAntiCheat::AddPlayer(playerid);

	return true;
}

bool CallbackHooks::OnPlayerDisconnect(int playerid, int reason)
{
	if (!CPlayer::IsNPC(playerid)) {
		return CAntiCheat::RemovePlayer(playerid);
	}

	return true;
}

bool CallbackHooks::OnPlayerStateChange(int playerid, int newstate, int oldstate)
{
	if (!CPlayer::IsNPC(playerid)) {
		CAntiCheat::CarWarpCheck(playerid, newstate);
		return true;
	}
	return true;
}

bool CallbackHooks::OnPlayerPickUpPickup(int playerid, int pickupid)
{
	if (!CPlayer::IsNPC(playerid)) {
		CAntiCheat::RapidPickupSpam(playerid, pickupid);
		return true;
	}
	return true;
}