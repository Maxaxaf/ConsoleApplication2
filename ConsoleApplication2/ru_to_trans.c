#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

const char* translate_char(unsigned char c) {
    switch (c) {
        case 192: return "A";  case 224: return "a";
        case 193: return "B";  case 225: return "b";
        case 194: return "V";  case 226: return "v";
        case 195: return "G";  case 227: return "g";
        case 196: return "D";  case 228: return "d";
        case 197: return "E";  case 229: return "e";
        case 168: return "Yo"; case 184: return "yo";
        case 198: return "Zh"; case 230: return "zh";
        case 199: return "Z";  case 231: return "z";
        case 200: return "I";  case 232: return "i";
        case 201: return "J";  case 233: return "j";
        case 202: return "K";  case 234: return "k";
        case 203: return "L";  case 235: return "l";
        case 204: return "M";  case 236: return "m";
        case 205: return "N";  case 237: return "n";
        case 206: return "O";  case 238: return "o";
        case 207: return "P";  case 239: return "p";
        case 208: return "R";  case 240: return "r";
        case 209: return "S";  case 241: return "s";
        case 210: return "T";  case 242: return "t";
        case 211: return "U";  case 243: return "u";
        case 212: return "F";  case 244: return "f";
        case 213: return "Kh"; case 245: return "kh";
        case 214: return "Ts"; case 246: return "ts";
        case 215: return "Ch"; case 247: return "ch";
        case 216: return "Sh"; case 248: return "sh";
        case 217: return "Shch"; case 249: return "shch";
        case 218: return "\""; case 250: return "\"";
        case 219: return "Y";  case 251: return "y";
        case 220: return "'";  case 252: return "'";
        case 221: return "E";  case 253: return "e";
        case 222: return "Yu"; case 254: return "yu";
        case 223: return "Ya"; case 255: return "ya";
        default: return NULL;
    }
}

int is_alpha_cp1251(unsigned char c) {
    if ((c >= 192 && c <= 255) || c == 168 || c == 184) return 1;
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) return 1;
    return 0;
}

void process_file(const char* in_path) {
    FILE* in = fopen(in_path, "r");
    if (!in) return;

    char out_path[260];
    strncpy(out_path, in_path, 250);
    out_path[250] = '\0';
    
    char* dot = strrchr(out_path, '.');
    if (dot) {
        strcpy(dot, "_trans.txt");
    } else {
        strcat(out_path, "_trans.txt");
    }

    FILE* out = fopen(out_path, "w");
    if (!out) {
        fclose(in);
        return;
    }

    int ch;
    while ((ch = fgetc(in)) != EOF) {
        unsigned char uc = (unsigned char)ch;
        if (is_alpha_cp1251(uc)) {
            const char* trans = translate_char(uc);
            if (trans) {
                fputs(trans, out);
            } else {
                fputc(uc, out);
            }
        } else {
            fputc(uc, out);
        }
    }

    fclose(in);
    fclose(out);
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    if (argc < 2) return 1;

    for (int i = 1; i < argc && i <= 1000; i++) {
        process_file(argv[i]);
    }

    return 0;
}
