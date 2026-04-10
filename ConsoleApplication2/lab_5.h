#ifndef LAB_5_H
#define LAB_5_H

// Создание матрицы в динамической памяти
double* create_matrix(int n);

// Ввод матрицы с консоли
void input_matrix(double* matrix, int n, const char* name);

// Вывод матрицы на консоль
void print_matrix(const double* matrix, int n, const char* name);

// Выполнение операции над матрицами (+, -, *)
double* matrix_calc(const double* a, const double* b, int n, char op);

// Освобождение памяти матрицы
void free_matrix(double* matrix);

#endif
