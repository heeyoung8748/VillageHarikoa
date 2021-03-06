#pragma once

#include "Framework.h"
#include "PageIndex.h"

typedef struct Option
{
	int32		PosX;
	int32		PosY;
	Text		Text;
	EPageIndex	NextPage;
	EPageIndex	NextPage2;
	SDL_Color	Color;
} Option;

void Option_Init(Option* option, int32 posX, int32 posY);
void Option_Update(Option* option);
void Option_Render(Option* option, bool selectActive);
void Option_Release(Option * option);
