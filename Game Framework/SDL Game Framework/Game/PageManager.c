#include "stdafx.h"
#include "PageManager.h"
#include "PageIndex.h"

void PageManager_Init(PageManager* pageManager)
{
	CsvFile csvFile = { 0 };
	CreateCsvFile(&csvFile, "db.csv");

	for (int32 page = 1; page < csvFile.RowCount; ++page)
	{
		pageManager->Pages[page].ID = ParseToInt(csvFile.Items[page][COL_PAGE_INDEX]);

		for (int32 i = 0; i < 5; ++i)
		{
			Text_CreateText(&pageManager->Pages[page].TextID, DEFAULT_FONT, DEFAULT_FONT_SIZE, csvFile.Items[page], COL_PAGE_INDEX + i);
		}
		for (int32 i = 0; i < 5; i++)
		{
			Text_CreateText(&pageManager->Pages[page].Script[i], DEFAULT_FONT, DEFAULT_FONT_SIZE, csvFile.Items[page + 1], 128);
		}
		const char* backgroundImageFileName = ParseToAscii(csvFile.Items[page][COL_BACKGROUND_IMAGE]);
		Image_LoadImage(&pageManager->Pages[page].Background, backgroundImageFileName);
		const char* characterImageFileName = ParseToAscii(csvFile.Items[page][COL_CHARACTER_IMAGE]);
		Image_LoadImage(&pageManager->Pages[page].Character, characterImageFileName);

		const char* backgroundMusicFileName = ParseToAscii(csvFile.Items[page][COL_BACKGROUND_MUSIC]);
		Audio_LoadMusic(&pageManager->Pages[page].Bgm, backgroundMusicFileName);
		const char* effectMusicFileName = ParseToAscii(csvFile.Items[page][COL_EFFECT_MUSIC]);
		Audio_LoadMusic(&pageManager->Pages[page].Effect, effectMusicFileName);

		int32 diff = COL_OPTION2 - COL_OPTION1;
		for (int32 i = 0; i < 2; ++i)
		{
			Page_SetOption(&pageManager->Pages[page], i, csvFile.Items[page], COL_OPTION1 + i * diff);
		}

		// pageManager->Pages[page].ID = ParseToInt(csvFile.Items[page][COL_PAGE_INDEX]);

		SafeFree(backgroundImageFileName);
		SafeFree(characterImageFileName);
		SafeFree(backgroundMusicFileName);
		SafeFree(effectMusicFileName);

		Page_Init(&pageManager->Pages[page]);
	}

	FreeCsvFile(&csvFile);

	pageManager->CurrentPage = &pageManager->Pages[PAGE_1];
	pageManager->NextPage = NULL;
	
}

void PageManager_Update(PageManager* pageManager)
{
	if (pageManager->NextPage != NULL)
	{
		pageManager->CurrentPage = pageManager->NextPage;
		pageManager->NextPage = NULL;
	}

	Page_Update(pageManager->CurrentPage);
	
	if (Input_GetKeyDown(VK_SPACE))
	{ 
		
		int32 nextPageIndex = pageManager->CurrentPage->Options->NextPage;
		pageManager->NextPage = &pageManager->Pages[nextPageIndex];
			
	}
}

void PageManager_Render(PageManager* pageManager)
{
	Page_Render(pageManager->CurrentPage);
}

void PageManager_Release(PageManager* pageManager)
{
	for (int32 i = 0; i < MAX_PAGE_COUNT; ++i)
	{
		Page_Release(&pageManager->Pages[i]);
	}
}
