#include "stdafx.h"
#include "Scene.h"
#include <crtdbg.h>
#include "Framework.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

#pragma region TitleScene

#define SOLID 0
#define SHADED 1
#define BLENDED 2

//const wchar_t* str[] = {
//	L"여기는 타이틀씬입니다. 텍스트와 관련된 여러가지를 테스트해봅시다.",
//	L"B키를 누르면 폰트가 굵게 변합니다.",
//	L"I키를 누르면 폰트가 이탤릭체로 변합니다.",
//	L"U키를 누르면 텍스트에 밑줄이 생깁니다.",
//	L"S키를 누르면 텍스트에 취소선이 생깁니다.",
//	L"N키를 누르면 다시 원래대로 돌아옵니다.",
//	L"C키를 누르면 렌더 모드가 바뀝니다. (Solid -> Shaded -> Blended)",
//	L"1키를 누르면 텍스트가 작아집니다.",
//	L"2키를 누르면 텍스트가 커집니다.",
//	L"스페이스 키를 누르면 다음 씬으로 넘어갑니다."
//};

typedef struct TitleSceneData
{
	Text	GuideLine[10];
	Text	TestText;
	int32	FontSize;
	int32	RenderMode;
	//Image	TestImage;
	Image	BackGroundImage;
	Music	BGM;
} TitleSceneData;

void Title_logOnFinished(void)
{
	LogInfo("You can show this log on stopped the music");
}

void Title_log2OnFinished(int32 channel)
{
	LogInfo("You can show this log on stopped the effect");
}

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	Audio_LoadMusic(&data->BGM, "SOUND_PROLOGUE_1.mp3");
	Audio_HookMusicFinished(Title_logOnFinished);
	Audio_PlayFadeIn(&data->BGM, INFINITY_LOOP, 3000);
	/*for (int32 i = 0; i < 10; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "d2coding.ttf", 16, str[i], wcslen(str[i]));
	}*/

	data->FontSize = 24;
	Text_CreateText(&data->TestText, "d2coding.ttf", data->FontSize, L"스페이스 바를 누르면 시작합니다", 18);
	
	data->RenderMode = SOLID;
	Image_LoadImage(&data->BackGroundImage, "BackGround.jpg");
	//Image_LoadImage(&data->TestImage, "SCENE_ROADSIDE_1.jpg");
	
}

void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	

	/*if (Input_GetKey('1'))
	{
		--data->FontSize;
		Text_SetFont(&data->TestText, "d2coding.ttf", data->FontSize);
	}

	if (Input_GetKey('2'))
	{
		++data->FontSize;
		Text_SetFont(&data->TestText, "d2coding.ttf", data->FontSize);
	}*/

	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_EXTRA);
	}

	if (Input_GetKeyDown('1'))
	{
		Scene_SetNextScene(SCENE_MAIN);
	}

}

void render_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	/*for (int32 i = 0; i < 10; ++i)
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawTextSolid(&data->GuideLine[i], 10, 20 * i, color);
	}*/
	data->BackGroundImage.Height = WINDOW_HEIGHT;
	data->BackGroundImage.Width = WINDOW_WIDTH;
	Renderer_DrawImage(&data->BackGroundImage,0 ,0);
	/*data->TestImage.Height = WINDOW_HEIGHT * 0.6;
	data->TestImage.Width = WINDOW_WIDTH * 0.8;
	Renderer_DrawImage(&data->TestImage, WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.1);*/
	
	
	SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
	Renderer_DrawTextBlended(&data->TestText, 450, 600, color);
	/*switch (data->RenderMode)
	{
	case SOLID:
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawTextSolid(&data->TestText, 400, 350, color);
	}
	break;
	case SHADED:
	{
		SDL_Color bg = { .a = 255 };
		SDL_Color fg = { .r = 255, .g = 255, .a = 255 };
		Renderer_DrawTextShaded(&data->TestText, 400, 350, fg, bg);
	}
	break;
	case BLENDED:
	{
		Renderer_DrawImage(&data->TestImage, 400, 400);
		SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
		Renderer_DrawTextBlended(&data->TestText, 400, 350, color);
	}
	break;
	}*/

	

}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	for (int32 i = 0; i < 10; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}
	Text_FreeText(&data->TestText);

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region MainScene
//const wchar_t* str2[] = {
//	L"여기서는 사운드와 이미지 블렌딩에 대해서 알아봅시다.",
//	L"화살표키로 이미지를 이동시킬 수 있습니다.",
//	L"E키를 누르면 이펙트를 재생시킬 수 있습니다. 이펙트 소리가 작으니 볼륨을 낮춘 후 진행하세요.",
//	L"M키로 음악을 끄거나 켤 수 있습니다.",
//	L"P키로 음악을 멈추거나 재개할 수 있습니다.",
//	L"1번과 2번으로 볼륨을 조절할 수 있습니다.",
//	L"WASD로 이미지의 스케일을 조정할 수 있습니다.",
//	L"KL키로 이미지의 투명도를 조절할 수 있습니다."
//};

