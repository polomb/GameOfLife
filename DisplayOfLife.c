#include <stdio.h>
#include <stdlib.h>
#include "EngineOfLife.h"

void PokazPolya(char* pole, int x, int y)
{
	//Показ поля
	for (int a = 0; a < y; a++)
	{
		for (int b = 0; b < x; b++)
			printf("|%c", pole[a * x + b]);
		printf("|\n");
	}
}
