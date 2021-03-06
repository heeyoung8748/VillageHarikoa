#include "stdafx.h"
#include "PageManager.h"
#include "PageIndex.h"


int32 lineSave[500];
int32 lineSaveCount = 0;
void PageManager_Init(PageManager* pageManager)
{
	
	CsvFile csvFile = {0};
	CreateCsvFile(&csvFile, "dbfinal2.csv");
	for (int32 page = 1; page < 479; ++page)
	{

		pageManager->Pages[page].ID = ParseToInt(csvFile.Items[page][COL_PAGE_INDEX]);
		pageManager->saveScript = ParseToUnicode(csvFile.Items[page][COL_TEXT]); // saveScript = ´ë»ç ¿£ÅÍÆ÷ÇÔ
		const wchar_t* lineStart = pageManager->saveScript;
		
		for  (int32 line = 0; line < TEXT_MAX_LINE; line++) // 
		{
			
			const wchar_t* lineEnd = lineStart;
			while (true)
			{
				if (L'\n' == *lineEnd || L'\0' == *lineEnd)
				{
					break;
				}
				++lineEnd;
			}
			int32 lineLength = lineEnd - lineStart;
		
			Text_CreateText(&pageManager->Pages[page].Script[line], DEFAULT_FONT, DEFAULT_FONT_SIZE, lineStart, lineLength);
			
			if (L'\0' == *lineEnd)
			{
				lineSave[lineSaveCount] = line + 1;
				lineSaveCount++;
				break;
			}
			lineStart = lineEnd + 1;
			  
		}
		
		//Text_CreateText(&pageManager->Pages[page].Script, DEFAULT_FONT, DEFAULT_FONT_SIZE, saveScript, 128);
		/*for (int32 i = 0; i < 5; ++i)
		{
			Text_CreateText(&pageManager->Pages[page].TextID, DEFAULT_FONT, DEFAULT_FONT_SIZE, csvFile.Items[page], COL_PAGE_INDEX + i);
		}*/
		
		const char* backgroundImageFileName = ParseToAscii(csvFile.Items[page][COL_BACKGROUND_IMAGE]);
		Image_LoadImage(&pageManager->Pages[page].Background, backgroundImageFileName);
		const char* characterImageFileName = ParseToAscii(csvFile.Items[page][COL_CHARACTER_IMAGE]);
		Image_LoadImage(&pageManager->Pages[page].Character, characterImageFileName);

		const char* backgroundMusicFileName = ParseToAscii(csvFile.Items[page][COL_BACKGROUND_MUSIC]);
		Audio_LoadMusic(&pageManager->Pages[page].Bgm, backgroundMusicFileName);
		
		const char* effectMusicFileName = ParseToAscii(csvFile.Items[page][COL_EFFECT_MUSIC]);
		if (*effectMusicFileName)
		{
			Audio_LoadSoundEffect(&pageManager->Pages[page].Effect, effectMusicFileName);
		}

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
	SafeFree(pageManager->saveScript);
	
}
bool selected = 0;
int32 nextPage = 1;
int32 count = 0;
int32 ccount = 0;
bool effectPlay = false;
void PageManager_Update(PageManager* pageManager)
{
	if (pageManager->NextPage != NULL)
	{
		pageManager->CurrentPage = pageManager->NextPage;
		pageManager->NextPage = NULL;
	}
	Page_Update(pageManager->CurrentPage);

	if (Input_GetKeyDown(VK_LEFT))
	{
		selected = 0;
	}

	if (Input_GetKeyDown(VK_RIGHT) && pageManager->selectActive == true)
	{
		selected = 1;
	}
	
 	if (Input_GetKeyDown(VK_SPACE))
	{ 
 		effectPlay = true;
		if (effectPlay == true && count == 0)
		{
			Audio_PlaySoundEffect(&pageManager->Pages[nextPage].Effect, 0);
			effectPlay = false;
		}
		if (count == 0)
		{
        jaehyuk_0523_last
		    Audio_Play(&pageManager->Pages[nextPage].Bgm, INFINITY_LOOP);
		}
 		count++;
		pageManager->selectActive = false;
		if (count == lineSave[ccount]-1)
		pageManager->selectActive = true;
			
		if (count == lineSave[ccount])
		{
				int32 nextPageIndex = pageManager->CurrentPage->Options->NextPage;
				nextPage = nextPageIndex;
				ccount = nextPageIndex - 1;
				pageManager->NextPage = &pageManager->Pages[nextPageIndex];

			if (selected == 1)
			{
				int32 nextPageIndex = pageManager->CurrentPage->Options->NextPage2;
				nextPage = nextPageIndex;
				ccount = nextPageIndex - 1;
				pageManager->NextPage = &pageManager->Pages[nextPageIndex];
				selected = 0;
			}
			count = 0;
		}
	
	}
	if (nextPage == 1000)
		Scene_SetNextScene(SCENE_CREDIT);

	
	
	
}

void PageManager_Render(PageManager* pageManager)
{
	Page_Render(pageManager->CurrentPage, pageManager->selectActive);
	SDL_Color white = { .r = 255, .b = 255, .g = 255, .a = 255 };
	
	if (pageManager->Pages[nextPage].Script->Length > 0)
	{
		Renderer_DrawTextBlended(&pageManager->Pages[nextPage].Script[count], 90, 480, white);
	}
	
}

void PageManager_Release(PageManager* pageManager)
{
	for (int32 i = 0; i < MAX_PAGE_COUNT; ++i)
	{
		Page_Release(&pageManager->Pages[i]);
	}
}