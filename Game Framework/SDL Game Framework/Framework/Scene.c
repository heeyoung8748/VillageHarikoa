#include "stdafx.h"
#include "Scene.h"

#include "Framework.h"
#include "Framework/Csv.h"

Scene g_Scene;

bool isCreated = false;

static ESceneType s_nextScene = SCENE_NULL;

#pragma region TitleScene

#define SOLID 0
#define SHADED 1
#define BLENDED 2

void logOnFinished(void) // 배경음악 출력 관련 필수 항목
{
    LogInfo("You can show this log on stopped the music");
}

// const wchar_t* str[] = {
//    L"여기는 타이틀씬입니다. 텍스트와 관련된 여러가지를 테스트해봅시다.",
// };

typedef struct TitleSceneData
{
    Image   TitleBackGroundImage;
    Text   Title;
    Music   TitleMusic;

} TitleSceneData;

void init_title(void)
{

    g_Scene.Data = malloc(sizeof(TitleSceneData));
    memset(g_Scene.Data, 0, sizeof(TitleSceneData));
    TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

    Image_LoadImage(&data->TitleBackGroundImage, "SCENE_INTRO.jpg");
    Text_CreateText(&data->Title, "d2coding.ttf", 20, L"- 스페이스바를 누르면 시작합니다 -", sizeof(L"- 스페이스바를 누르면 시작합니다 -"));
    Audio_LoadMusic(&data->TitleMusic, "BGM_INTRO.mp3");
    Audio_HookMusicFinished(logOnFinished);
    Audio_PlayFadeIn(&data->TitleMusic, INFINITY_LOOP, 3000);


}

void update_title(void)
{
    TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
    if (Input_GetKeyDown(VK_SPACE))
    {
        Scene_SetNextScene(SCENE_PAGE);
    }

}

void render_title(void)
{
    TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
    data->TitleBackGroundImage.ScaleX = 1;
    data->TitleBackGroundImage.ScaleY = 1;
    Renderer_DrawImage(&data->TitleBackGroundImage, 0, 0);
    SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
    Renderer_DrawTextSolid(&data->Title, 471, 675, color);
}

void release_title(void)
{
    TitleSceneData* data = (TitleSceneData*)g_Scene.Data;



    SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region PageScene

#include "Game/PageManager.h"

typedef struct PageSceneData
{
    PageManager PageManager;
} PageSceneData;

void init_page(void)
{
    g_Scene.Data = malloc(sizeof(PageSceneData));

    PageSceneData* data = (PageSceneData*)g_Scene.Data;
    memset(data, 0, sizeof(PageSceneData));


    PageManager_Init(&data->PageManager);
}

void update_page(void)
{
    PageSceneData* data = (PageSceneData*)g_Scene.Data;

    PageManager_Update(&data->PageManager);
}

void render_page(void)
{
    PageSceneData* data = (PageSceneData*)g_Scene.Data;

    PageManager_Render(&data->PageManager);
}

void release_page(void)
{
    PageSceneData* data = (PageSceneData*)g_Scene.Data;

    PageManager_Release(&data->PageManager);

    SafeFree(g_Scene.Data);
}

#pragma endregion

#pragma region CreditScene

const wchar_t* str2[] = {
   L"        CREDIT",
   L"       - 기획 -",
   L"       PD 황현태",
   L"        박민응",
   L"        남정현",
   L"    - 프로그래머 -",
   L"        권희영",
   L"        김재민",
   L"        이재혁"
};

typedef struct CreditSceneData
{
    Text   CreditText[9];
    int16   X;
    int16   Y;
    int      TextCoord[9];
    Image   CreditBackGroundImage;
    Music   CreditMusic;
    float   elapsedTime;
} CreditSceneData;



void init_credit()
{
    g_Scene.Data = malloc(sizeof(CreditSceneData));
    memset(g_Scene.Data, 0, sizeof(CreditSceneData));
    CreditSceneData* data = (CreditSceneData*)g_Scene.Data;

    // if (!isCreated)
    // {
    //     CreateCsvFile(&csvFile, "db.csv");  // 희희 
    //     isCreated = true;
    //
    // }

    data->elapsedTime = 0.0f;
    data->X = 510;
    data->Y = 500;
    Image_LoadImage(&data->CreditBackGroundImage, "SCENE_ENDING_CREDIT.jpg");
    for (int i = 0; i < 9; i++)
    {
        Text_CreateText(&data->CreditText[i], "d2coding.ttf", 20, str2[i], sizeof(L"스페이스바를 누르면 시작합니다"));
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
    data->CreditBackGroundImage.ScaleX = 1;
    data->CreditBackGroundImage.ScaleY = 1;
    Renderer_DrawImage(&data->CreditBackGroundImage, 0, 0);
    int count = 0;
    SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
    for (int i = 40; i < 400; i += 40)
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
	case SCENE_PAGE:
		g_Scene.Init = init_page;
		g_Scene.Update = update_page;
		g_Scene.Render = render_page;
		g_Scene.Release = release_page;
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