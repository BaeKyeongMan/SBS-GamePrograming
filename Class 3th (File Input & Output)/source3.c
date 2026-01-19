#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

enum State{
	IDLE = 1,
	ATTACK,
	DIE

	// 열거형은 값을 따로 설정할 수 있으며, 따로 설정된 다음의 값은 그 전의 값엣 
	// 하나 증가된 값으로 설정됩니다. 
};

void Select(enum State state);

int main()
{
#pragma region 열거형
	// 관련된 상수의 값을 이름으로 정의한 집합의 자료형입니다.
	/*enum State state = 0;
	Select(state);*/

#pragma endregion


	return 0;
}

void Select(enum State state)
{

	printf("현재 상태를 입력하세요. (1: 대기, 2: 공격, 3: 사망)");
	scanf("%d", &state);

	switch (state)
	{
	case IDLE:
		printf("현재 대기 상태입니다.\n");
		break;
	case ATTACK:
		printf("현재 공격 상태입니다.\n");
		break;
	case DIE:
		printf("현재 사망 상태입니다.\n");
		break;
	default:
		printf("잘못된 입력입니다.\n");
		break;
	}
}
