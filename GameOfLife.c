#include <stdio.h>
#include <stdlib.h>
#include "EngineOfLife.h"
#include <Windows.h>
#include <time.h>
#include <conio.h>
#define MAX 1000
#define TIME 100
//system("cls"); - очищает консоль

void main()
{
	//Консоль
	HANDLE consol = GetStdHandle(STD_OUTPUT_HANDLE);
	//Позиция курсора
	COORD pos; pos.X = 1; pos.Y = 0;
	//SetConsoleCursorPosition(consol, pos);

	//Начальные настройки
	char periodic = 0, random = 0, schitka, gameFlag = 0, c = ' ', FileNum;
	//Поле, x, y.
	int x, y; char* pole = 0;
	printf("Set the starting settings:\n");
	//Будет ли таблица периодичной (из правого переходит в левое, из нижнего в верхнее и т.п.)?
	printf("Will pole be periodic? (Y or N)\n");
	do
	{
		scanf_s("%c", &periodic);
	} while (!((periodic == 'Y') || (periodic == 'N')));
	//Считать ли позицию с файла?
	printf("Do you want to read pole with dead/alive cells from file? (Y or N)\n");
	do
	{
		scanf_s("%c", &schitka);
	} while (!((schitka == 'Y') || (schitka == 'N')));
	if (schitka == 'Y')
	{
		system("cls");
		printf("Enter the file number from 0 to 9:\n");
		do
		{
			scanf_s("%c", &FileNum);
		} while (!((FileNum <= 57) && (FileNum >= 48)));
		pole = ChtenieFaila(pole, &x, &y, FileNum);
	}
	else
	{
		//Будут ли рандомизированны ячейки в поле?
		printf("Will dead/alive cells in pole be randomized? (Y or N)\n");
		do
		{
			scanf_s("%c", &random);
		} while (!((random == 'Y') || (random == 'N')));

		//Задача размеров поля
		char fl = 0;
		while (fl == 0)
		{
			printf("Enter 2 <= x <= 100 (stolbiki) and 2 <= y <= 100 (stroki)\n");
			do
			{
				scanf_s("%d%d", &x, &y);
			} while (!((x >= 2) && (y >= 2) && (x <= 100) && (y <= 100)));
			if (x > 59 || y > 29)
			{
				printf("With x > 59 or y > 29 your table will be unreadable/hard to read\n");
				printf("Are you sure? (Y or N)\n");
				do
				{
					scanf_s("%c", &fl);
				} while (!((fl == 'Y') || (fl == 'N')));
				if (fl == 'Y')
					fl = 1;
				else if (fl == 'N')
					fl = 0;
			}
			else
				fl = 1;
		}
		//Создание поля
		pole = (char*)malloc(y * x * sizeof(char));
		if (random == 'Y')
		{
			srand(time(NULL));
			for (int c = 0; c < y; c++)
			{
				for (int d = 0; d < x; d++)
				{
					pole[x * c + d] = (rand() % 2) + 1;
					//pole[x * c + d] = 2; // - For Debug
				}
			}
		}
		else
		{
			for (int c = 0; c < y; c++)
			{
				for (int d = 0; d < x; d++)
				{
					pole[x * c + d] = 1;
				}
			}
		}
	}
	//Начальный показ поля
	system("cls");
	PokazPolya(pole, x, y);
	//Задача начального расположения клеток
	printf("Print w/W _ a/A _ s/S _ d/D to go on pole\n");
	printf("If you want to make cells alive/dead, print e/E (e/E means e or E)\n");
	printf("If you want to start the game, print f/F. (f/F means f or F)\n");
	do
	{
		SetConsoleCursorPosition(consol, pos);
		c = _getch();
		switch (c)
		{
		case 'w': case 'W':
			if (pos.Y > 0)
				pos.Y -= 1;
			SetConsoleCursorPosition(consol, pos);
			break;
		case 's': case 'S':
			if (pos.Y < y-1)
				pos.Y += 1;
			SetConsoleCursorPosition(consol, pos);
			break;
		case 'a': case 'A':
			if (pos.X > 1)
				pos.X -= 2;
			SetConsoleCursorPosition(consol, pos);
			break;
		case 'd': case 'D':
			if (pos.X < 2*x-2)
				pos.X += 2;
			SetConsoleCursorPosition(consol, pos);
			break;
		case 'e': case 'E':
			if (pole[pos.Y * x + pos.X / 2] == 1)
				pole[pos.Y * x + pos.X / 2] = 2;
			else if (pole[pos.Y * x + pos.X / 2] == 2)
				pole[pos.Y * x + pos.X / 2] = 1;
			Sleep(50);
			system("cls");
			PokazPolya(pole, x, y);
			printf("Print w/W _ a/A _ s/S _ d/D to go on pole\n");
			printf("If you want to make cells alive/dead, print e/E (e/E means e or E)\n");
			printf("If you want to save your pole, print c/C. (c/C means c or C)\n");
			printf("If you want to start the game, print f/F. (f/F means f or F)\n");
			break;
		case 'f': case 'F':
			gameFlag = 1;
			break;
		case 'c': case 'C':
			system("cls");
			printf("Enter the file number from 0 to 9:\n");
			do
			{
				scanf_s("%c", &FileNum);
			} while (!((FileNum <= 57) && (FileNum >= 48)));
			ZapisFaila(pole, x, y, FileNum);
			Sleep(50);
			system("cls");
			PokazPolya(pole, x, y);
			printf("Print w/W _ a/A _ s/S _ d/D to go on pole\n");
			printf("If you want to make cells alive/dead, print e/E (e/E means e or E)\n");
			printf("If you want to save your pole, print c/C. (c/C means c or C)\n");
			printf("If you want to start the game, print f/F. (f/F means f or F)\n");
			break;
		default:
			break;
		}
	} while (!(gameFlag == 1));

	//Начало игры
	system("cls");
	PokazPolya(pole, x, y);
	int flag = 0;
	do
	{
		//Расчёт одного шага
		if (periodic == 'Y')
		{
			SPovtoreniem(pole, x, y);
			Sleep(TIME);
			system("cls");
			PokazPolya(pole, x, y);
		}
		else
		{
			BezPovtorenya(pole, x, y);
			Sleep(TIME);
			system("cls");
			PokazPolya(pole, x, y);
		}
	} while (flag != MAX);
	//Освобождение поля
	free(pole);
}
