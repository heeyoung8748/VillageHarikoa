#pragma once

#include "Framework.h"
#include "PageIndex.h"
#include "Option.h"

typedef struct Page
{
	EPageIndex	ID;
	Text		TextID;
	Text        Script[40];
	Image		Background;
	Image		Character;
	Music		Bgm;
	SoundEffect		Effect;
	Option		Options[2];
	int32		CurrentOption;
} Page;

enum EColumn
{
	COL_PAGE_INDEX,
	COL_TEXT,
	COL_BACKGROUND_IMAGE,
	COL_CHARACTER_IMAGE,
	COL_BACKGROUND_MUSIC,
	COL_EFFECT_MUSIC,
	COL_OPTION1,
	COL_OPTION1_PAGE_INDEX,
	//COL_OPTION1_FONT,
	//COL_OPTION1_FONT_SIZE,
	COL_OPTION2,
	COL_OPTION2_PAGE_INDEX,
	//COL_OPTION2_FONT,
	//COL_OPTION2_FONT_SIZE
	COL_OPTION_SCENE_EFFECT
};

void Page_Init(Page* page);
void Page_Update(Page* page);
void Page_Render(Page* page, bool selectActive);
void Page_Release(Page* page);
void Page_SetOption(Page* page, int32 optionIndex, const CsvItem* csvRow, int32 startColumn);