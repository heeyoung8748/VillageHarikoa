#include "stdafx.h"
#include "Scene.h"
#include "csv.h"
#include "Text.h"

#include "Framework.h"

Scene g_Scene;
CsvFile csvFile;
Text CsvText[100][100]; // 여기는 계속 내가 손으로 바꿔줘야함 //여기 크게 하니까 에러 안난다


bool isCreated = false;


static ESceneType s_nextScene = SCENE_NULL;

#pragma region TitleScene

#define SOLID 0
#define SHADED 1
#define BLENDED 2

const wchar_t* str[] = {
	L"여기는 타이틀씬입니다. 텍스트와 관련된 여러가지를 테스트해봅시다.",
};

typedef struct TitleSceneData
{
	
} TitleSceneData;

void init_title(void)
{
	if (!isCreated)
	{
		CreateCsvFile(&csvFile, "db.csv");  // 희희 
		isCreated = true;

	}

	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	for (int r = 0; r < csvFile.RowCount; ++r)
	{
		for (int c = 0; c < csvFile.ColumnCount; ++c)
		{
			wchar_t* str = ParseToUnicode(csvFile.Items[r][c]);
			Text_CreateText(&CsvText[r][c], "d2coding.ttf", 16, str, wcslen(str));
			free(str);
		}

		//puts("");
	}

}

void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	
}

void render_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	
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
	
} MainSceneData;

void logOnFinished(void) // 배경음악 출력 관련 필수 항목
{
	LogInfo("You can show this log on stopped the music");
}

void log2OnFinished(int32 channel) // 이펙트사운드 출력 관련 필수 항목
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
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}