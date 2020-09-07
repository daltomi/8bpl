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


#include "memory.h"


struct tagMEMPOOL
{
	MEMPOOLID id;
	U64 nBlocks;
	U64 nFreeBlocks;
	U64 nSizeOfEachBlock;
	U64 nInitialized;
	U8* memStart;
	U8* memNext;
};



//~ #define MEM_ALIGNED

#ifdef MEM_ALIGNED

#include <stdlib.h>  // posix_memalign
#include <malloc.h>  // memalign
#include <unistd.h>  // sysconf

static void* MemAllocAligned(USIZE const size)
{
	USIZE const align = sysconf(_SC_PAGESIZE);

	MESSAGE_DBG("mem page size %zu\n", align);

#if _POSIX_C_SOURCE >= 200112L

	int ret;
	void* mem = 0;

	ret = posix_memalign(&mem, align, size);

	ASSERT(ret == 0);

	return mem;

#elif defined(_ISOC11_SOURCE)

	return aligned_alloc(align, size);

#else

	return memalign(align, size);
#endif
}
#endif

void* Mem_Alloc(USIZE const size)
{
	void* memory = 0;

#ifdef MEM_ALIGNED
	memory = MemAllocAligned(size);
#else
	memory = malloc(size);
	ASSERT(memory != 0);
#endif

	return memory;
}

void* Mem_Calloc(USIZE const n, USIZE const size)
{
	ASSERT_DBG(n > 0);
	ASSERT_DBG(size > 0);

	void* memory = 0;

	memory = calloc(n, size);

	ASSERT_DBG(memory != 0);

	return memory;
}

void Mem_Free(void** memory)
{
	free(*memory);
	*memory = 0;
}

U64 MemoryPool_GetUsedBlocks(MEMPOOL const* const memory)
{
	ASSERT_DBG(memory != 0);
	return memory->nBlocks - memory->nFreeBlocks;
}

U64 MemPool_IndexFromAddress(MEMPOOL const *const memory, U8 const* const address)
{
	ASSERT_DBG(memory != 0);
	return (((U64)(address - memory->memStart)) / memory->nSizeOfEachBlock);
}


U8* MemPool_AddressFromIndex(MEMPOOL const* const memory, U64 const index)
{
	ASSERT_DBG(memory != 0);
	return memory->memStart + (index * memory->nSizeOfEachBlock);
}


static void MemPool_InitDefault(MEMPOOL* memory)
{
	ASSERT_DBG(memory != 0);

	memory->id[0] = '\0';
	memory->nBlocks = 0U;
	memory->nFreeBlocks = 0U;
	memory->nSizeOfEachBlock = 0U;
	memory->nInitialized = 0U;
	memory->memStart = 0;
	memory->memNext = 0;
}


MEMPOOL* MemPool_Create(USIZE const nSizeOfEachBlock, U64 const  nBlocks,  MEMPOOLID const id)
{
	ASSERT_DBG(nSizeOfEachBlock > sizeof(U64));
	ASSERT_DBG(nBlocks > 0U);

	MEMPOOL* newMemory = Mem_Alloc(sizeof(MEMPOOL));

	MemPool_InitDefault(newMemory);

	newMemory->nSizeOfEachBlock = nSizeOfEachBlock;
	newMemory->nBlocks = nBlocks;

	newMemory->memStart = Mem_Alloc(nSizeOfEachBlock * nBlocks);
	newMemory->memNext  = newMemory->memStart;

	newMemory->nFreeBlocks = nBlocks;

	strncpy(newMemory->id, id, MEMPOOLID_LEN - 1);
	newMemory->id[MEMPOOLID_LEN - 1] = '\0';

	MESSAGE_DBG("MemPool_Create.\nID:%5s", newMemory->id);
	return newMemory;
}


