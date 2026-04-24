#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
int is_vowel(int c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

int is_consonant(int c) {
    if (!isalpha(c)) return 0;
    return !is_vowel(c);
}

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");
    char filename[256];
    FILE* file;
    int c;

    long total_chars = 0, lines = 0, digits = 0, punctuation = 0, spaces = 0;
    long letters = 0, lower = 0, upper = 0, vowels = 0, consonants = 0;

    printf("Введите имя файла: ");
    scanf("%255s", filename);

    file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка при открытии файла");
        return 1;
    }

    while ((c = fgetc(file)) != EOF) {
        total_chars++;

        if (c == '\n') lines++;
        if (isdigit(c)) digits++;
        if (ispunct(c)) punctuation++;
        if (isspace(c)) spaces++;

        if (isalpha(c)) {
            letters++;
            if (islower(c)) lower++;
            if (isupper(c)) upper++;

            if (is_vowel(c)) vowels++;
            else if (is_consonant(c)) consonants++;
        }
    }

    fclose(file);

    printf("\nРезультат %s\n", filename);
    printf("Общее количество символов: %ld\n", total_chars);
    printf("Количество строк:           %ld\n", lines);
    printf("Количество цифр:            %ld\n", digits);
    printf("Знаков препинания:          %ld\n", punctuation);
    printf("Пробельных символов:        %ld\n", spaces);
    printf("Всего букв:                 %ld\n", letters);
    printf("  - из них строчных:        %ld\n", lower);
    printf("  - из них прописных:       %ld\n", upper);
    printf("  - гласных:                %ld\n", vowels);
    printf("  - согласных:              %ld\n", consonants);

    return 0;
}