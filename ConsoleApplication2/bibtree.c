#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

typedef struct BookNode {
    char* author;
    char* title;
    char* publisher;
    int   year;
    struct BookNode* left;
    struct BookNode* right;
} BOOK;

char* trim(char* s) {
    while (isspace((unsigned char)*s))
        s++;
    if (*s != '\0') {
        char* end = s + strlen(s) - 1;
        while (end > s && isspace((unsigned char)*end))
            end--;
        end[1] = '\0';
    }
    return s;
}

char* get_field(char* block, const char* key) {
    char* p = strstr(block, key);
    if (!p) return NULL;

    p = strchr(p, '=');
    if (!p) return NULL;

    p++;
    while (isspace((unsigned char)*p))
        p++;

    if (*p != '{') return NULL;
    p++;

    char* start = p;
    int depth = 1;
    while (*p && depth > 0) {
        if (*p == '{') depth++;
        else if (*p == '}') depth--;
        p++;
    }

    int len = (p - start) - 1;
    char* result = malloc(len + 1);
    if (!result) return NULL;
    memcpy(result, start, len);
    result[len] = '\0';

    return trim(result);
}

BOOK* create_node(char* author, char* title, char* publisher, int year) {
    BOOK* node = malloc(sizeof(BOOK));
    if (!node) return NULL;
    node->author = _strdup(author ? author : "Unknown");
    node->title = _strdup(title ? title : "Unknown");
    node->publisher = _strdup(publisher ? publisher : "N/A");
    node->year = year;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BOOK* insert(BOOK* root, char* author, char* title, char* publisher, int year) {
    if (!root)
        return create_node(author, title, publisher, year);

    int cmp = strcoll(author, root->author);
    if (cmp == 0)
        cmp = strcoll(title, root->title);

    if (cmp < 0)
        root->left = insert(root->left, author, title, publisher, year);
    else if (cmp > 0)
        root->right = insert(root->right, author, title, publisher, year);
    else
        root->year = year;

    return root;
}

void print_sorted(BOOK* root, FILE* out) {
    if (!root) return;
    print_sorted(root->left, out);
    fprintf(out, "Author: %s | Title: %s | Publisher: %s | Year: %d\n",
        root->author, root->title, root->publisher, root->year);
    print_sorted(root->right, out);
}

void free_tree(BOOK* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root->author);
    free(root->title);
    free(root->publisher);
    free(root);
}

void parse_bib(const char* filename, BOOK** root) {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    FILE* f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Не найден: %s\n", filename);
        return;
    }

    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    rewind(f);

    if (len == 0) { fclose(f); return; }

    char* buf = malloc(len + 1);
    if (!buf) { fclose(f); return; }
    fread(buf, 1, len, f);
    buf[len] = '\0';
    fclose(f);

    char* p = buf;
    while (1) {
        char* entry = strstr(p, "@");
        if (!entry) break;

        char* brace = strchr(entry, '{');
        if (!brace) break;

        char* end = brace + 1;
        int depth = 1;
        while (*end && depth > 0) {
            if (*end == '{') depth++;
            else if (*end == '}') depth--;
            if (depth > 0) end++;
        }
        if (*end == '\0') break;

        char temp = *end;
        *end = '\0';

        char* author = get_field(brace, "author");
        char* title = get_field(brace, "title");
        char* publisher = get_field(brace, "publisher");
        char* ystr = get_field(brace, "year");
        int   year = ystr ? atoi(ystr) : 0;

        if (author && title)
            *root = insert(*root, author, title, publisher, year);

        free(author); free(title); free(publisher); free(ystr);

        *end = temp;
        p = end + 1;
    }

    free(buf);
}

int main(int argc, char* argv[]) {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    char exe_dir[512] = "";
    strncpy(exe_dir, argv[0], sizeof(exe_dir) - 1);
    char* slash = strrchr(exe_dir, '\\');
    if (!slash) slash = strrchr(exe_dir, '/');
    if (slash) *(slash + 1) = '\0';
    else       exe_dir[0] = '\0';

    char files_folder[512];
    snprintf(files_folder, sizeof(files_folder), "%sfiles\\", exe_dir);
    printf("Ищу .bib файлы в: %s\n", files_folder);

    char cmd[600];
    snprintf(cmd, sizeof(cmd), "dir /b \"%s*.bib\" 2>nul", files_folder);

    FILE* dir = _popen(cmd, "r");
    if (!dir) {
        fprintf(stderr, "Ошибка: не удалось открыть папку files\\\n");
        return 1;
    }

    BOOK* root = NULL;
    int file_count = 0;
    char fname[256];

    while (fgets(fname, sizeof(fname), dir)) {
        fname[strcspn(fname, "\r\n")] = '\0';
        char fullpath[512];
        snprintf(fullpath, sizeof(fullpath), "%s%s", files_folder, fname);
        printf("  Читаю: %s\n", fname);
        parse_bib(fullpath, &root);
        file_count++;
    }
    _pclose(dir);

    if (file_count == 0) {
        fprintf(stderr, "Ошибка: папка files\\ пуста или не найдена.\n");
        fprintf(stderr, "Создай папку 'files' рядом с .exe и положи туда .bib файлы.\n");
        return 1;
    }

    if (!root) {
        fprintf(stderr, "Ошибка: записи не найдены. Проверь .bib файлы.\n");
        return 1;
    }

    char outpath[512];
    snprintf(outpath, sizeof(outpath), "%ssorted_bib.txt", exe_dir);

    FILE* out = fopen(outpath, "w");
    if (!out) {
        perror("Ошибка создания файла");
        return 1;
    }

    print_sorted(root, out);
    fclose(out);
    free_tree(root);

    printf("Готово! Результат сохранён в: %s\n", outpath);
    return 0;
}