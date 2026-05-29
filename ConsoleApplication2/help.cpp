#include <stdio.h>
#include <stdlib.h>

int main() {
    int val;
    printf("\n Введите число, до которого вы собираетесь найти простые:  \n ");

    if (scanf("%i", &val) != 1 || val < 2) {
        printf("Натуральные значения не могут быть равны единицы или меньше 0");
        return 1;
    }

    int* arr = malloc((val + 1) * sizeof(int));

    if (!arr) return 1;

    for (int k = 2; k <= val; k++) {
        arr[k] = k;
    }

    int m = 2;

    while (m * m <= val) {
        for (int x = m * m; x <= val; x += m) {
            arr[x] = 0;
        }

        int next_v = 0;
        for (int k = m + 1; k <= val; k++) {
            if (arr[k] != 0) {
                next_v = arr[k];
                break;
            }
        }

        if (next_v == 0) break;
        m = next_v;
    }

    int total = 0;
    for (int k = 2; k <= val; k++) {
        if (arr[k] != 0) {
            arr[total++] = arr[k];
        }
    }

    printf("Простые числа до %d: ", val);
    for (int k = 0; k < total; k++) {
        printf("%d ", arr[k]);
    }
    printf("\n");

    free(arr);
    return 0;
}
