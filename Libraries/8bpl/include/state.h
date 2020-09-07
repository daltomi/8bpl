/*
    8bpl - Copyright © daltomi <daltomi@disroot.org>
    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from
    the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not claim
      that you wrote the original software. If you use this software in a product,
      an acknowledgment in the product documentation would be appreciated but is
      not required.

    2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original software.

    3. This notice may not be removed or altered from any source distribution.
*/
#ifndef LIB_8BPL_STATE_H_INCLUDED
#define LIB_8BPL_STATE_H_INCLUDED

#include "8bpl.h"


typedef struct tagSTATE STATE;

typedef void (State_EnterCallback)(__attribute__((unused)) void* data);
typedef void (State_RunCallback)  (__attribute__((unused)) void* data);
typedef void (State_ExitCallback) (__attribute__((unused)) void* data);

void State_Create(U32 const nStates);

void State_Destroy(void);

void State_SetCallback(U32 const id, State_EnterCallback* enter, State_RunCallback* run, State_ExitCallback* exit, void* data);

void State_Allocate(U32 const id);

void State_Deallocate(U32 const id);

void State_SetCurrent(U32 const id);

void State_Update(void);

#endif
