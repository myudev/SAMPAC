#ifndef NATIVES_H
#define NATIVES_H

#include <sampgdk/plugin.h>

#define CHECK_PARAMS(m, n) \
	if (params[0] != (m * 4)) \
	{ \
	logprintf("[SAMPAC:] %s: Expecting %d parameter(s), but found %d", n, m, params[0] / 4); \
	return 0; \
	}

namespace CNatives
{
	cell AMX_NATIVE_CALL SAMPAC_SetTickRate(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL SAMPAC_SetDetectionState(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL SAMPAC_CallbackHook(AMX *amx, cell *params);
}
#endif