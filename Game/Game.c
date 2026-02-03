#include "Game.h"

int main()
{
	char input = 0;
	ObjPositions object = {
		.player = {2, 2},
		.monster = {27, 13}
	};
	StageInfo stageinfo = { 1, MAPSIZE, 20, 0 };
	char uiMessage[50] = "";
	char STAGE[MAPSIZE][MAPSIZE * 2]; // 맵 사이즈


	// 룰에 대한 설명
	GameRule(input);

	while (1) // 무한 루프
	{
		// 만약 몬스터가 플레이어를 따라잡거나 Q를 누르면 종료
		if (GameOver(object, &stageinfo, input))
		{
			break;
		}

		// 맵 초기화
		Init_Map(STAGE, stageinfo.stageMapSize);

		// 위치 업데이트
		PositionUpdate(STAGE, &object);

		// 맵 프린트
		PrintMap(STAGE, stageinfo.stageMapSize);

		// 메세지 프린트
		PrintMessage(&stageinfo, uiMessage);

		// 입력 받기
		input = _getch(); // Enter 없이 바로 키 입력 받기

		// 입력할 때 마다 무브 카운트 증가
		IsMoveKey(input, uiMessage, &stageinfo);

		// 스킬 사용 조건
		UsingSkill(input, &object, &stageinfo);

		// 플레이어 움직임
		MovePlayer(&object, input, STAGE);

		// 몬스터 이동
		MoveMonster(&object, input, STAGE);

		// 클리어 표시
		ClearStage(&stageinfo, &object);

		// 스테이지별 이동 횟수
		NextStage(&stageinfo);
	}


	// 게임 종료시 무브 카운트 (Q를 눌러서 종료했을 때도 포함)
	MoveCountPrint(input, object, &stageinfo);

	return 0;
}



//1. 맵의 크기 설정 (완료) 
//2. 플레이어, 몬스터 등 맵 안에 등장하는 물건 설정 (완료)
//3. 맵의 벽 설정 (완료)
//4. 플레이어의 움직임 설정 (완료)
//5. 플레이어가 벽에 닿았을 때 설정 (완료)
//6. 몬스터 움직임 설정 (완료)
//0. 내가 만들려고 하는 게임 : 플레이어를 따라오는 몬스터를 최대한 늦게 따라잡히기
//0-1. 플레이어가 한칸 움직이면 몬스터도 플레이어를 향해서 한칸 움직인다. (완료)
//0-2. 플레이어가 움직인 횟수를 카운트하고 따라잡혔을 때 횟수가 클리어에 필요한 횟수보다
//     많으면 다음 스테이지 그렇지 않으면 게임오버 (완료)
//0-3. 다음 스테이지에서는 맵이 작아짐 (완료)
//0-4. 가능하면 벽에 닿았을 때 반대쪽으로 가는 스킬을 딱 한 번 쓸 수 있게 하고 싶다. (완료)


// Version 1.0.0 : 맵과 플레이어, 몬스터의 움직임 설정 완료, 스테이지 클리어 조건 생성
// Version 1.0.1 : 게임소개 출력 후 맵 클리어 그리고 게임 시작 할 수 있게 하기
// Version 1.0.2 : 클리어 하거나 실패했을 때 즉시 종료
// Version 1.0.3 : wasd 외의 버튼을 눌러도 카운트가 되는 버그 수정
//                wasd 외의 버튼을 눌러도 몬스터가 따라오는 로직 수정
//                게임 화면 밑에 클리어까지 남은 횟수를 표기
//                플레이어와 몬스터의 좌표를 구조체로 정의
// Version 1.0.4 : 클리어 실패가 표시되지 않는 버그 수정
//				  클리어에 필요한 움직임 수 변동
//				  클리어 실패 메세지가 중복으로 나오는 버그
// Version 1.0.5 : 1스테이지를 클리어 했을 때 클리어 표시가 안되는 버그 수정
//				  q를 눌러도 게임이 종료되지 않는 버그 수정
// Version 1.0.6 : 스테이지의 반대편으로 가는 기능 추가
//				   맵 사이즈 수정
// Version 1.0.7 : 맵이 작아졌을 때 오브젝트가 맵 밖에 있을 경우 그대로 사라지는 버그 수정
// Version 1.0.8 : 위치를 초기화 했을 때 벽에 끼이는 버그 수정
// Version 1.0.9 : 4스테이지를 클리어 했을 때 맵이 한 번 출력 되고 클리어 문장이 나오는 버그 수정
//				  4스테이지에 스킬을 무한으로 쓰거나 쓰지 못하는 버그 수정