/*
    8bpl - Copyright (c) daltomi <daltomi@disroot.org>
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

#include "stb_vorbis.h"

#define CUTE_SOUND_IMPLEMENTATION
#define CUTE_SOUND_FORCE_SDL

#include "cute_sound.h"

#include "sound.h"

typedef struct tagSOUND_FILE
{
	U32 size;
	cs_loaded_sound_t* sound;
} SOUND_FILE;


typedef struct tagSOUND_PLAY
{
	U32 size;
	cs_playing_sound_t* sound;
} SOUND_PLAYER;


static SOUND_PLAYER* memorySoundPlay;
static SOUND_FILE* memorySoundFile;
static cs_context_t* soundContext = 0;

void Sound_Create(U32 const nFilesSounds, U32 const nPlaySounds)
{
	ASSERT_DBG(soundContext == 0);
	ASSERT_DBG(nFilesSounds > 0);
	ASSERT_DBG(nPlaySounds > 0);

	#define FREQ 44100

	#define BUFLEN (4096 * 2)

	soundContext = cs_make_context(0, FREQ, BUFLEN, 0, 0);

	ASSERT_DBG(soundContext);

	memorySoundPlay = Mem_Alloc(sizeof(struct tagSOUND_PLAY));
	memorySoundPlay->sound = Mem_Calloc(nPlaySounds, sizeof(struct cs_playing_sound_t));
	memorySoundPlay->size = nPlaySounds;

	memorySoundFile = Mem_Alloc(sizeof(struct tagSOUND_FILE));
	memorySoundFile->sound = Mem_Calloc(nFilesSounds, sizeof(struct cs_loaded_sound_t));
	memorySoundFile->size = nFilesSounds;

	cs_spawn_mix_thread(soundContext);
}


void Sound_SetMap(SOUND_MAP const* const soundMap)
{
	ASSERT_DBG(soundContext);
	ASSERT_DBG(soundMap);

	cs_loaded_sound_t *const file = memorySoundFile->sound;
	ASSERT_DBG(file);

	cs_playing_sound_t *const play = memorySoundPlay->sound;
	ASSERT_DBG(play);

	U32 const playIds = memorySoundPlay->size;

	for (U32 id = 0; id < playIds; ++id)
	{
		SOUND_MAP const* const sndId = soundMap + id;
		ASSERT_DBG(sndId);

		play[sndId->play] = cs_make_playing_sound(&file[sndId->file]);
	}
}


void Sound_Destroy(void)
{
	ASSERT_DBG(soundContext);

	for (U32 i = 0; i < memorySoundFile->size; ++i)
	{
		cs_free_sound(&memorySoundFile->sound[i]);
	}

	Mem_Free((void**)&memorySoundFile->sound);
	Mem_Free((void**)&memorySoundPlay->sound);

	Mem_Free((void**)&memorySoundFile);
	Mem_Free((void**)&memorySoundPlay);

	cs_shutdown_context(soundContext);
}



#ifdef DEBUG
static void Sound_Load_AssertIfNotValid(U32 const id)
{
	ASSERT_DBG(soundContext);
	ASSERT_DBG(memorySoundFile);
	ASSERT_DBG(memorySoundFile->size > 0);
	ASSERT_DBG(id < memorySoundFile->size);
}
#else
static void Sound_Load_AssertIfNotValid(__attribute__((unused)) U32 const id)
{
}
#endif


#ifdef DEBUG
static void Sound_Play_AssertIfNotValid(U32 const id)
{
	ASSERT_DBG(soundContext);
	ASSERT_DBG(memorySoundPlay);
	ASSERT_DBG(memorySoundPlay->size > 0);
	ASSERT_DBG(id < memorySoundPlay->size);
}
#else
static void Sound_Play_AssertIfNotValid(__attribute__((unused)) U32 const id)
{
}
#endif



void Sound_LoadOgg(U32 const idLoad, char const* const fileName)
{
	ASSERT_DBG(fileName);
	ASSERT_DBG(strlen(fileName));
	Sound_Load_AssertIfNotValid(idLoad);

	memorySoundFile->sound[idLoad] = cs_load_ogg(fileName);

	if (cs_error_reason)
	{
		STOP("%s\n", cs_error_reason);
	}
}


void Sound_LoadWav(U32 const idLoad, char const* const fileName)
{
	ASSERT_DBG(fileName);
	ASSERT_DBG(strlen(fileName));
	Sound_Load_AssertIfNotValid(idLoad);

	memorySoundFile->sound[idLoad] = cs_load_ogg(fileName);

	if (cs_error_reason)
	{
		STOP("%s\n", cs_error_reason);
	}
}


void Sound_Play(U32 const idPlay)
{
	Sound_Play_AssertIfNotValid(idPlay);
	cs_insert_sound(soundContext, &memorySoundPlay->sound[idPlay]);
}


void Sound_PlayAll(void)
{
	for (U32 i = 0; i < memorySoundPlay->size; ++i)
	{
		Sound_Play(i);
	}
}


void Sound_Pause(U32 const idPlay, BOOL const pause)
{
	Sound_Play_AssertIfNotValid(idPlay);
	cs_pause_sound(&memorySoundPlay->sound[idPlay], (int)pause);
}
