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

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_DEPRECATE
//#define _WIN32_WINNT 0x600

#define PI 3.1415926535
#define NULL_ENTRY	222

using namespace std;

#pragma once

#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "shlwapi.lib")

#define EXPORT __declspec(dllexport)
#define FASTCALL __fastcall
#define FUNCCALL __cdecl
#define IMPORT __declspec(dllimport)
#define NAKED __declspec(naked)
#define STDCALL __stdcall

#pragma warning(disable : 4311)
#pragma warning(disable : 4312)

#include <Windows.h>
#include <string>
#include "Constants.h"
#include "CommonStructs.h"
#include <glide.h>

#include <ctime>
#include <iosfwd>
#include <list>
#include <math.h>
#include <process.h>
#include <psapi.h>
#include <shlwapi.h>
#include <sstream>
#include <stdio.h>
#include <time.h>
#include <tlhelp32.h>
#include <valarray>
#include <vector>
#include <winbase.h>
#include <windef.h>
#include <winnt.h>
#include <winuser.h>

#ifdef VER_113D
#include "D2Structs_113D.h"
#include "D2ExPointers_113D.h"
#elif defined VER_111B
#include "D2Structs_111B.h"
//#include "D2ExPointers_111B.h"
#endif

#include "BlizzardSmartPointer.h"

#include "D2Stubs.h"

#include "Misc.h"
#include "Vars.h"
#include "D2Strings.h"

#ifdef _DEBUG
#define DEBUGMSG(format,...) Misc::Debug(__FUNCTION__, format, ##__VA_ARGS__);
#else
#define DEBUGMSG(format,...) {}
#endif

//ASSERT macro is deprecated, use D2EXASSERT
#define ASSERTD(e) if (e == 0) { ShowWindow(D2Funcs.D2GFX_GetHwnd(),SW_HIDE);Misc::Log("Error at line %d in file '%s' , function: '%s'",__LINE__,__FILE__,__FUNCTION__); MessageBoxA(0,"An error occured. Check D2Ex.log, and send error\ncode to *LOLET!","D2Ex",0); exit(-1); }

#define D2EXASSERT(e, format, ...) if(!e) { ShowWindow(D2Funcs.D2GFX_GetHwnd(),SW_HIDE);   Misc::ShowMsgBox(format, ##__VA_ARGS__); exit(-1); }
#define D2EXERROR(format, ...) { ShowWindow(D2Funcs.D2GFX_GetHwnd(),SW_HIDE);   Misc::ShowMsgBox(format, ##__VA_ARGS__); exit(-1); }
#define D2EXINFO(format, ...) ExScreen::PrintTextEx(COL_ORANGE, format, ##__VA_ARGS__);

