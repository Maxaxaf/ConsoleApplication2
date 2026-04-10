#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "lab_5.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");
    int n;
    char op;

    printf("Введите размер матрицы n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Ошибка: нужно ввести положительное число!\n");
        return 1;
    }

    while (getchar() != '\n');

    double* A = create_matrix(n);
    double* B = create_matrix(n);

    input_matrix(A, n, "1");
    input_matrix(B, n, "2");

    print_matrix(A, n, "Матрица 1");
    print_matrix(B, n, "Матрица 2");

    printf("\nВыберите операцию (+, -, *): ");
    scanf(" %c", &op);

    double* result = matrix_calc(A, B, n, op);

    if (result != NULL) {
        print_matrix(result, n, "Результат операции");
        free_matrix(result); 
    }

    free_matrix(A);
    free_matrix(B);

    return 0;
}