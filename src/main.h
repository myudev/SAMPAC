/*
	PROJECT		<>	SA:MP Anticheat Plug-in
	LICENSE		<>	See LICENSE in the top level directory.
	AUTHOR(S)	<>	MyU (myudev0@gmail.com)
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
#include <sampgdk/a_samp.h>
#include "CSampServer.h"

typedef void (*logprintf_t)(const char*, ...);

extern logprintf_t logprintf;

// TODO: Put later in the right file :P
struct eSettings {
	int g_iTicksMax;
	int g_iMaxPing;
};
extern eSettings set;
extern std::set<AMX*> pLAMXList;

#endif
