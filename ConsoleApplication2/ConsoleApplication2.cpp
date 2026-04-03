// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Russian");
	double matr[3][3];
	printf("Matrix: \n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			scanf("%lf", &matr[i][j]);
		}
	}
	printf("Matrix \n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%.2lf ",matr[i][j]);
		}
        printf("\n");
	}
	double num_2 = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j ++) {
			if(i == j){
				num_2 += matr[i][j];
			}
		}
	}
	printf("Главная диагональ: ");
	printf("%2.lf ", num_2);

	double num_3 = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if ((i == 0 && j == 2) || (i == 2 && j == 0) || (i == 1 && j == 1))  {
				num_3 += matr[i][j];
			}
		}
	}
	printf("Побочная диагональ: ");
	printf("%2.lf ", num_3);


	double matr_2[2][2];
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			scanf("%lf", &matr_2[i][j]);
		}
	}
	double a = matr_2[0][0], b = matr_2[0][1];
	double c = matr_2[1][0], d = matr_2[1][1];

	matr_2[0][0] = a * a + b * c;
	matr_2[0][1] = a * b + b * d;
	matr_2[1][0] = c * a + d * c;
	matr_2[1][1] = c * b + d * d;
	printf("Квадрат матрицы 2 на 2: \n");
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			printf("%.2lf ", matr_2[i][j]);
		}
		printf("\n");
	}
	return 0;
}




