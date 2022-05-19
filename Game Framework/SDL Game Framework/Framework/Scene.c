#include "stdafx.h"
#include "Scene.h"
#include "csv.h"
#include "Text.h"

#include "Framework.h"

Scene g_Scene;
CsvFile csvFile;
Text CsvText[100][100]; // ����� ��� ���� ������ �ٲ������ //���� ũ�� �ϴϱ� ���� �ȳ���


bool isCreated = false;


static ESceneType s_nextScene = SCENE_NULL;

#pragma region TitleScene

#define SOLID 0
#define SHADED 1
#define BLENDED 2

void logOnFinished(void) // ������� ��� ���� �ʼ� �׸�
{
	LogInfo("You can show this log on stopped the music");
}

const wchar_t* str[] = {
	L"����� Ÿ��Ʋ���Դϴ�. �ؽ�Ʈ�� ���õ� ���������� �׽�Ʈ�غ��ô�.",
};

typedef struct TitleSceneData
{
	Image	TitleBackGroundImage;
	Text	Title;
	Music	TitleMusic;

} TitleSceneData;

void init_title(void)
{

	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	Image_LoadImage(&data->TitleBackGroundImage, "TitleTestImage.jpg");
	Text_CreateText(&data->Title, "d2coding.ttf", 20, L"�����̽��ٸ� ������ �����մϴ�", sizeof(L"�����̽��ٸ� ������ �����մϴ�"));
	Audio_LoadMusic(&data->TitleMusic, "powerful.mp3");
	Audio_HookMusicFinished(logOnFinished);
	Audio_PlayFadeIn(&data->TitleMusic, INFINITY_LOOP, 3000);


}

void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_CREDIT);
	}
	
}

void render_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	data->TitleBackGroundImage.ScaleX = WINDOW_WIDTH;
	data->TitleBackGroundImage.ScaleY = WINDOW_HEIGHT;
	Renderer_DrawImage(&data->TitleBackGroundImage, 0, 0 );
	SDL_Color color = {.r = 255, .g =255, .b = 255, .a = 255 };
	Renderer_DrawTextSolid(&data->Title, 450, 500, color);
}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region MainScene



typedef struct MainSceneData
{
	int a;

} MainSceneData;



void log2OnFinished(int32 channel) // ����Ʈ���� ��� ���� �ʼ� �׸�
{
	LogInfo("You can show this log on stopped the effect");
}

void init_main(void)
{
	g_Scene.Data = malloc(sizeof(MainSceneData));
	memset(g_Scene.Data, 0, sizeof(MainSceneData));

	MainSceneData* data = (MainSceneData*)g_Scene.Data;

}

void update_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	
}

void render_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	
}

void release_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region CreditScene

const wchar_t* str2[] = {
   L"CREDIT",
   L"PD ������",
   L"���丮��ȹ �̴���",
   L"������ȹ �蹫��",
   L"-",
   L"�������α׷��� ����",
   L"�������� �����",
   L"^^���α׷��� ������"
};

typedef struct CreditSceneData
{
	Text	CreditText[8];
	int16	X;
	int16	Y;
	int		TextCoord[8];
	Image	CreditBackGroundImage;
	Music	CreditMusic;
	float	elapsedTime;
} CreditSceneData;



void init_credit()
{
	g_Scene.Data = malloc(sizeof(CreditSceneData));
	memset(g_Scene.Data, 0, sizeof(CreditSceneData));
	CreditSceneData* data = (CreditSceneData*)g_Scene.Data;

	if (!isCreated)
	{
		CreateCsvFile(&csvFile, "db.csv");  // ���� 
		isCreated = true;

	} 

	data->elapsedTime = 0.0f;
	data->X = 500;
	data->Y = 500;
	Image_LoadImage(&data->CreditBackGroundImage, "TitleTestImage.jpg");
	for (int i = 0; i < 8; i++)
	{
		Text_CreateText(&data->CreditText[i], "d2coding.ttf", 20, str2[i], sizeof(L"�����̽��ٸ� ������ �����մϴ�"));
	}

	Audio_LoadMusic(&data->CreditMusic, "powerful.mp3");
	Audio_HookMusicFinished(logOnFinished);
	Audio_PlayFadeIn(&data->CreditMusic, INFINITY_LOOP, 3000);

}
void update_credit()
{
	CreditSceneData* data = (CreditSceneData*)g_Scene.Data;
	data->elapsedTime += Timer_GetDeltaTime();
	if (data->elapsedTime > 0.005f)
	{
		data->Y--;
		data->elapsedTime = 0.0f;
	}
}
void render_credit()
{
	CreditSceneData* data = (CreditSceneData*)g_Scene.Data;
	data->CreditBackGroundImage.ScaleX = WINDOW_WIDTH;
	data->CreditBackGroundImage.ScaleY = WINDOW_HEIGHT;
	Renderer_DrawImage(&data->CreditBackGroundImage, 0, 0);
	int count = 0;
	SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
	for (int i = 40; i < 360; i+=40)
	{
		Renderer_DrawTextSolid(&data->CreditText[count], data->X, data->Y + i, color);
		count++;
	}
}
void release_credit()
{
	
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
	case SCENE_CREDIT:
		g_Scene.Init = init_credit;
		g_Scene.Update = update_credit;
		g_Scene.Render = render_credit;
		g_Scene.Release = release_credit;
		break;
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}