#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#include <math.h>
#include <stdlib.h>

double* sum_m(double* matrix_1, double* matrix_2, int count) {
	double* sum_matrix = (double*)malloc(count * count * sizeof(double)); int k = 0;
	if (!sum_matrix) {
		exit(1);
	}
	for (int i = 0;i < count;i++) {
		for (int j = 0;j < count;j++) {
			sum_matrix[k] = matrix_1[i * count + j] + matrix_2[i * count + j];
			k++;
		}
	}
	return sum_matrix;
}

int main(void) {
	setlocale(LC_ALL, "en_US.UTF-8");
	const char* filename = "input.txt";
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("Файл не открылся.");
		return 1;
	}
	int count;
	printf("Введите размер матрицы: n x n\n");
	scanf("%d", &count);

	int two = 0; int k = 1;
	while (two != 2) {
		printf("Вывод матрицы под номером %d: \n", k);
		for (int i = 0; i < count; i++) {
			for (int j = 0; j < count; j++) {
				int number;
				scanf("%d", &number);
				fprintf(fp, "%d ", number);
			}
			fprintf(fp, "\n");
		}	
		fprintf(fp, "\n");
		two++;
		k++;
	}
	fclose(fp);
	fp = fopen(filename, "r");
	double* matrix_1 = (double*)malloc(count * count * sizeof(double));
	double* matrix_2 = (double*)malloc(count * count * sizeof(double));


	for (int i = 0; i < count * count; i++) {
		fscanf(fp, "%lf", &matrix_1[i]);
	}
	for (int i = 0; i < count * count; i++) {
		fscanf(fp, "%lf", &matrix_2[i]);
	}
	double* sum_result = sum_m(matrix_1, matrix_2, count);
	printf("\nРезультат сложения матриц:\n");
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			printf("%.1lf\t", sum_result[i * count + j]);
		}
		printf("\n"); // Перенос на новую строку экрана
	}
	return 0;
}


