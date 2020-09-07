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
#ifndef LIB_8BPL_SOUND_H_INCLUDED
#define LIB_8BPL_SOUND_H_INCLUDED

#include "8bpl.h"

typedef struct tagSOUND_MAP
{
	U32 file;
	U32 play;
} SOUND_MAP;


void Sound_Create(U32 const nFilesSounds, U32 const nPlaySounds);

void Sound_Destroy(void);

void Sound_LoadOgg(U32 const idLoad, char const* const fileName);

void Sound_LoadWav(U32 const idLoad, char const* const fileName);

void Sound_SetMap(SOUND_MAP const* const soundMap);

void Sound_Play(U32 const idPlayer);

void Sound_PlayAll(void);

void Sound_Pause(U32 const idPlayer, BOOL const pause);


#endif