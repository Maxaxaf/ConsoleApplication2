#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <windows.h>

int main(void) {
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	int count = 1;
	char buffer[200];
	char cals[200];
	int day[10][10];
	char month[10][10];
	int sum = 0;


	printf("Открытие фаила \n");
	const char* filename = "data.txt";
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Ошибка, фаил не был найден.");
		return 1;
	}
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		printf("%d: %s \n", count, buffer);
		count++;
	}
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		fscanf(fp, "%d %99s", &day, month);
	}
	for (int i = 0; i < count; i++) {
		sum += day[i]; 
	}

	return 0;
}