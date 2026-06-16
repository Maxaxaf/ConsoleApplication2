#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#include <math.h>

int main(void) {
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	int count = 1;
	char buffer[200];
	char cals[200];
	int day[10][10];
	char month[10][100];
	int month_num[10][10];
	int sum = 0;


	printf("Открытие фаила \n");
	const char* filename = "data.txt";
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("aОшибка, фаил не был найден.");
		return 1;
	}
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		printf("%d: %s \n", count, buffer);
		count++;
	}
	rewind(fp);
	int col = 0;
	while (fgets(buffer,sizeof(buffer), fp) != NULL) {
		if (sscanf(buffer, "%d %99s", &day[0][col], month[col]) == 2){
		printf("Days: %d \n", day[0][col]);
		col++;
		}
	}
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < col; j++) {
			sum += day[i][j];
		}
	}
	printf("Result sum: %d \n", sum);
	for (int i = 0; i < col; i++) {
		printf("Month: %s \n", month[i]);
		if (strcmp(month[i], "январь") == 0) {
			month_num[0][i] =  0;
		}
		if (strcmp(month[i], "февраль") == 0) {
			month_num[0][i] = 30;
		}
		if (strcmp(month[i], "март") == 0) {
			month_num[0][i] = 61;
		}
		if (strcmp(month[i], "апрель") == 0) {
			month_num[0][i] = 91;
		}
		if (strcmp(month[i], "май") == 0) {
			month_num[0][i] = 122;
		}
		if (strcmp(month[i], "июнь") == 0) {
			month_num[0][i] = 152;
		}
		if (strcmp(month[i], "июль") == 0) {
			month_num[0][i] = 183;
		}
		if (strcmp(month[i], "авгусь") == 0) {
			month_num[0][i] = 213;
		}
		if (strcmp(month[i], "сентябрь") == 0) {
			month_num[0][i] = 244;
		}
		if (strcmp(month[i], "октябрь") == 0) {
			month_num[0][i] = 274;
		}
		if (strcmp(month[i], "ноябрь") == 0) {
			month_num[0][i] = 305;
		}
		if (strcmp(month[i], "декабрь") == 0) {
			month_num[0][i] = 335;
		}
	}
	if (month_num[0][0] < month_num[0][1]) {
		int result = abs((day[0][0] + month_num[0][0]) - (day[0][1] + month_num[0][1]));
		printf("FINAL RESULT: %d", result);
	}
	else {
		int result = 365 - ((day[0][0] + month_num[0][0]) - (day[0][1] + month_num[0][1]));
		printf("FINAL RESULT: %d", result);
	}
	return 0;
}