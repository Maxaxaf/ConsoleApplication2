# define _CRT_SECURE_NO_WARNINGS
#define maxim(massive, count) do { \
    int m_count = (count); \
    if (m_count > 0) { \
        double m_max = (massive)[0]; \
        for (int m_i = 1; m_i < m_count; m_i++) { \
            if ((massive)[m_i] > m_max) { \
                m_max = (massive)[m_i]; \
            } \
        } \
        printf("Maximum number: %lf\n", m_max); \
    } else { \
        printf("No numbers entered.\n"); \
    } \
} while(0)
#include <stdio.h>
#include <string.h>
#include <windows.h>

int main(void) {
	double num_m[100];
	char str_m[100];
	char* token;
	scanf("%100[^\n]", str_m);
	int i = 1; int j = 0;
	printf("Input Num: %d\n", i);
	token = strtok(str_m, " ");

	while (token != NULL) {
		num_m[j] = strtod(token, NULL);
		token = strtok(NULL, " ");
		j++;
	}
	printf("All numbers: \n");
	for (int i = 0; i < j; i++) {
		printf("Result %lf\n", num_m[i]);
	}
	maxim(num_m, j);
	return 0;
}