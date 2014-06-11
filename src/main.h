#ifndef MAIN_H
#define MAIN_H

#include <sampgdk/plugin.h>
#include <set>

// OS includes
#ifdef _WIN32
#include <windows.h>
#else
#include "unistd.h"
#include <sys/mman.h>
#endif

#ifndef _WIN32 
#define BOOL		int
#define DWORD		unsigned long
#define BYTE		unsigned char
#define WORD		unsigned short
#define TRUE		(1)
#define FALSE		(0)
#define STDCALL	
#else
#	define STDCALL	__stdcall
#endif


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> 
#include <math.h>
#include <string.h>
#include "typedef.h"
#include "CSampServer.h"
typedef void (*logprintf_t)(const char*, ...);

extern logprintf_t logprintf;

// TODO: Put later in the right file :P
struct eSettings {
	int g_iTicksMax;
};
extern eSettings set;
extern std::set<AMX*> pLAMXList;

#endif
