#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    printf("matrix size (n x n): ");
    scanf("%d", &n);

    double** matr = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matr[i] = (double*)malloc(n * sizeof(double));
    }

    printf("matrix elements %d x %d:\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &matr[i][j]);
        }
    }

    printf("\nmatrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2lf ", matr[i][j]);
        }
        printf("\n");
    }

    double main_diag_sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                main_diag_sum += matr[i][j];
            }
        }
    }
    printf("\nmain diagonal: %.2lf\n", main_diag_sum);

    double sec_diag_sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i + j == n - 1) {
                sec_diag_sum += matr[i][j];
            }
        }
    }
    printf("secondary diagonal: %.2lf\n", sec_diag_sum);

    double matr_2[2][2];

    printf("\nmatrix 2x2:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%lf", &matr_2[i][j]);
        }
    }

    double result[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                result[i][j] += matr_2[i][k] * matr_2[k][j];
            }
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            matr_2[i][j] = result[i][j];
        }
    }

    printf("\nmatrix 2/2:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%.2lf ", matr_2[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(matr[i]);
    }
    free(matr);

    return 0;
}
