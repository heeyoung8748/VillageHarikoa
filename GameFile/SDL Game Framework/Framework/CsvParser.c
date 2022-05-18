#include "stdafx.h"
#include "csv.h"
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#include <crtdbg.h>

void Parser(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	CsvFile csvFile;
	memset(&csvFile, 0, sizeof(CsvFile));
	CreateCsvFile(&csvFile, "final.csv");

	// CSV 파일 파싱한 후 텍스트 그려본 다음
	// 유니코드 제대로 출력 안되면
	// App_Init()에 아래 구문 추가
	// setlocale(LC_ALL, "kr_KR.utf8");

	for (int r = 0; r < csvFile.RowCount; ++r)
	{
		for (int c = 0; c < csvFile.ColumnCount; ++c)
		{
			char* str = ParseToAscii(csvFile.Items[r][c]);
			printf("%s\t", str);
			free(str);
		}

		puts("");
	}

	FreeCsvFile(&csvFile);

	return;
}