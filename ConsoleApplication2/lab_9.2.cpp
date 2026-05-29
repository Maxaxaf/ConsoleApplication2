#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <windows.h>

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    char calc[100];
    char op[100];
    double CalcNum[100];
    char* token;
    char* token_2;
    printf("Test\n");
    printf("Проверка русского языка\n\n");
    printf("Счмтываем строку calc_element функцией scanf\n");
    
    int i = 1; int CalcId = 0; int numb_c = 0; int two_c = 0;
    scanf("%100[^\n]", calc);
    printf("String of input: %s \n", calc);
    token = strtok(calc, "+-");
    token_2 = strtok(calc, "0123456789");
    printf("Token%d: %s\n", i, token);
    int opid = 0, numid = 0;
    CalcNum[numid] = strtod(token, NULL);
    // Первый токен это первое число
 
    //CalcNum[numid] = strtod(token, NULL);
    //printf("#Number%d: %f \n", numid, CalcNum[numid]);
    //numid++;
     
    //op[opid]=*token;
    //printf("Operator%d: %c\n",opid,op[opid]);
    // Алгоритм преобразования строки под обрабатываемый формат (цифры - пробелы - операнды)
    // Входящая строка может быть как с пробелами так и без, но без повторяющихся знаков
    // Т.е. допустимо +45б4 + 5 + 5.66-4--6   ### Но не допустимо +++66---5.4++-4.3+56,+5
    // в начале строки до первой цивры все знаки удаляются, кроме первого перед цифрой если он "-"
    // далее если символ "цифра или точка или запятая" остается, если знак " + или - " то устанавливаются пробелы с обоих сторон
    // последующие знаки до "цифра или точка или запятая" удаляются
    while (token != NULL) {
        i++;
        token = strtok(NULL, "+-");
        CalcNum[numb_c] = *token;
        printf("Tokeen%d: %s\n", i, token);
        numb_c++;
    }
    while (token_2 != NULL) {
        token_2 = strtok(NULL, "0123456789");
        op[two_c] = *token_2;
    }

    for (int i = 0; i < 5; i++) {
        double result = CalcNum[i];
        printf("lf", result);
    }
    //std::cout << "Hello World!\n";
}