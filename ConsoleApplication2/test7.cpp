#include <stdio.h>

struct human {
    char name[30];
    char surname[30];
    int age;
};

int main() {
    // Объявляем массив БЕЗ { 0 }
    struct human m_test[1] = { 0 };

    // Мы НИЧЕГО не вводили и не присваивали.
    // Давай посмотрим, что там лежит прямо сейчас.
    printf(": %s\n", m_test[0].name);
    printf(": %d\n", m_test[0].age);

    return 0;
}
