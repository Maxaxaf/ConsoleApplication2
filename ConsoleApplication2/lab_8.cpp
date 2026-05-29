#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <windows.h>
#include <string.h>
#include<locale.h>

struct Person {
	char name[50];
	char surname[50];
	char gender[50];
	int birth_year;
	double size;
};

void printPerson(struct Person p) {
	printf("%s %s %d %s %.2f\n", p.name, p.surname, p.birth_year, p.gender, p.size);
}

int main(void) {
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	struct Person massive[100];
	const char* filename = "lab_8.txt";
	int count = 0;
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Ошибка чтения файла\n");
		return 1;
	}

	while (fscanf(fp, "%s %s %d %s %lf",
		massive[count].name,
		massive[count].surname,
		&massive[count].birth_year,
		massive[count].gender,
		&massive[count].size) == 5) {
		count++;
	}
	fclose(fp);

	int choise[5] = { 0 };
	int num_par;
	printf("Введите сколько параметров сортировки вы хотите использовать: \n");
	scanf("%d", &num_par);

	if (num_par > 5) num_par = 5;
	printf("Сортировка: \n 1 - Имя \n 2 - Фамилия \n 3 - Год рождения \n 4 - Пол \n 5 - Рост \n");

	for (int i = 0; i < num_par; i++) {
		scanf("%d", &choise[i]);
	}

	printf("\nИсходный список:\n");
	for (int i = 0; i < count; i++) {
		printf("%s %s\n", massive[i].name, massive[i].surname);
	}

	struct Person temp;
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count - 1; j++) {
			for (int k = 0; k < num_par; k++) {
				int need_swap = 0;
				int is_equal = 0;
				switch (choise[k]) {
				case 1: 
					if (strcmp(massive[j].name, massive[j + 1].name) > 0) need_swap = 1;
					if (strcmp(massive[j].name, massive[j + 1].name) == 0) is_equal = 1;
					break;
				case 2: 
					if (strcmp(massive[j].surname, massive[j + 1].surname) > 0) need_swap = 1;
					if (strcmp(massive[j].surname, massive[j + 1].surname) == 0) is_equal = 1;
					break;
				case 3: 
					if (massive[j].birth_year > massive[j + 1].birth_year) need_swap = 1;
					if (massive[j].birth_year == massive[j + 1].birth_year) is_equal = 1;
					break;
				case 4: 
					if (strcmp(massive[j].gender, massive[j + 1].gender) > 0) need_swap = 1;
					if (strcmp(massive[j].gender, massive[j + 1].gender) == 0) is_equal = 1;
					break;
				case 5: 
					if (massive[j].size > massive[j + 1].size) need_swap = 1;
					if (massive[j].size == massive[j + 1].size) is_equal = 1;
					break;
				}

				if (need_swap) {
					temp = massive[j];
					massive[j] = massive[j + 1];
					massive[j + 1] = temp;
					break;
				}

				if (!is_equal) {
					break;
				}
			} 
		} 
	} 

	printf("\nОтсортированный список:\n");
	for (int i = 0; i < count; i++) {
		printPerson(massive[i]);
	}

	return 0;
}