#define GUIDELINE_COUNT 8

typedef struct MainSceneData
{
	Text		GuideLine[GUIDELINE_COUNT];
	Music		BGM;
	float		Volume;
	SoundEffect Effect;
	Image		BackGround;
	float		Speed;
	int32		X;
	int32		Y;
	int32		Alpha;
} MainSceneData;

void logOnFinished(void)
{
	LogInfo("You can show this log on stopped the music");
}

void log2OnFinished(int32 channel)
{
	LogInfo("You can show this log on stopped the effect");
}

void init_main(void)
{
	g_Scene.Data = malloc(sizeof(MainSceneData));
	memset(g_Scene.Data, 0, sizeof(MainSceneData));

	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	/*for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "d2coding.ttf", 16, str2[i], wcslen(str2[i]));
	}*/
	
	Image_LoadImage(&data->BackGround, "unnamed.jfif");

	Audio_LoadMusic(&data->BGM, "SOUND_PROLOGUE_1.mp3");
	Audio_HookMusicFinished(logOnFinished);
	Audio_LoadSoundEffect(&data->Effect, "effect2.wav");
	Audio_HookSoundEffectFinished(log2OnFinished);
	Audio_PlayFadeIn(&data->BGM, INFINITY_LOOP, 3000);

	data->Volume = 1.0f;

	data->Speed = 400.0f;
	data->X = 400;
	data->Y = 400;
	data->Alpha = 255;
}

void update_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	if (Input_GetKeyDown('E'))
	{
		Audio_PlaySoundEffect(&data->Effect, 1);
	}

	if (Input_GetKeyDown('M'))
	{
		if (Audio_IsMusicPlaying())
		{
			Audio_Stop();
		}
		else
		{
			Audio_Play(&data->BGM, INFINITY_LOOP);
		}
	}

	if (Input_GetKeyDown('P'))
	{
		if (Audio_IsMusicPaused())
		{
			Audio_Resume();
		}
		else
		{
			Audio_Pause();
		}
	}

	if (Input_GetKey('1'))
	{
		data->Volume -= 0.01f;
		Audio_SetVolume(data->Volume);
	}

	if (Input_GetKey('2'))
	{
		data->Volume += 0.01f;
		Audio_SetVolume(data->Volume);
	}

	if (Input_GetKey(VK_DOWN))
	{
		data->Y += data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_UP))
	{
		data->Y -= data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_LEFT))
	{
		data->X -= data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_RIGHT))
	{
		data->X += data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey('W'))
	{
		data->BackGround.ScaleY -= 0.05f;
	}

	if (Input_GetKey('S'))
	{
		data->BackGround.ScaleY += 0.05f;
	}

	if (Input_GetKey('A'))
	{
		data->BackGround.ScaleX -= 0.05f;
	}

	if (Input_GetKey('D'))
	{
		data->BackGround.ScaleX += 0.05f;
	}

	if (Input_GetKey('K'))
	{
		data->Alpha = Clamp(0, data->Alpha - 1, 255);
		Image_SetAlphaValue(&data->BackGround, data->Alpha);
	}

	if (Input_GetKey('L'))
	{
		data->Alpha = Clamp(0, data->Alpha + 1, 255);
		Image_SetAlphaValue(&data->BackGround, data->Alpha);
	}
}

void render_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawTextSolid(&data->GuideLine[i], 10, 20 * i, color);
	}

	Renderer_DrawImage(&data->BackGround, data->X, data->Y);
}

