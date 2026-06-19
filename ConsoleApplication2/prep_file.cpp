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
	const char* filename = "data.txt";

	printf("Запись фаила: \n");
	int first; char second[20];
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("Ошибка, фаил не найден.");
		return 1;
	}
	for (int i=0;i<2;i++){
		printf("Введите дату: \n");
		scanf("%d", &first);

		printf("Введите месяц: \n");
		scanf("%s", second);

		fprintf(fp, "%d %s\n", first, second);
	}
	fclose(fp);
	printf("Открытие фаила \n");
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Ошибка, фаил не был найден.");
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

double* create_matrix(int n) {
	double* matrix = (double*)malloc(n * n * sizeof(double));
	if (!matrix) {
		exit(1);
	}
	return matrix;
}

double sum_matrix(double* a, int count) {
	double summa = 0.0;
	if (a == NULL) {
		return summa;
	}
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			summa += a[i * count + j];
		}
	}
	return summa;
}

double** hide(double** own, double* matrix, int con, int index) {
	own[index] = matrix;
	static double* good[2];

	for (int i = 0; i < index; i++) {
		for (int j = i + 1; j <= index; j++) {
			if (own[i] != NULL && own[j] != NULL) {

				double sum_i = sum_matrix(own[i], con);
				double sum_j = sum_matrix(own[j], con);
			
				if (sum_i == sum_j) {
					good[0] = own[i];
					good[1] = own[j];
					return good;
				}
			}
		}
	}
	return NULL;
}

int matrix(void) {
	int count;

	printf("Введите размер матриц n x n: \n");
	scanf("%d", &count);

	double* own_m[100] = { NULL }; int index = 0;

	double** result = NULL;

	while (result == NULL){
		double* my_matrix = create_matrix(count);

		printf("Введите элменеты матрицы.");
		int k = 0;
		for (int i = 0;i < count; i++) {
			for (int j = 0;j < count; j++) {
				k++;
				printf("Введите элемент массива №%d:", k);
				scanf("%lf", &my_matrix[i * count + j]);
			}
		}

		result = hide(own_m, my_matrix, count, index);
		index++;
	}
	printf("Найдены две матрицы с одинаковой суммой элементов.\n");

	printf("Первая матрица:\n");
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			printf("%.1lf\t", result[0][i * count + j]);
		}
		printf("\n");
	}

	printf("\nВторая матрица:\n");
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			printf("%.1lf\t", result[1][i * count + j]);
		}
		printf("\n");
	}

	for (int i = 0; i < index; i++) {
		free(own_m[i]);
	}

	return 0;
}

double* create_m(int count) {

	double* matrix = (double*)malloc(sizeof(double) * count * count);
	if (!matrix) {
		exit(1);
	}
	return matrix;
}
int write_matrix(void) {
	const char* filename = "input.txt";
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("Файл не открылся.");
		return 1;
	}
	int count;
	printf("Введите размер матрицы: n x n\n");
	scanf("%d", count);

	int two = 0; int k = 0;
	while (two != 2) {
		//double* matrix_1 = create_m(count); 
		printf("Вывод матрицы под номером %d", k);
		for (int i = 0; i < count; i++) {
			for (int j = 0; j < count; j++) {
				int number;
				//scanf("%lf", &matrix_1[i * count + j]);
				scanf("%d", &number);
				fprintf(fp, "%d ", number);
			}
		}	fprintf(fp, "\n");
		two++;
		k++;
		//free(matrix_1);
	}
}