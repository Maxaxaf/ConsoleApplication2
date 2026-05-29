#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Оптимизация ввода-вывода
    if (freopen(NULL, "r", stdin));

    int n;
    long long l;
    if (scanf("%d %lld", &n, &l) != 2) return 0;

    // Выделяем память под массивы
    int* a = (int*)malloc((n - 1) * sizeof(int));
    long long* b = (long long*)malloc((n - 1) * sizeof(long long));
    long long* max_path = (long long*)calloc(n, sizeof(long long));

    if (!a || !b || !max_path) return 1;

    for (int i = 0; i < n - 1; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        scanf("%lld", &b[i]);
    }

    long long total_worms = 0;

    // Идем снизу вверх (от N-1 до 1)
    for (int i = n - 2; i >= 0; i--) {
        int child = i + 1;
        int parent = a[i];
        long long edge = b[i];

        // Длина пути, пришедшая из ребенка + длина текущего ребра
        long long current_path = max_path[child] + edge;

        // Считаем червяков, поместившихся на этом участке
        total_worms += current_path / l;
        long long rem = current_path % l;

        // В родителе сохраняем максимальный остаток среди всех его детей
        if (rem > max_path[parent]) {
            max_path[parent] = rem;
        }
    }

    printf("%lld\n", total_worms);

    // Освобождаем память
    free(a);
    free(b);
    free(max_path);

    return 0;
}