void release_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}
	Audio_FreeMusic(&data->BGM);
	Audio_FreeSoundEffect(&data->Effect);

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region ExtraScene
CsvFile csvFile;
typedef struct ExtraSceneData
{
	Text	saveText[3];
	Text	script;
	Image	BackGroundImage;
	Image	TestImage;
	int16	SelectScript;
} ExtraSceneData;
//CsvFile csvFile;
const wchar_t* str[] = {
	L"나는 김기자다.",
	L"올해 26살이지.",
	L"어제까지만 해도 방송국 기자로 일하면서 각종 특종을 취재하러 다녔지만..."
};
void init_extra(void)
{
	g_Scene.Data = malloc(sizeof(ExtraSceneData));
	memset(g_Scene.Data, 0, sizeof(ExtraSceneData));
	ExtraSceneData* data = (ExtraSceneData*)g_Scene.Data;

	Image_LoadImage(&data->BackGroundImage, "BackGround.jpg");
	Image_LoadImage(&data->TestImage, "SCENE_PROLOGUE_1.jpg");

	for (int32 i = 0; i < 3; ++i)
	{
		Text_CreateText(&data->saveText[i], "d2coding.ttf", 16, str[i], wcslen(str[i]));
	}
	data->SelectScript = 0;


	/*_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	
	memset(&csvFile, 0, sizeof(CsvFile));
	CreateCsvFile(&csvFile, "final.csv");*/

	// CSV 파일 파싱한 후 텍스트 그려본 다음
	// 유니코드 제대로 출력 안되면
	// App_Init()에 아래 구문 추가
	// setlocale(LC_ALL, "kr_KR.utf8");

	/*for (int r = 0; r < csvFile.RowCount; ++r)
	{
		for (int c = 0; c < csvFile.ColumnCount; ++c)
		{
			char* str = ParseToAscii(csvFile.Items[r][c]);
			printf("%s\t", str);
			free(str);
		}

		puts("");
	}*/
}

void update_extra(void)
{
	ExtraSceneData* data = (ExtraSceneData*)g_Scene.Data;

	//for (int r = 0; r < csvFile.RowCount; ++r)
	//{
	//	for (int c = 0; c < csvFile.ColumnCount; ++c)
	//	{
	//		char* str = ParseToAscii(csvFile.Items[r][c]);
	//		//printf("%s\t", str);
	//		

	//		free(str);
	//	}

	//	puts("");
	//}

	if (Input_GetKeyDown(VK_SPACE))
	{
		data->SelectScript++;
	}
}

void render_extra(void)
{
	ExtraSceneData* data = (ExtraSceneData*)g_Scene.Data;
	
	/*SDL_Color color = { .a = 255 };
	Renderer_DrawTextSolid(&data->TestText1, 20, 20, color);*/
	data->BackGroundImage.Height = WINDOW_HEIGHT;
	data->BackGroundImage.Width = WINDOW_WIDTH;
	Renderer_DrawImage(&data->BackGroundImage, 0, 0);
	data->TestImage.Height = WINDOW_HEIGHT * 0.6;
	data->TestImage.Width = WINDOW_WIDTH * 0.8;
	Renderer_DrawImage(&data->TestImage, WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.1);

	SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
	Renderer_DrawTextBlended(&data->saveText[data->SelectScript], WINDOW_WIDTH * 0.1, 600, color);
	

	
}

void release_extra(void)
{
	FreeCsvFile(&csvFile);
	SafeFree(g_Scene.Data);
}
#pragma endregion


bool Scene_IsSetNextScene(void)
{
	if (SCENE_NULL == s_nextScene)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Scene_SetNextScene(ESceneType scene)
{
	assert(s_nextScene == SCENE_NULL);
	assert(SCENE_NULL < scene&& scene < SCENE_MAX);

	s_nextScene = scene;
}

void Scene_Change(void)
{
	assert(s_nextScene != SCENE_NULL);

	if (g_Scene.Release)
	{
		g_Scene.Release();
	}

	switch (s_nextScene)
	{
	case SCENE_TITLE:
		g_Scene.Init = init_title;
		g_Scene.Update = update_title;
		g_Scene.Render = render_title;
		g_Scene.Release = release_title;
		break;
	case SCENE_MAIN:
		g_Scene.Init = init_main;
		g_Scene.Update = update_main;
		g_Scene.Render = render_main;
		g_Scene.Release = release_main;
		break;
	case SCENE_EXTRA:
		g_Scene.Init = init_extra;
		g_Scene.Update = update_extra;
		g_Scene.Render = render_extra;
		g_Scene.Release = release_extra;
		break;
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}