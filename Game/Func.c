#include "Game.h"

const char PLAYER = '!';
const char MONSTER = '&';
const char WALL = '#';

void GameRule(char input)
{
	// 게임에 대한 설명
	printf("WASD를 이용해서 몬스터(&)를 피해서 움직여보세요!\n");
	printf("20번 움직이면 다음 스테이지로 이동합니다!\n");

	// 버튼을 눌러서 게임 시작
	printf("R를 눌러서 게임을 시작 / Q를 눌러서 게임을 종료하세요!\n");
	while (1)
	{
		input = _getch();
		if (input != 'r' && input != 'R')
		{
			printf("잘못된 입력입니다! r를 눌러서 게임을 시작하세요!\n");
			continue;
		}
		break;
	}
}

int GameOver(ObjPositions obj, StageInfo* clearlevel, char input)
{
	// 게임 멈춤 버튼
	if (input == 'q' || input == 'Q')
	{
		return 1;
	}
	else if (clearlevel->stageLevel > 4)
	{
		system("cls");
		printf("====================================\n");
		printf("   모든 스테이지를 클리어했습니다!  \n");
		printf("         축하합니다! YOU WIN!       \n");
		printf("====================================\n");
		return 1;
	}
	return obj.monster.x == obj.player.x && obj.monster.y == obj.player.y;
}

void Init_Map(char stage[MAPSIZE][MAPSIZE * 2], int currentSize)
{
	//맵 초기화
	for (int y = 0; y < currentSize; y++)
	{
		for (int x = 0; x < currentSize * 2; x++)
		{
			if (y == 0 || y == currentSize - 1 || x == 0 || x == currentSize * 2 - 2)
				stage[y][x] = WALL;
			else
				stage[y][x] = ' ';
		}
		stage[y][currentSize * 2 - 1] = '\0'; // 문자열 끝
	}
}

void PositionUpdate(char stage[MAPSIZE][MAPSIZE * 2], ObjPositions* obj)
{
	// 플레이어와 몬스터 위치 업데이트
	stage[obj->player.y][obj->player.x] = PLAYER;
	stage[obj->monster.y][obj->monster.x] = MONSTER;
}

void MovePlayer(ObjPositions* player, char input, char stage[MAPSIZE][MAPSIZE * 2])
{
	if ((input == 'w' || input == 'W') && stage[player->player.y - 1][player->player.x] != WALL)
		player->player.y--;
	else if ((input == 's' || input == 'S') && stage[player->player.y + 1][player->player.x] != WALL)
		player->player.y++;
	else if ((input == 'a' || input == 'A') && stage[player->player.y][player->player.x - 1] != WALL)
		player->player.x--;
	else if ((input == 'd' || input == 'D') && stage[player->player.y][player->player.x + 1] != WALL)
		player->player.x++;
}

void MoveMonster(ObjPositions* obj, char input, char stage[MAPSIZE][MAPSIZE * 2])
{
	if (input == 'w' || input == 'a' || input == 's' || input == 'd' ||
		input == 'W' || input == 'A' || input == 'S' || input == 'D')
	{
		if (obj->monster.x < obj->player.x && stage[obj->monster.y][obj->monster.x + 1] != WALL)
			obj->monster.x++;
		else if (obj->monster.x > obj->player.x && stage[obj->monster.y][obj->monster.x - 1] != WALL)
			obj->monster.x--;

		if (obj->monster.y < obj->player.y && stage[obj->monster.y + 1][obj->monster.x] != WALL)
			obj->monster.y++;
		else if (obj->monster.y > obj->player.y && stage[obj->monster.y - 1][obj->monster.x] != WALL)
			obj->monster.y--;
	}
}

void PrintMap(char stage[MAPSIZE][MAPSIZE * 2], int currentSize)
{
	system("cls"); // 화면 지우기
	for (int y = 0; y < currentSize; y++)
	{
		printf("%s\n", stage[y]);
	}
}

void PrintMessage(StageInfo* clearmovecount, const char* message)
{
	printf("\n클리어 까지 남은 횟수 : %d\n", clearmovecount->clearMoveCount - clearmovecount->MoveCount);
	if (message[0] != '\0')
	{
		printf("%s\n", message);
	}
}

