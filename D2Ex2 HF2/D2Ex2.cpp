/*==========================================================
* D2Ex2
* https://github.com/lolet/D2Ex2
* ==========================================================
* Copyright (c) 2011-2014 Bartosz Jankowski
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
* ==========================================================
*/

#include "stdafx.h"
#include "D2Ex2.h"

#include <sstream>
#include <process.h>

//-Must be
#include "Vars.h"
#define  __DEFINE_VARS
#include "Vars.h"

#define __DEFINE_EXPTRS
#ifdef VER_113D
#include "D2ExPointers_113D.h"
#else
#include "D2ExPointers_111B.h"
#endif

//--Structs
#include "Misc.h"
#include "Offset.h"

//-Program elements

#include "ExExtendedLevels.h"
#include "ExMPQ.h"

static HMODULE gModule;
static HANDLE Handle;
static HANDLE hEvent;
static HANDLE hAimEvent;
static unsigned Id;

BOOL D2Ex::Init()
{
	Misc::Log("Defining offsets...");
	SetupD2Vars();
	SetupD2Pointers();
	SetupD2Funcs();

	//BEFORE START...
#define CALL 0xE8
#define JUMP 0xE9
#define NOP 0x90
#define RET 0xC3
#define XOR 0x33
#define CUSTOM 0

	char filename[MAX_PATH];
	GetModuleFileName(gModule, filename, MAX_PATH);
	D2ExDir.assign(filename, strrchr(filename, '\\') + 1);

// I'd rather to avoid using __asm stubs
Misc::Patch(CALL, GetDllOffset("D2Common.dll", 0x4F330), (DWORD)ExExtendedLevels::GetActByLevel, 22, "Replace inline GetActByLevel"); //  Ordinal11007
Misc::Patch(CALL, GetDllOffset("D2Common.dll", 0x4F3C7), (DWORD)ExExtendedLevels::GetActByLevel, 26, "Replace inline GetActByLevel"); //  Ordinal11051
Misc::Patch(CALL, GetDllOffset("D2Common.dll", 0x4F160), (DWORD)ExExtendedLevels::GetActByRoom2, 22, "Replace inline GetActByLevel"); //  Ordinal10301

Misc::Patch(CALL, GetDllOffset("D2Common.dll", 0x2AD76), (DWORD)ExExtendedLevels::GetActByLevelNo_STUB1, 20, "Replace inline GetActByLevel"); //  sub_6FD7AD60
Misc::Patch(CALL, GetDllOffset("D2Common.dll", 0x56F40), (DWORD)ExExtendedLevels::GetActByLevelNo_STUB1, 20, "Replace inline GetActByLevel"); //  sub_6FDA6EA0
Misc::Patch(CALL, GetDllOffset("D2Common.dll", 0x510A0), (DWORD)ExExtendedLevels::GetActByLevelNo_STUB2, 20, "Replace inline GetActByLevel"); //  sub_6FDA1070

Misc::Patch(JUMP, GetDllOffset("D2Common.dll", -10864), (DWORD)ExExtendedLevels::GetActByLevelNo, 5, "Replace original GetActByLevelNo");

// The original value is 400
Misc::Patch(CUSTOM, GetDllOffset("D2Client.dll", 0x6FFFB + 1), 4096, 4, "Automap patch I");
Misc::Patch(CUSTOM, GetDllOffset("D2Client.dll", 0x7100B + 1), 4096, 4, "Automap patch I");
Misc::Patch(CUSTOM, GetDllOffset("D2Client.dll", 0x71044 + 1), 4096, 4, "Automap patch I");
Misc::Patch(CUSTOM, GetDllOffset("D2Client.dll", 0x710D9 + 1), 4096, 4, "Automap patch I");
Misc::Patch(CUSTOM, GetDllOffset("D2Client.dll", 0x728EA + 1), 4096, 4, "Automap patch I");

Misc::Patch(CUSTOM, GetDllOffset("D2Client.dll", 0x70FD6 + 2), 4256, 4, "Automap patch II - stack fix"); // The original value is 416
Misc::Patch(CUSTOM, GetDllOffset("D2Client.dll", 0x728A6 + 2), 4172, 4, "Automap patch II - stack fix"); // The original value is 472

// The original value is 99
Misc::Patch(CUSTOM, GetDllOffset("D2Client.dll", 0x70FF6 + 1), 399, 4, "Automap patch III");
Misc::Patch(CUSTOM, GetDllOffset("D2Client.dll", 0x728D9 + 1), 399, 4, "Automap patch III");

// The original value is 400
Misc::Patch(CUSTOM, GetDllOffset("D2Client.dll", 0x7101B + 4), 4096, 4, "Automap patch IV");
Misc::Patch(CUSTOM, GetDllOffset("D2Client.dll", 0x728FE + 4), 4096, 4, "Automap patch IV");

	ExMpq::LoadMPQ();

	return D2Funcs.FOG_isDirect();
}

DWORD WINAPI DllMain(HMODULE hModule, int dwReason, void* lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
#ifdef D2EX_WIN_ERROR_LEVEL_2
			Misc::WinSetErrorLevel(2);
#endif
			SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
			gModule = hModule;

#define CALL 0xE8
#ifdef VER_113D
			Misc::Patch(CALL, GetDllOffset("D2Win.dll", 0xD32E), (DWORD)D2Ex::Init, 5, "Init hook for D2Ex");
#elif VER_111B
			Misc::Patch(CALL, GetDllOffset("D2Win.dll", 0xC86E), (DWORD)D2Ex::Init, 5, "Init hook for D2Ex");
#endif
#undef CALL
		}
		break;
		case DLL_PROCESS_DETACH:
		{
		}
		break;
	}
	return TRUE;
}