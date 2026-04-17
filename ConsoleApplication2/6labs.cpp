#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");
    
    FILE* fin = fopen("input.txt", "r");
    FILE* fout = fopen("output.txt", "w");

    if (!fin) {
        perror("Ошибка: input.txt не  удалось открыть.");
        return 1;
    }
    if (!fout) {
        perror("Ошибка: output.txt не удалось открыть.\n");
        fclose(fin);
        return 1;
    }

    char line[256];
    int count = 0;

    
    while (fgets(line, sizeof(line), fin)) {

        line[strcspn(line, "\r\n")] = '\0';

        if (strlen(line) == 0) continue;

        char* last_space = strrchr(line, ' ');
        if (!last_space) {
            continue;
        }

        int year = atoi(last_space + 1);

        if (year > 1980) {
            fprintf(fout, "%s\n", line);
            count++;
        }
    }

    fclose(fin);
    fclose(fout);

    printf("Обработка завершена. В output.txt записано %d строк.\n", count);
    return 0;
}