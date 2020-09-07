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
#include "state.h"

#define STATE_FLAG_DELETE	BIT(0)

struct tagSTATE {
	U64 reserved;
	U32 id;
	U8 flags;
	State_EnterCallback* enter;
	State_RunCallback* run;
	State_ExitCallback* exit;
	void* data;
};


static MEMPOOL* memoryState = 0;

static STATE* previousState = 0;
static STATE* currentState = 0;

static MEMPOOLID const memoryStateId = "STATE";

#ifdef DEBUG
static void State_AssertIfNotValidId(U32 const id)
{
	ASSERT_DBG(memoryState != 0);

	void* address = MemPool_AddressFromIndex(memoryState, id);
	STATE* state = (STATE*)address;
	if (CHK_BIT(state->flags, STATE_FLAG_DELETE)) {
		STOP_DBG("It is attempting to use a deleted object.");
	}
}

#else
static void State_AssertIfNotValidId(U32 const id)
{
	(void)id;
}
#endif


static void State_Init(STATE* const state, U32 const id)
{
	ASSERT_DBG(state != 0);

	state->enter = 0;
	state->run = 0;
	state->exit = 0;
	state->id = id;
	state->flags = (U8)0;
	state->data = 0;
}


static void* State_GetMemoryAddress(U32 const id)
{
	State_AssertIfNotValidId(id);
	return MemPool_AddressFromIndex(memoryState, id);
}


void State_Create(U32 const nStates)
{
	ASSERT_DBG(memoryState == 0);

	memoryState = MemPool_Create(sizeof(struct tagSTATE), nStates, memoryStateId);

	for (U64 i = 0U; i < nStates; ++i) {
		State_Allocate(i);
	}
}


void State_Destroy(void)
{
	U64 const nBlocks = MemoryPool_GetUsedBlocks(memoryState);

	for (U64 i = 0U; i < nBlocks; ++i) {
		State_Deallocate(i);
	}

	currentState = 0;
	previousState = 0;

	MemPool_Destroy(&memoryState);
}


void State_Allocate(U32 const id)
{
	void* address = MemPool_Allocate(memoryState);

	STATE* newState = (STATE*)address;

	State_Init(newState, id);
}


void State_Deallocate(U32 const id)
{
	void* address = State_GetMemoryAddress(id);

	STATE* state = (STATE*)address;

	if (NOT_BIT(state->flags, STATE_FLAG_DELETE)) {
		SET_BIT(state->flags, STATE_FLAG_DELETE);
		MemPool_Deallocate(memoryState, address);
	}
}


void State_SetCallback(	U32 const id,
						State_EnterCallback* enter,
						State_RunCallback* run,
						State_ExitCallback* exit,
						void* data)
{
	ASSERT_DBG(enter != 0);
	ASSERT_DBG(run != 0);
	ASSERT_DBG(exit != 0);

	void* address = State_GetMemoryAddress(id);

	STATE* state = (STATE*)address;

	state->enter = enter;
	state->run = run;
	state->exit = exit;
	state->data = data;
}


void State_SetCurrent(U32 const id)
{
	void* address = State_GetMemoryAddress(id);

	previousState = currentState;

	currentState = (STATE*)address;

	if (previousState != 0) {
		previousState->exit(previousState->data);
	}

	currentState->enter(currentState->data);
}


void State_Update(void)
{
	ASSERT_DBG(currentState != 0);

	if (NOT_BIT(currentState->flags, STATE_FLAG_DELETE)) {
		currentState->run(currentState->data);
	}
}

