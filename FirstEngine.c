#include <stdio.h>
#include <stdlib.h>
#include "EngineOfLife.h"

void SPovtoreniem(char* pole, int x, int y)
{
	//Создание доп поля
	char* dop = (char*)malloc(y * x * sizeof(char));
	for (int c = 0; c < y; c++)
	{
		for (int d = 0; d < x; d++)
		{
			dop[x * c + d] = pole[x * c + d];
		}
	}
	//Переделка поля на новое
	char k;
	for (int a = 0; a < y; a++)
	{
		for (int b = 0; b < x; b++)
		{
			if (a != 0 && b != 0 && a != y-1 && b != x-1)
			{
				k = 0;
				for (int c = 0; c < 3; c++)
				{
					for (int d = 0; d < 3; d++)
						if (dop[x * (a + 1) + (b + 1) - (c * x + d)] == 2) k += 1;
				}
				if (dop[x * a + b] == 2) k -= 1;
			}
			else
			{

				//Граничные
				if (a == 0 && b == 0)
				{
					//printf("1");
					k = 0;
					if (dop[1] == 2) k += 1;
					if (dop[x] == 2) k += 1;
					if (dop[x + 1] == 2) k += 1;
					//Периодичность
					if (dop[2 * x - 1] == 2) k += 1;
					if (dop[x - 1] == 2) k += 1;
					if (dop[y * x - 1] == 2) k += 1;
					if (dop[(y - 1) * x] == 2) k += 1;
					if (dop[(y - 1) * x + 1] == 2) k += 1;
				}
				if (a == 0 && b == x-1)
				{
					//printf("1");
					k = 0;
					if (dop[x - 2] == 2) k += 1;
					if (dop[2 * x - 1] == 2) k += 1;
					if (dop[2 * x - 2] == 2) k += 1;
					//Периодичность
					if (dop[0] == 2) k += 1;
					if (dop[x] == 2) k += 1;
					if (dop[(y - 1) * x] == 2) k += 1;
					if (dop[y * x - 1] == 2) k += 1;
					if (dop[y * x - 2] == 2) k += 1;
				}
				if (a == y-1 && b == 0)
				{
					//printf("1");
					k = 0;
					if (dop[(y - 2) * x] == 2) k += 1;
					if (dop[(y - 2) * x + 1] == 2) k += 1;
					if (dop[(y - 1) * x + 1] == 2) k += 1;
					//Периодичность
					if (dop[(y - 1) * x - 1] == 2) k += 1;
					if (dop[y * x - 1] == 2) k += 1;
					if (dop[x - 1] == 2) k += 1;
					if (dop[0] == 2) k += 1;
					if (dop[1] == 2) k += 1;
				}
				if (a == y-1 && b == x-1)
				{
					//printf("1");
					k = 0;
					if (dop[y * x - 2] == 2) k += 1;
					if (dop[(y - 1) * x - 1] == 2) k += 1;
					if (dop[(y - 1) * x - 2] == 2) k += 1;
					//Периодичность
					if (dop[(y - 2) * x] == 2) k += 1;
					if (dop[(y - 1) * x] == 2) k += 1;
					if (dop[0] == 2) k += 1;
					if (dop[x - 1] == 2) k += 1;
					if (dop[x - 2] == 2) k += 1;
				}
				//Безграничные
				if (a == 0 && b != 0 && b != x-1)
				{
					//printf("1");
					k = 0;
					if (dop[a * x + b - 1] == 2) k += 1;
					if (dop[a * x + b + 1] == 2) k += 1;
					if (dop[a * x + b + x - 1] == 2) k += 1;
					if (dop[a * x + b + x] == 2) k += 1;
					if (dop[a * x + b + x + 1] == 2) k += 1;
					//Периодичность
					if (dop[(y - 1) * x + b - 1] == 2) k += 1;
					if (dop[(y - 1) * x + b] == 2) k += 1;
					if (dop[(y - 1) * x + b + 1] == 2) k += 1;
				}
				if (a == y-1 && b != 0 && b != x-1)
				{
					//printf("1");
					k = 0;
					if (dop[a * x + b - 1] == 2) k += 1;
					if (dop[a * x + b + 1] == 2) k += 1;
					if (dop[a * x + b - x - 1] == 2) k += 1;
					if (dop[a * x + b - x] == 2) k += 1;
					if (dop[a * x + b - x + 1] == 2) k += 1;
					//Периодичность
					if (dop[b - 1] == 2) k += 1;
					if (dop[b] == 2) k += 1;
					if (dop[b + 1] == 2) k += 1;
				}
				if (b == 0 && a != 0 && a != y-1)
				{
					//printf("1");
					k = 0;
					if (dop[a * x + b - x] == 2) k += 1;
					if (dop[a * x + b - x + 1] == 2) k += 1;
					if (dop[a * x + b + 1] == 2) k += 1;
					if (dop[a * x + b + x] == 2) k += 1;
					if (dop[a * x + b + x + 1] == 2) k += 1;
					//Периодичность
					if (dop[a * x - 1] == 2) k += 1;
					if (dop[a * x - 1 + x] == 2) k += 1;
					if (dop[a * x - 1 + 2 * x] == 2) k += 1;
				}
				if (b == x-1 && a != 0 && a != y-1)
				{
					//printf("1");
					k = 0;
					if (dop[a * x + b - x - 1] == 2) k += 1;
					if (dop[a * x + b - x] == 2) k += 1;
					if (dop[a * x + b - 1] == 2) k += 1;
					if (dop[a * x + b + x - 1] == 2) k += 1;
					if (dop[a * x + b + x] == 2) k += 1;
					//Периодичность
					if (dop[a * x + x] == 2) k += 1;
					if (dop[a * x] == 2) k += 1;
					if (dop[a * x - x] == 2) k += 1;
					//if (a == 10 && b == 11)
					//	printf("%d %d %d", a* x + 1, a* x + 1 - x, a* x + 1 - 2 * x);
				}
			}
			//if (a == 10 && b == 11)
			//	printf("%d", k);
			if (k == 3 && dop[a * x + b] == 1)
				pole[a * x + b] = 2;
			else if (k != 2 && k != 3 && dop[a * x + b] == 2)
				pole[a * x + b] = 1;
		}
	}
	free(dop);
}
void BezPovtorenya(char* pole, int x, int y)
{
	//Создание доп поля
	char* dop = (char*)malloc(y * x * sizeof(char));
	for (int c = 0; c < y; c++)
	{
		for (int d = 0; d < x; d++)
		{
			dop[x * c + d] = pole[x * c + d];
		}
	}
	//Переделка поля на новое
	char k;
	for (int a = 0; a < y; a++)
	{
		for (int b = 0; b < x; b++)
		{
			if (a != 0 && b != 0 && a != y-1 && b != x-1)
			{
				k = 0;
				for (int c = 0; c < 3; c++)
				{
					for (int d = 0; d < 3; d++)
						if (dop[x * (a + 1) + (b + 1) - (c * x + d)] == 2) k += 1;
				}
				if (dop[x * a + b] == 2) k -= 1;
			}
			else
			{
				//Граничные
				if (a == 0 && b == 0)
				{
					k = 0;
					if (dop[1] == 2) k += 1;
					if (dop[x] == 2) k += 1;
					if (dop[x + 1] == 2) k += 1;
				}
				if (a == 0 && b == x-1)
				{
					k = 0;
					if (dop[x - 2] == 2) k += 1;
					if (dop[2 * x - 1] == 2) k += 1;
					if (dop[2 * x - 2] == 2) k += 1;
				}
				if (a == y-1 && b == 0)
				{
					k = 0;
					if (dop[(y - 2) * x] == 2) k += 1;
					if (dop[(y - 2) * x + 1] == 2) k += 1;
					if (dop[(y - 1) * x + 1] == 2) k += 1;
				}
				if (a == y-1 && b == x-1)
				{
					k = 0;
					if (dop[y * x - 2] == 2) k += 1;
					if (dop[(y - 1) * x - 1] == 2) k += 1;
					if (dop[(y - 1) * x - 2] == 2) k += 1;
				}
				//Безграничные
				if (a == 0 && b != 0 && b != x-1)
				{
					k = 0;
					if (dop[a * x + b - 1] == 2) k += 1;
					if (dop[a * x + b + 1] == 2) k += 1;
					if (dop[a * x + b + x - 1] == 2) k += 1;
					if (dop[a * x + b + x] == 2) k += 1;
					if (dop[a * x + b + x + 1] == 2) k += 1;
				}
				if (a == y-1 && b != 0 && b != x-1)
				{
					k = 0;
					if (dop[a * x + b - 1] == 2) k += 1;
					if (dop[a * x + b + 1] == 2) k += 1;
					if (dop[a * x + b - x - 1] == 2) k += 1;
					if (dop[a * x + b - x] == 2) k += 1;
					if (dop[a * x + b - x + 1] == 2) k += 1;
				}
				if (b == 0 && a != 0 && a != y-1)
				{
					k = 0;
					if (dop[a * x + b - x] == 2) k += 1;
					if (dop[a * x + b - x + 1] == 2) k += 1;
					if (dop[a * x + b + 1] == 2) k += 1;
					if (dop[a * x + b + x] == 2) k += 1;
					if (dop[a * x + b + x + 1] == 2) k += 1;
				}
				if (b == x-1 && a != 0 && a != y-1)
				{
					k = 0;
					if (dop[a * x + b - x - 1] == 2) k += 1;
					if (dop[a * x + b - x] == 2) k += 1;
					if (dop[a * x + b - 1] == 2) k += 1;
					if (dop[a * x + b + x - 1] == 2) k += 1;
					if (dop[a * x + b + x] == 2) k += 1;
				}
			}
			if (k == 3 && dop[a * x + b] == 1)
				pole[a * x + b] = 2;
			else if (k != 2 && k != 3 && dop[a * x + b] == 2)
				pole[a * x + b] = 1;
		}
	}
	free(dop);
}
