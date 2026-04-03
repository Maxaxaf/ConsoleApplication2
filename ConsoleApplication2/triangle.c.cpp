#include "triangle.h"
#include <math.h>

bool is_valid_triangle(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return false;
    }

    if (a + b > c && a + c > b && b + c > a) {
        return true;
    }

    return false;
}

double calculate_perimeter(double a, double b, double c) {
    return a + b + c;
}

double calculate_area(double a, double b, double c) {
    double p = calculate_perimeter(a, b, c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}