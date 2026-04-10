#define _CRT_SECURE_NO_WARNINGS
#include "lab_5.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
// Создание матрицы
double* create_matrix(int n) {
    setlocale(LC_ALL, "en_US.UTF-8");
    double* matrix = (double*)malloc(n * n * sizeof(double));
    if (!matrix) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    return matrix;
}

// Ввод матрицы
void input_matrix(double* matrix, int n, const char* name) {
    setlocale(LC_ALL, "en_US.UTF-8");
    printf("\nВвод матрицы %s (%dx%d):\n", name, n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            while (scanf("%lf", &matrix[i * n + j]) != 1) {
                printf("ОШИБКА! Введите число: ");
                while (getchar() != '\n'); 
            }
        }
    }
}

// Вывод матрицы
void print_matrix(const double* matrix, int n, const char* name) {
    setlocale(LC_ALL, "en_US.UTF-8");
    printf("\nВывод: %s\n", name);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.2lf ", matrix[i * n + j]);
        }
        printf("\n");
    }
}

// Выполнение операции
double* matrix_calc(const double* a, const double* b, int n, char op) {
    double* res = create_matrix(n);

    if (op == '+' || op == '-' || op == '*') {
        if (op == '+') {
            for (int i = 0; i < n * n; i++)
                res[i] = a[i] + b[i];
        }

        if (op == '-') {
            for (int i = 0; i < n * n; i++)
                res[i] = a[i] - b[i];
        }

        if (op == '*') {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    double sum = 0;
                    for (int k = 0; k < n; k++)
                        sum += a[i * n + k] * b[k * n + j];
                    res[i * n + j] = sum;
                }
        }
    }
    else {
        setlocale(LC_ALL, "en_US.UTF-8");
        printf("Ошибка: неверная операция '%c'!\n", op);
        free_matrix(res);
        return NULL;
    }

    return res;
}

// Освобождение памяти
void free_matrix(double* matrix) {
    if (matrix) free(matrix);
}