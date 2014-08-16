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

#ifndef FHOOKS_H
#define FHOOKS_H

namespace CFunctionHooks
{
	cell AMX_NATIVE_CALL HookedGivePlayerWeapon(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL HookedResetPlayerWeapons(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL HookedSetSpawnInfo(AMX* amx, cell* params);

	cell AMX_NATIVE_CALL HookedAddPlayerClass(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL HookedAddPlayerClassEx(AMX* amx, cell* params);

	cell AMX_NATIVE_CALL HookedGivePlayerMoney(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL HookedGetPlayerMoney(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL HookedResetPlayerMoney(AMX* amx, cell* params);

	cell AMX_NATIVE_CALL HookedTogglePlayerSpectating(AMX* amx, cell* params);

	cell AMX_NATIVE_CALL HookedSetPlayerSpecialAction(AMX* amx, cell* params);

	cell AMX_NATIVE_CALL HookedSetPlayerHealth(AMX* amx, cell* params);
};

#endif