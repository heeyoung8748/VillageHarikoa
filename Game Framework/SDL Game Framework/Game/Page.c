#include "stdafx.h"
#include "Page.h"

void Page_Init(Page* page)
{
	wchar_t str[8] = L"";
	wsprintf(str, L"%d", page->ID);
	Text_CreateText(&page->TextID, DEFAULT_FONT, DEFAULT_FONT_SIZE, str, wcslen(str));

	for (int32 i = 0; i < 2; ++i)
	{
		Option_Init(&page->Options[i], PAGE_OPTION_POS_X + i * PAGE_OPTION_WIDTH, PAGE_OPTION_POS_Y);
	}

	page->CurrentOption = 0;

	//Audio_Play(&page->Bgm, INFINITY_LOOP);
	Image_SetAlphaValue(&page->Background, 255 * 0.6);
}

void Page_Update(Page* page)
{
	
		
	if (Input_GetKeyDown(VK_LEFT))
	{
		page->CurrentOption = 0;
	}

	if (Input_GetKeyDown(VK_RIGHT))
	{
		page->CurrentOption = 1;
	}
	
	for (int32 i = 0; i < 2; ++i)
	{
		Option_Update(&page->Options[i]);
	}

	const static SDL_Color SELECTED_COLOR_RED = { .r = 255, .a = 255 };
	const static SDL_Color NON_SELECTED_COLOR_BLACK = { .a = 255 };
	for (int32 i = 0; i < 2; ++i)
	{
		page->Options[i].Color = NON_SELECTED_COLOR_BLACK;
	}
	page->Options[page->CurrentOption].Color = SELECTED_COLOR_RED;
}

void Page_Render(Page* page, bool selectActive)
{
	
	
	Renderer_DrawImage(&page->Background, 0, 0);
	Renderer_DrawImage(&page->Character, 0, 0);

	SDL_Color red = { .r = 255, .a = 255 };
	Renderer_DrawTextBlended(&page->TextID, PAGE_INDEX_POS_X, PAGE_INDEX_POS_Y, red);
	
	
	for (int32 i = 0; i < 2; ++i)
	{
		Option_Render(&page->Options[i], selectActive);
	}
	
	
}

void Page_Release(Page* page)
{
	Text_FreeText(&page->TextID);
	Image_FreeImage(&page->Background);
	Audio_FreeMusic(&page->Bgm);
	for (int32 i = 0; i < 2; ++i)
	{
		Option_Release(&page->Options[i]);
	}
}

void Page_SetOption(Page* page, int32 optionIndex, const CsvItem* csvRow, int32 startColumn)
{

	const wchar_t* text = ParseToUnicode(csvRow[startColumn]);
	int32 len = wcslen(text);
	int32 nextPageIndex = ParseToInt(csvRow[7]);
	// const char* font = ParseToAscii(csvRow[startColumn + 2]);
	int32 nextPageIndex2 = ParseToInt(csvRow[9]);

	Text_CreateText(&page->Options[optionIndex].Text, DEFAULT_FONT, DEFAULT_FONT_SIZE, text, len);
	page->Options->NextPage = nextPageIndex;
	page->Options->NextPage2 = nextPageIndex2;

	 SafeFree(text);
	// SafeFree(font);
}

//void Page_Audio(Page* page,)