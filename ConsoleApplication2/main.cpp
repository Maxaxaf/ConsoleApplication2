#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "triangle.h"

int get_triangle_sides(double* a, double* b, double* c) {
    printf("Enter side a: ");
    if (scanf("%lf", a) != 1) return 1;

    printf("Enter side b: ");
    if (scanf("%lf", b) != 1) return 1;

    printf("Enter side c: ");
    if (scanf("%lf", c) != 1) return 1;

    return 0;
}

int main() {
    double a, b, c;

    printf("Triangle Calculator\n");

    if (get_triangle_sides(&a, &b, &c) != 0) {
        printf("Invalid input!\n");
        return 1;
    }

    if (a <= 0 || b <= 0 || c <= 0) {
        printf("Sides must be positive!\n");
        return 1;
    }

    if (!is_valid_triangle(a, b, c)) {
        printf("Triangle inequality failed!\n");
        return 1;
    }

    double perimeter = calculate_perimeter(a, b, c);
    double area = calculate_area(a, b, c);

    printf("\nResults:\n");
    printf("Perimeter: %.2f\n", perimeter);
    printf("Area: %.2f\n", area);

    return 0;
}