void MemPool_Destroy(MEMPOOL** memory)
{
	MESSAGE_DBG("MemPool_Destroy.\nID:%5s", (*memory)->id);
	ASSERT_DBG((memory != 0) && (*memory != 0));

	U8 *memStart = (*memory)->memStart;
	ASSERT_DBG(memStart != 0);

	Mem_Free((void **)&memStart);
	Mem_Free((void **)memory);
}


void* MemPool_Allocate(MEMPOOL* const memory)
{
	MESSAGE_DBG("MemPool_Allocate.\nID:%5s", memory->id);
	ASSERT_DBG(memory != 0);

	if (memory->nInitialized < memory->nBlocks)
	{
		U64 *address = 0;
		address = (U64 *)MemPool_AddressFromIndex(memory, memory->nInitialized);
		*address = memory->nInitialized + 1;
		memory->nInitialized++;
	}

	void* address = 0;

	if (memory->nFreeBlocks > 0U)
	{
		address = (void*)memory->memNext;
		memory->nFreeBlocks--;

		if (memory->nFreeBlocks != 0U)
		{
			memory->memNext = MemPool_AddressFromIndex(memory,
					  *((U64 *)memory->memNext));
		}
		else
		{
			memory->memNext = 0;
		}
	}

	if (address == 0)
	{
		STOP("MemPool_Allocate returns 0. Do you try to allocate more than expected?");
	}

	MemPool_Info(memory);

	return address;
}


void MemPool_Deallocate(MEMPOOL* memory, void* address)
{
	MESSAGE_DBG("MemPool_Deallocate.\nID:%5s", memory->id);
	ASSERT_DBG(memory != 0);

	if (memory->memNext != 0)
	{
		(*(U64*)address) = MemPool_IndexFromAddress(memory, memory->memNext);
		memory->memNext = (U8 *)address;
	}
	else
	{
		(*(U64*)address) = memory->nBlocks;
		memory->memNext = (U8 *)address;
	}

	memory->nFreeBlocks++;
	MemPool_Info(memory);
}

#ifdef DEBUG
void MemPool_Info(MEMPOOL const *const memory)
{
	U64 const nBlocks = memory->nBlocks ;
	U64 const nFreeBlocks = memory->nFreeBlocks;
	U64 const nSizeOfEachBlock	= memory->nSizeOfEachBlock;
	U64 const nInitialized = memory->nInitialized;
	U8 const* const memStart = memory->memStart;
	U8 const* const memNext = memory->memNext;

#ifdef __i386__
	MESSAGE_DBG("Memory info\n"
		/*A*/     "%-20s:%s\n%-20s:%lld\n%-20s:%lld\n%-20s:%lld\n%-20s:%lld\n%-20s:%p\n%-20s:%p\n"
		/*B*/     "Memory %llu byte x %lld blocks - Total: %lld bytes\n",
		/*A*/     "ID", memory->id, "blocks", nBlocks, "free blocks", nFreeBlocks, "size blocks", nSizeOfEachBlock,
		"initilized", nInitialized,
		"start", memStart,
		"next", memNext,
		/*B*/ nSizeOfEachBlock, nBlocks, nSizeOfEachBlock * nBlocks);
#else
	MESSAGE_DBG("Memory info\n"
		/*A*/     "%-20s:%s\n%-20s:%ld\n%-20s:%ld\n%-20s:%ld\n%-20s:%ld\n%-20s:%p\n%-20s:%p\n"
		/*B*/     "Memory %zu byte x %ld blocks - Total: %ld bytes\n",
		/*A*/     "ID", memory->id, "blocks", nBlocks, "free blocks", nFreeBlocks, "size blocks", nSizeOfEachBlock,
		"initilized", nInitialized,
		"start", memStart,
		"next", memNext,
		/*B*/ nSizeOfEachBlock, nBlocks, nSizeOfEachBlock * nBlocks);
#endif
}
#else
void MemPool_Info(MEMPOOL const* const memory)
{ }
#endif
