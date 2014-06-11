#ifndef MAIN_H
#define MAIN_H

#include <sampgdk/plugin.h>
#include <set>

typedef void (*logprintf_t)(const char*, ...);

extern logprintf_t logprintf;

// TODO: Put later in the right file :P
struct eSettings {
	bool m_bSAMPHooks;
	int g_iTicksMax;
};
extern eSettings set;
extern std::set<AMX*> pLAMXList;

#endif
