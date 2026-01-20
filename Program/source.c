#include <stdio.h>
#include <Windows.h>
#include <conio.h>

void position(int x, int y)
{
	COORD position = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

int main()
{
	char key = 0;
	int x = 0;
	int y = 0;

	while (1)
	{

		key = _getch();

		if (key == -32 || key == 0)
		{
			key = _getch();
		}

		switch (key)
		{
		case 119: y -= 1;
			break;

		case 97: x -= 1;
			break;

		case 115: y += 1;
			break;

		case 100: x += 1;
			break;

		default: printf("excetion\n");
			break;
		}

		system("cls");

		position(x, y);

		printf("¡Ú");
	}

	return 0;
}