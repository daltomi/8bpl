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

/*
	Ref.: http://www.thinkmind.org/download.php?articleid=computation_tools_2012_1_10_80006
*/


#ifndef LIB_8BPL_MEMORY_H_INCLUDED
#define LIB_8BPL_MEMORY_H_INCLUDED

#include "8bpl.h"

#define MEMPOOLID_LEN 10

typedef char MEMPOOLID[MEMPOOLID_LEN];

typedef struct tagMEMPOOL MEMPOOL;

U64 MemoryPool_GetUsedBlocks(MEMPOOL const* const memory);

MEMPOOL* MemPool_Create(USIZE const nSizeOfEachBlock, U64 const nBlocks, MEMPOOLID const id);

void MemPool_Destroy(MEMPOOL** memory);

void* MemPool_Allocate(MEMPOOL* const memory);

void MemPool_Deallocate(MEMPOOL* memory, void* address);

U64 MemPool_IndexFromAddress(MEMPOOL const* const memory, U8 const* address);

U8* MemPool_AddressFromIndex(MEMPOOL const* const memory, U64 const index);

void MemPool_Info(MEMPOOL const* const memory);

void* Mem_Alloc(USIZE const size);

void* Mem_Calloc(USIZE const n, USIZE const size);

void Mem_Free(void** memory);
#endif
