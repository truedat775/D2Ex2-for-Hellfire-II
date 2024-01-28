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

#ifndef __D2STUBS_H
#define __D2STUBS_H

#pragma once

namespace D2ASMFuncs
{
	void* __stdcall D2WIN_LoadMpq(DWORD OrderFlag, const char* szDllFile, const char* szMpqFile, const char* szName, DWORD _1, BOOL (__stdcall *fnMPQMissing)());
}

#endif