int IsMoveKey(char input, char* message, StageInfo* movecount)
{
	if (input == 'w' || input == 'a' || input == 's' || input == 'd' ||
		input == 'W' || input == 'A' || input == 'S' || input == 'D')
	{
		strcpy(message, "");
		movecount->MoveCount++;
		return 1;
	}


	else
	{
		// ui에 저장
		strcpy(message, "잘못된 입력입니다!");
		return 0;
	}
}

void UsingSkill(char input, ObjPositions* player, StageInfo* stage)
{
	// 이 기능은 2, 4스테이지에 한 번 만 적용
	if (stage->stageLevel == 2 || stage->stageLevel == 4)
	{

		// 위쪽 벽에 닿을 경우
		if (used_skill == 1)
		{
			if (input == 'w' || input == 'W')
			{
				if (player->player.y <= 1)
				{
					player->player.y = stage->stageMapSize - 2;
					used_skill--;
				}

			}

			// 아래쪽 벽에 닿을 경우
			if (input == 's' || input == 'S')
			{
				if (player->player.y >= stage->stageMapSize - 2)
				{
					player->player.y = 1;
					used_skill--;
				}
			}

			// 왼쪽 벽에 닿은 경우
			if (input == 'a' || input == 'A')
			{
				if (player->player.x <= 1)
				{
					player->player.x = (stage->stageMapSize * 2) - 3;
					used_skill--;
				}
			}

			// 오른쪽 벽에 닿은 경우
			if (input == 'd' || input == 'D')
			{
				if (player->player.x >= (stage->stageMapSize * 2) - 3)
				{
					player->player.x = 1;
					used_skill--;
				}
			}
		}
	}
}

void ClearStage(StageInfo* nextlevel, ObjPositions* obj)
{
	if (nextlevel->MoveCount >= nextlevel->clearMoveCount)
	{
		printf("===================================================\n");
		printf("---축하합니다! %d스테이지를 클리어 하셨습니다!---\n", nextlevel->stageLevel);
		printf("===================================================\n");

		if (nextlevel->stageLevel == 1)
		{
			printf("2스테이지와 4스테이지는 딱 한 번 만 반대쪽 벽으로 넘어갈 수 있습니다!!");
		}
		_getch(); // 플레이어가 메세지를 읽을 수 있도록 입력 전까지 화면 멈춤

		nextlevel->stageLevel++;
		nextlevel->MoveCount = 0;

		// 클리어 후 플레이어 위치 초기화
		obj->player.x = 2;
		obj->player.y = 2;

		// 클리어 후 몬스터 위치 초기화
		if (nextlevel->stageLevel == 1)
		{
			nextlevel->stageMapSize = 15;
		}
		else if (nextlevel->stageLevel == 2)
		{
			nextlevel->stageMapSize = 13;
		}
		else if (nextlevel->stageLevel == 3)
		{
			nextlevel->stageMapSize = 10;
		}
		else if (nextlevel->stageLevel >= 4)
		{
			nextlevel->stageMapSize = 9;
			used_skill = 1;
		}

		obj->monster.x = (nextlevel->stageMapSize * 2) - 4;
		obj->monster.y = nextlevel->stageMapSize - 2;
	}
}

void NextStage(StageInfo* stagelevel_movecount)
{
	switch (stagelevel_movecount->stageLevel)
	{
	case 1:
		stagelevel_movecount->clearMoveCount = 20;
		stagelevel_movecount->stageMapSize = 15;
		break;

	case 2:
		stagelevel_movecount->clearMoveCount = 17;
		stagelevel_movecount->stageMapSize = 13;
		break;

	case 3:
		stagelevel_movecount->clearMoveCount = 14;
		stagelevel_movecount->stageMapSize = 10;
		break;

	case 4:
		stagelevel_movecount->clearMoveCount = 13;
		stagelevel_movecount->stageMapSize = 9;
		break;
	}
}

void MoveCountPrint(char input, ObjPositions obj, StageInfo* moveCount)
{
	// 무브 카운트 표시
	if (input == 'q' || input == 'Q'
		|| obj.monster.x == obj.player.x && obj.monster.y == obj.player.y)
	{
		printf("---클리어 실패~!---\n");
		printf("%d스테이지를 %d번 움직였습니다!\n", moveCount->stageLevel, moveCount->MoveCount);
	}

}

