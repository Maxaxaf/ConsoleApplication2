#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <direct.h> 

#define MAX_WORDS 100000
#define MAX_FILES 256
#define MAX_LINE_LEN 4096

typedef struct word {
    int count;
    char* w;
} WORD;

WORD* words[MAX_WORDS];
int word_count = 0;

int clean_and_validate(char* str) {
    if (!isalpha((unsigned char)str[0])) {
        return 0;
    }

    int i = 0;
    while (str[i] != '\0') {
        if (!isalnum((unsigned char)str[i])) {
            str[i] = '\0';
            break;
        }
        str[i] = (char)tolower((unsigned char)str[i]);
        i++;
    }
    return (strlen(str) > 0);
}

void add_word(const char* str) {
    for (int i = 0; i < word_count; i++) {
        if (strcmp(words[i]->w, str) == 0) {
            words[i]->count++;
            return;
        }
    }

    if (word_count >= MAX_WORDS) return;

    words[word_count] = (WORD*)malloc(sizeof(WORD));
    if (!words[word_count]) return;

    words[word_count]->w = (char*)malloc((strlen(str) + 1) * sizeof(char));
    if (!words[word_count]->w) {
        free(words[word_count]);
        return;
    }

    strcpy(words[word_count]->w, str);
    words[word_count]->count = 1;
    word_count++;
}

int compare_alphabet(const void* a, const void* b) {
    WORD* wordA = *(WORD**)a;
    WORD* wordB = *(WORD**)b;
    return strcmp(wordA->w, wordB->w);
}

int compare_frequency(const void* a, const void* b) {
    WORD* wordA = *(WORD**)a;
    WORD* wordB = *(WORD**)b;
    if (wordB->count != wordA->count) {
        return wordB->count - wordA->count;
    }
    return strcmp(wordA->w, wordB->w);
}

void process_file(const char* filepath) {
    FILE* f = fopen(filepath, "r");
    if (!f) {
        printf("Файл %s не найден.\n", filepath);
        return;
    }

    char line[MAX_LINE_LEN];
    const char* delimiters = " \t\n\r,.!?;:\"()[]{}<>-";

    while (fgets(line, sizeof(line), f)) {
        char* token = strtok(line, delimiters);
        while (token != NULL) {
            if (clean_and_validate(token)) {
                add_word(token);
            }
            token = strtok(NULL, delimiters);
        }
    }
    fclose(f);
}

void free_memory() {
    for (int i = 0; i < word_count; i++) {
        free(words[i]->w);
        free(words[i]);
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "en_US.UTF-8");

    char cwd[1024];
    if (_getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Программа ищет файлы здесь: %s\\texts\\\n", cwd);
    }

    if (argc < 2) {
        printf("Инструкция: запустите программу через командную строку, передав имена файлов.\n");
        printf("Пример: program.exe test1.txt test2.txt\n");
        return 1;
    }

    int files_to_process = (argc - 1 > MAX_FILES) ? MAX_FILES : argc - 1;

    for (int i = 1; i <= files_to_process; i++) {
        char path[512];
        sprintf(path, "texts/%s", argv[i]);
        printf("Обработка: %s...\n", path);
        process_file(path);
    }

    qsort(words, word_count, sizeof(WORD*), compare_alphabet);
    FILE* out_alpha = fopen("result_alphabet.txt", "w");
    if (out_alpha) {
        for (int i = 0; i < word_count; i++) {
            fprintf(out_alpha, "%s : %d\n", words[i]->w, words[i]->count);
        }
        fclose(out_alpha);
        printf("Создан файл: 'result_alphabet.txt'\n");
    }

    qsort(words, word_count, sizeof(WORD*), compare_frequency);
    FILE* out_freq = fopen("result_frequency.txt", "w");
    if (out_freq) {
        for (int i = 0; i < word_count; i++) {
            fprintf(out_freq, "%d : %s\n", words[i]->count, words[i]->w);
        }
        fclose(out_freq);
        printf("Создан файл: 'result_frequency.txt'\n");
    }

    free_memory();
    return 0;
}
