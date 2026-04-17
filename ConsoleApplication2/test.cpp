#include <stdio.h>

void sum(int x, int y)
{
    printf("%d + %d = %d \n", x, y, x + y);
}

int main(void)
{
    sum(1.4, 2.5);  // передаем значения double
    sum(1.4f, 2.5f);  // передаем значения float
}