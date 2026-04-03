#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <windows.h>
int main()
{
	SetConsoleOutputCP(65001);  // UTF-8
	SetConsoleCP(65001);        // UTF-8
	setlocale(LC_ALL, "ru-RU.UTF-8");
	double matrix[3][3];
	double sum_main_d = 0, sum_second_d = 0;

	printf("Введите элементы матрицы 3на3 \n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			scanf("%lf", &matrix[i][j]);
		}
	}

	printf("Матрица 3x3:\n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%8.2lf ", matrix[i][j]);
		}
		printf("\n");
	}

}