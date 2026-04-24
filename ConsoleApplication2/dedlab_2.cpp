#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <direct.h> // Обязательно добавь этот include в самый верх

// Структура узла дерева
typedef struct node {
    int count;
    char* w;
    struct node* left;
    struct node* right;
} NODE;

// Функция создания нового узла
NODE* create_node(char* word) {
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    if (!new_node) return NULL;
    new_node->w = _strdup(word); // Выделяет память и копирует строку
    new_node->count = 1;
    new_node->left = new_node->right = NULL;
    return new_node;
}

// Добавление слова в дерево (алфавитная сортировка)
NODE* add_to_tree(NODE* root, char* word) {
    if (root == NULL) return create_node(word);

    int cmp = strcmp(word, root->w);
    if (cmp == 0) {
        root->count++; // Слово совпало
    }
    else if (cmp < 0) {
        root->left = add_to_tree(root->left, word);
    }
    else {
        root->right = add_to_tree(root->right, word);
    }
    return root;
}

// Сохранение дерева в файл (симметричный обход: Л-К-П)
void save_tree(NODE* root, FILE* out) {
    if (root != NULL) {
        save_tree(root->left, out);
        fprintf(out, "%-20s : %d\n", root->w, root->count);
        save_tree(root->right, out);
    }
}

// Функция для очистки памяти дерева в конце работы
void free_tree(NODE* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root->w);
        free(root);
    }
}

// Чтение файла и разбивка на слова
void process_file(const char* filename, NODE** root) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Файл %s не найден в папке files/\n", filename);
        return;
    }

    char word[256];
    int c, i = 0;

    while ((c = fgetc(f)) != EOF) {
        // Начинается с буквы (условие задачи)
        if (isalpha(c)) {
            word[i++] = (char)tolower(c);
            // Дальше могут быть буквы или цифры
            while ((c = fgetc(f)) != EOF && isalnum(c)) {
                if (i < 255) word[i++] = (char)tolower(c);
            }
            word[i] = '\0';
            *root = add_to_tree(*root, word);
            i = 0; // Сброс индекса для нового слова
        }
    }
    fclose(f);
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "en_US.UTF-8");
    char cwd[1024];
    if (_getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Программа ищет файлы здесь: %s\n", cwd);
    }

    if (argc < 2) {
        printf("Инструкция: запустите программу через командную строку, передав имена файлов.\n");
        printf("Пример: program.exe test1.txt test2.txt\n");
        return 1;
    }

    NODE* tree = NULL;

    for (int i = 1; i < argc; i++) {
        char path[512];
        // Формируем путь к файлу в папке "files"
        sprintf(path, "files/%s", argv[i]);
        printf("Обработка: %s...\n", path);
        process_file(path, &tree);
    }

    FILE* out = fopen("result_dictionary.txt", "w");
    if (out) {
        save_tree(tree, out);
        fclose(out);
        printf("\nГотово! Результат в файле 'result_dictionary.txt'\n");
    }
    else {
        printf("Не удалось создать файл результата.\n");
    }

    free_tree(tree); // Освобождаем память
    return 0;
}