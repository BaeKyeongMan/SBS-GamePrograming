#include <stdio.h>
#include <windows.h>

enum Color
{
	BLACK,
	DARKBLUE,
	DARKGREEN,
	DARKSKYBLUE,
	DARKRED,
	DARKVIOLET,
	DARKYELLOW,
	GRAY,
	DARKGRAY,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	VIOLET,
	YELLOW,
	WHITE,
};

int main()
{
	for (int i = 0; i < 16; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);

		if (i != 0 && i % 3 == 0)
		{
			system("pause");
		}

		printf("color index : %d\n", i);
	}

	return 0;
}