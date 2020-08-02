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
#ifndef LIB_8BPL_TEXT_H_INCLUDED
#define LIB_8BPL_TEXT_H_INCLUDED

#include "8bpl.h"


void Text_Create(U32 nTexts);

void Text_Destroy(void);

void Text_SetTilesetFile(U32 const id, U32 const row, U32 const column, char const* const tilesetFile);

void Text_SetTileset(U32 const id, U32 const row, U32 const column, TLN_Tileset const tileset);

TLN_Tileset Text_GetTileset(U32 const id);

TLN_Tilemap Text_GetTilemap(U32 const id);

void Text_Hide(U32 const id);

void Text_Show(U32 const id);

void Text_Draw(U32 const id, U32 const row, U32 const column, wchar_t const* str);

void Text_DrawFormat(U32 const id, U32 const row, U32 const column, wchar_t const* const format, ...);

#endif
