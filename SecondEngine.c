#include <stdio.h>
#include <stdlib.h>
#include "EngineOfLife.h"

void ZapisFaila(char* pole, int x, int y, char FileNum)
{
	//Создание ссылки на файл
	FILE* ptr;
	errno_t err;
	//Файл открыт
	char a[17] = "./SaveFile_a.bin";
	a[11] = FileNum;
	err = fopen_s(&ptr, a, "w+");
	//Если не получилось
	if (err != NULL)
	{
		fputs("Error occurred while creating a file/writing in a file", stdout);
		exit(1);
	}
	//Макс
	int k = 0; int OneTwo;
	for (char a = 0; a < y; a++)
	{
		for (char b = 0; b < x; b++)
		{
			if (pole[a * x + b] == 2)
			{
				k += 1;
			}
		}
	}
	if (k <= (x * y)/2)
		OneTwo = 2;
	else
	{
		k = x * y - k;
		OneTwo = 1;
	}
	k = k * 2 + 4;
	//Что положить в файл
	int* dataInsert = (int*)malloc(k * sizeof(int));
	if (x <= 25)
		dataInsert[0] = x;
	else if (x > 25 && x <= 50)
		dataInsert[0] = x + 1000 - 25;
	else if (x > 50 && x <= 75)
		dataInsert[0] = x + 2000 - 50;
	else
		dataInsert[0] = x + 3000 - 75;
	if (y <= 25)
		dataInsert[1] = y;
	else if (y > 25 && y <= 50)
		dataInsert[1] = y + 1000 - 25;
	else if (y > 50 && y <= 75)
		dataInsert[1] = y + 2000 - 50;
	else
		dataInsert[1] = y + 3000 - 75;
	dataInsert[2] = k;
	dataInsert[3] = OneTwo;
	char ForOneTwo = OneTwo;
	int i = 4;
	for (int a = 0; a < y; a++)
	{
		for (int b = 0; b < x; b++)
		{
			if (pole[a * x + b] == ForOneTwo)
			{
				if (b <= 25)
					dataInsert[i] = b;
				else if (b > 25 && b <= 50)
					dataInsert[i] = b + 1000 - 25;
				else if (b > 50 && b <= 75)
					dataInsert[i] = b + 2000 - 50;
				else
					dataInsert[i] = b + 3000 - 75;
				i += 1;
				if (a <= 25)
					dataInsert[i] = a;
				else if (a > 25 && a <= 50)
					dataInsert[i] = a + 1000 - 25;
				else if (a > 50 && a <= 75)
					dataInsert[i] = a + 2000 - 50;
				else
					dataInsert[i] = a + 3000 - 75;
				i += 1;
			}
		}
	}
	//Кладётся информация в файл
	fwrite(dataInsert, sizeof(int), k, ptr);
	//Закрытие файла
	fclose(ptr);
	free(dataInsert);
}
char* ChtenieFaila(char* pole, int* x, int* y, char FileNum)
{
	int x1 = 0; int y1 = 0; int k; int OneTwo;
	//Создание ссылки на файл
	FILE* ptr;
	errno_t err;
	//Файл открыт
	char a[17] = "./SaveFile_a.bin";
	a[11] = FileNum;
	err = fopen_s(&ptr, a, "r");
	//Если не получилось
	if (err != NULL)
	{
		fputs("Error occurred while reading a file", stdout);
		exit(1);
	}
	//Сколько считать из файла
	fread(x, sizeof(int), 1, ptr);
	if (*x >= 1000 && *x < 2000)
		*x = *x - 1000 + 25;
	else if (*x >= 2000 && *x < 3000)
		*x = *x - 2000 + 50;
	else if (*x >= 3000 && *x < 4000)
		*x = *x - 3000 + 75;
	fread(y, sizeof(int), 1, ptr);
	if (*y >= 1000 && *y < 2000)
		*y = *y - 1000 + 25;
	else if (*y >= 2000 && *y < 3000)
		*y = *y - 2000 + 50;
	else if (*y >= 3000 && *y < 4000)
		*y = *y - 3000 + 75;
	fread(&k, sizeof(int), 1, ptr);
	fread(&OneTwo, sizeof(int), 1, ptr);
	printf("%d", OneTwo);
	int xx = *x; int yy = *y;
	pole = (char*)malloc(yy * xx * sizeof(char));
	char ForOneTwo = OneTwo;
	char zapolnenie;
	if (OneTwo == 1)
		zapolnenie = 2;
	else
		zapolnenie = 1;
	for (int c = 0; c < yy; c++)
	{
		for (int d = 0; d < xx; d++)
		{
			pole[xx * c + d] = zapolnenie;
		}
	}
	int* dataRead = (int*)malloc((k - 4) * sizeof(int));
	fread(dataRead, sizeof(int), (k - 4), ptr);
	for (int i = 0; i < k-4; i++)
	{
		if (dataRead[i] < 1000)
			x1 = dataRead[i];
		else if (dataRead[i] >= 1000 && dataRead[i] < 2000)
			x1 = dataRead[i] - 1000 + 25;
		else if (dataRead[i] >= 2000 && dataRead[i] < 3000)
			x1 = dataRead[i] - 2000 + 50;
		else if (dataRead[i] >= 3000 && dataRead[i] < 4000)
			x1 = dataRead[i] - 3000 + 75;
		i++;

		if (dataRead[i] < 1000)
			y1 = dataRead[i];
		else if (dataRead[i] >= 1000 && dataRead[i] < 2000)
			y1 = dataRead[i] - 1000 + 25;
		else if (dataRead[i] >= 2000 && dataRead[i] < 3000)
			y1 = dataRead[i] - 2000 + 50;
		else if (dataRead[i] >= 3000 && dataRead[i] < 4000)
			y1 = dataRead[i] - 3000 + 75;
		pole[xx * y1 + x1] = ForOneTwo;
	}
	fclose(ptr);
	free(dataRead);
	return pole;
}
