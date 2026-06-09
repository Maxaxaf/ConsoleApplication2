#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    FILE* In, * Out;
    unsigned long long buffer = 0;
    int bit_count = 0;

    unsigned long long count_A = 0;
    unsigned long long count_C = 0;
    unsigned long long count_G = 0;
    unsigned long long count_T = 0;
    unsigned long long count_N = 0;

    if (argc < 2) {
        printf("Использование: %s <имя_входного_файла>\n", argv[0]);
        return 1;
    }

    In = fopen(argv[1], "r");
    if (In == NULL) {
        printf("Ошибка открытия входного файла %s\n", argv[1]);
        return 1;
    }

    Out = fopen("OUT.dat", "wb");
    if (Out == NULL) {
        printf("Ошибка создания выходного файла OUT.dat\n");
        fclose(In);
        return 1;
    }

    char header_buffer[256];
    if (fgets(header_buffer, sizeof(header_buffer), In) == NULL) {}
    if (fgets(header_buffer, sizeof(header_buffer), In) == NULL) {}

    int ch;
    while ((ch = fgetc(In)) != EOF) {
        unsigned long long triada = 0;
        int valid = 0;

        if (ch == 'A' || ch == 0101) {
            triada = 0b001;
            count_A++;
            valid = 1;
        }
        else if (ch == 'C' || ch == 0103) {
            triada = 0b010;
            count_C++;
            valid = 1;
        }
        else if (ch == 'G' || ch == 0107) {
            triada = 0b100;
            count_G++;
            valid = 1;
        }
        else if (ch == 'T' || ch == 0124) {
            triada = 0b111;
            count_T++;
            valid = 1;
        }
        else if (ch == 'N' || ch == 0116) {
            triada = 0b000;
            count_N++;
            valid = 1;
        }

        if (valid) {
            buffer |= (triada << bit_count);
            bit_count += 3;

            if (bit_count == 63) {
                fwrite(&buffer, sizeof(unsigned long long), 1, Out);
                buffer = 0;
                bit_count = 0;
            }
        }
    }

    if (bit_count > 0) {
        fwrite(&buffer, sizeof(unsigned long long), 1, Out);
    }

    fclose(In);
    fclose(Out);

    printf("Статистика азотистых оснований:\n");
    printf("A: %llu\n", count_A);
    printf("C: %llu\n", count_C);
    printf("G: %llu\n", count_G);
    printf("T: %llu\n", count_T);
    printf("N: %llu\n", count_N);

    return 0;
}
