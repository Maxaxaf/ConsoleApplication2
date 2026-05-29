#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

typedef struct {
    const char* trans;
    unsigned char ru_code;
} TransRule;

TransRule rules[] = {
    {"shch", 249}, {"Shch", 217}, {"SHCH", 217},
    {"sh", 248},   {"Sh", 216},   {"SH", 216},
    {"ch", 247},   {"Ch", 215},   {"CH", 215},
    {"zh", 230},   {"Zh", 218},   {"ZH", 218},
    {"kh", 245},   {"Kh", 213},   {"KH", 213},
    {"ts", 246},   {"Ts", 214},   {"TS", 214},
    {"yo", 184},   {"Yo", 168},   {"YO", 168},
    {"yu", 254},   {"Yu", 222},   {"YU", 222},
    {"ya", 255},   {"Ya", 223},   {"YA", 223},
    {"a", 224},    {"A", 192},
    {"b", 225},    {"B", 193},
    {"v", 226},    {"V", 194},
    {"g", 227},    {"G", 195},
    {"d", 228},    {"D", 196},
    {"e", 229},    {"E", 197},
    {"z", 231},    {"Z", 199},
    {"i", 232},    {"I", 200},
    {"j", 233},    {"J", 201},
    {"k", 234},    {"K", 202},
    {"l", 235},    {"L", 203},
    {"m", 236},    {"M", 204},
    {"n", 237},    {"N", 205},
    {"o", 238},    {"O", 206},
    {"p", 239},    {"P", 207},
    {"r", 240},    {"R", 208},
    {"s", 241},    {"S", 209},
    {"t", 242},    {"T", 210},
    {"u", 243},    {"U", 211},
    {"f", 244},    {"F", 212},
    {"y", 251},    {"Y", 219},
    {"\"", 250},   {"'", 252}
};
int num_rules = sizeof(rules) / sizeof(TransRule);

void process_file_back(const char* in_path) {
    FILE* in = fopen(in_path, "r");
    if (!in) return;

    char out_path[260];
    strncpy(out_path, in_path, 250);
    out_path[250] = '\0';

    char* pos = strstr(out_path, "_trans");
    if (pos) {
        strcpy(pos, "_rus.txt");
    }
    else {
        char* dot = strrchr(out_path, '.');
        if (dot) strcpy(dot, "_rus.txt");
        else strcat(out_path, "_rus.txt");
    }

    FILE* out = fopen(out_path, "w");
    if (!out) {
        fclose(in);
        return;
    }

    char lookahead[6] = { 0 };
    int l_len = 0;

    while (1) {
        int ch;
        while (l_len < 5 && (ch = fgetc(in)) != EOF) {
            lookahead[l_len++] = (char)ch;
        }

        if (l_len == 0) break;

        int matched = 0;
        for (int i = 0; i < num_rules; i++) {
            int len = strlen(rules[i].trans);
            if (l_len >= len && strncmp(lookahead, rules[i].trans, len) == 0) {
                fputc(rules[i].ru_code, out);
                memmove(lookahead, lookahead + len, l_len - len);
                l_len -= len;
                matched = 1;
                break;
            }
        }

        if (!matched) {
            fputc(lookahead[0], out);
            memmove(lookahead, lookahead + 1, l_len - 1);
            l_len--;
        }
    }

    fclose(in);
    fclose(out);
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    if (argc < 2) return 1;

    for (int i = 1; i < argc && i <= 1000; i++) {
        process_file_back(argv[i]);
    }
    return 0;
}
