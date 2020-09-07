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
#include <stdio.h>
#include <stdarg.h>

#include "text.h"

#define TEXT_BUFFER_LEN 256

typedef struct tagTEXT
{
	TLN_Tilemap tilemap;
} TEXT;

static TEXT* memoryText = 0;
static U32 memoryTextCount = 0U;
static wchar_t* memoryTextBuffer = 0;


#ifdef DEBUG
static void Text_AssertIfNotValidId(void)
{
	ASSERT_DBG(memoryText != 0);
	ASSERT_DBG(memoryTextCount > 0);
}

#else
static void Text_AssertIfNotValidId(void)
{
}
#endif

void Text_Create(U32 nTexts)
{
	ASSERT_DBG(nTexts > 0);
	ASSERT_DBG(memoryText == 0);

	memoryText = (TEXT*) Mem_Calloc(nTexts, sizeof(struct tagTEXT));
	memoryTextBuffer = (wchar_t*) Mem_Calloc(TEXT_BUFFER_LEN, sizeof(wchar_t));
	memoryTextCount = nTexts;
}


void Text_Destroy(void)
{
	ASSERT_DBG(memoryText != 0);

	for (U32 i = 0U; i < memoryTextCount; ++i)
	{
		TLN_DeleteTilemap(memoryText[i].tilemap);
	}

	Mem_Free((void**)&memoryTextBuffer);
	ASSERT_DBG(memoryTextBuffer == 0);

	Mem_Free((void**)&memoryText);
	ASSERT_DBG(memoryText == 0);

	memoryTextCount = 0U;
}


static void Text_CreateTilemap(U32 const id, U32 const row, U32 const column, TLN_Tileset const tileset)
{
	ASSERT_DBG(row > 0U);
	ASSERT_DBG(column > 0U);
	ASSERT_DBG(tileset != 0);

	memoryText[id].tilemap = TLN_CreateTilemap(row, column, 0, 0, tileset);
	ASSERT_DBG(memoryText[id].tilemap != 0);
	TLN_SetLayerTilemap(id, memoryText[id].tilemap);
}


void Text_SetTilesetFile(U32 const id, U32 const row, U32 const column, char const* const tilesetFile)
{
	Text_AssertIfNotValidId();
	TLN_Tileset tileset = TLN_LoadTileset(tilesetFile);
	ASSERT_DBG(tileset != 0);
	Text_CreateTilemap(id, row, column, tileset);
}


void Text_SetTileset(U32 const id, U32 const row, U32 const column, TLN_Tileset const tileset)
{
	Text_AssertIfNotValidId();
	Text_CreateTilemap(id, row, column, tileset);
}


TLN_Tilemap Text_GetTilemap(U32 const id)
{
	Text_AssertIfNotValidId();
	return memoryText[id].tilemap;
}


TLN_Tileset Text_GetTileset(U32 const id)
{
	Text_AssertIfNotValidId();
	return TLN_GetTilemapTileset(memoryText[id].tilemap);
}


static void Text_DrawText(U32 const id, U32 const row,  U32 column, wchar_t const* str)
{
	ASSERT_DBG(str);

	TLN_Tilemap const tilemap = memoryText[id].tilemap;
	ASSERT_DBG(tilemap);

	Tile tile = (Tile){0}; /* valgrind indica un comportamiento
							  posiblemente no definido en Tilengine::Draw.c
							  si no se inicializa a 0.
						   */

	do
	{
		tile.index = *str + 1;
		TLN_SetTilemapTile(tilemap, row, column, &tile);
		column++;
	} while (*str++);
}


void Text_Draw(U32 const id, U32 const row, U32 const column, wchar_t const* str)
{
	Text_AssertIfNotValidId();
	ASSERT_DBG(str != 0);
	Text_DrawText(id, row, column, str);
}


void Text_DrawFormat(U32 const id, U32 const row, U32 const column, wchar_t const* const format, ...)
{
	Text_AssertIfNotValidId();
	ASSERT_DBG(format != 0);

	wchar_t* textBufferPtr = memoryTextBuffer;

	va_list vl;
	va_start(vl, format);
	vswprintf(textBufferPtr, TEXT_BUFFER_LEN, format, vl);
	va_end(vl);

	Text_Draw(id, row, column, textBufferPtr);
}


void Text_Hide(U32 const id)
{
	Text_AssertIfNotValidId();
	TLN_DisableLayer(id);
}


void Text_Show(U32 const id)
{
	Text_AssertIfNotValidId();
	TLN_SetLayer(id, 0, Text_GetTilemap(id));
}
