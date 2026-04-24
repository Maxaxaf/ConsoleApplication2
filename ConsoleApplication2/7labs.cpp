#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

struct human
{
	char name[30];      
	char surname[30];   
	int age;
};

int main(void) {
	setlocale(LC_ALL, "en_US.UTF-8");
	struct human m_1[4] = { 0 };
	struct human m_2[4] = { 0 };
	int count;
	printf("Number: \n");
	if (scanf("%d", &count) != 1) {
		printf("Ошибка, введите число!\n");
		return 1; 
	}
	for (int i = 0; i < count; i++) {
		printf("Enter the name:");
		scanf("%s", m_1[i].name);

		printf("Enter the surname: ");
		scanf("%s", m_1[i].surname);

		printf("Enter the age: ");
		scanf("%d", &m_1[i].age);

	}
	printf("\nFirst massive\n");
	for (int i = 0; i < count; i++) {
		printf("%d: %s %s %d\n", i + 1, m_1[i].name, m_1[i].surname, m_1[i].age);
	}

	for (int i = 0; i < count; i++) {
		m_2[i] = m_1[i];
	 }

	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - 1; j++) {
			if (m_2[j].age > m_2[j + 1].age) {
				struct human zamen = m_2[j];
				m_2[j] = m_2[j + 1];
				m_2[j + 1] = zamen;
			}
		}
	}
	for (int i = 0; i < 2; i++) {
		printf("%s %s %d\n", m_2[i].name, m_2[i].surname, m_2[i].age);
	}
}