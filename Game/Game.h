#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>
#define MAPSIZE 15

typedef struct {
	int x;
	int y;
}Position;  // 좌표

typedef struct {
	Position player;
	Position monster;
}ObjPositions;  // 오브젝트 좌표

typedef struct {
	int stageLevel;
	int stageMapSize;
	int clearMoveCount;
	int MoveCount;
}StageInfo;   // 스테이지 구성요소 (오브젝트 제외)

extern const char PLAYER;
extern const char MONSTER;
extern const char WALL;
static int used_skill = 1;

void GameRule(char input);
int GameOver(ObjPositions obj, StageInfo* clearlevel, char input);
void Init_Map(char stage[MAPSIZE][MAPSIZE * 2], int currentSize);
void PositionUpdate(char stage[MAPSIZE][MAPSIZE * 2], ObjPositions* obj);
void MovePlayer(ObjPositions* player, char input, char stage[MAPSIZE][MAPSIZE * 2]);
void MoveMonster(ObjPositions* obj, char input, char stage[MAPSIZE][MAPSIZE * 2]);
void PrintMap(char stage[MAPSIZE][MAPSIZE * 2], int currentSize);
void PrintMessage(StageInfo* clearmovecount, const char* message);
int IsMoveKey(char input, char* message, StageInfo* movecount);
void UsingSkill(char input, ObjPositions* player, StageInfo* stage);
void ClearStage(StageInfo* nextlevel, ObjPositions* obj);
void NextStage(StageInfo* stagelevel_movecount);
void MoveCountPrint(char input, ObjPositions obj, StageInfo* moveCount);