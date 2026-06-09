#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct point {
    double x;
    double y;
    int num;
} MY_POINT;

MY_POINT* p = NULL;
MY_POINT* hull = NULL;
int hull_size = 0;

int compare(const void* a, const void* b) {
    MY_POINT* p1 = (MY_POINT*)a;
    MY_POINT* p2 = (MY_POINT*)b;
    if (p1->x < p2->x) return -1;
    if (p1->x > p2->x) return 1;
    if (p1->y < p2->y) return -1;
    if (p1->y > p2->y) return 1;
    return 0;
}

double cross_product(MY_POINT a, MY_POINT b, MY_POINT c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double distance_to_line(MY_POINT a, MY_POINT b, MY_POINT c) {
    return fabs(cross_product(a, b, c));
}

void quick_hull(MY_POINT* pts, int n, MY_POINT p1, MY_POINT p2, int side) {
    int max_idx = -1;
    double max_dist = 0.0;

    for (int i = 0; i < n; i++) {
        double cp = cross_product(p1, p2, pts[i]);

        if (pts[i].num == p1.num || pts[i].num == p2.num) continue;

        if ((side == 1 && cp > 1e-9) || (side == -1 && cp < -1e-9)) {
            double dist = distance_to_line(p1, p2, pts[i]);
            if (dist > max_dist) {
                max_dist = dist;
                max_idx = i;
            }
        }
    }

    if (max_idx == -1) {
        for (int i = 0; i < hull_size; i++) {
            if (hull[i].num == p1.num) return;
        }
        hull[hull_size++] = p1;
        return;
    }

    MY_POINT max_pt = pts[max_idx];

    quick_hull(pts, n, p1, max_pt, cross_product(p1, max_pt, p2) < 0 ? 1 : -1);
    quick_hull(pts, n, max_pt, p2, cross_product(max_pt, p2, p1) < 0 ? 1 : -1);
}

void find_convex_hull(MY_POINT* pts, int n) {
    if (n < 3) {
        for (int i = 0; i < n; i++) hull[hull_size++] = pts[i];
        return;
    }

    MY_POINT min_x = pts[0];
    MY_POINT max_x = pts[n - 1];

    quick_hull(pts, n, min_x, max_x, 1);
    quick_hull(pts, n, min_x, max_x, -1);

    hull[hull_size++] = max_x;
}

int main(int argc, char* argv[]) {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    FILE* In, * Out;
    int i, num;
    double x, y;

    if (argc < 2) {
        printf("Использование: %s <имя_входного_файла>\n", argv[0]);
        return 1;
    }

    In = fopen(argv[1], "r");
    if (In == NULL) {
        printf("Ошибка открытия входного файла %s\n", argv[1]);
        return 1;
    }

    p = (MY_POINT*)malloc(100000 * sizeof(MY_POINT));
    hull = (MY_POINT*)malloc(100000 * sizeof(MY_POINT));

    i = 0;
    while (fscanf(In, "%d%lf%lf", &num, &x, &y) == 3 && i < 100000) {
        p[i].num = num;
        p[i].x = x;
        p[i].y = y;
        i++;
    }
    fclose(In);

    int n = i;
    if (n == 0) {
        printf("Входной файл пуст.\n");
        free(p); free(hull);
        return 0;
    }

    qsort(p, n, sizeof(MY_POINT), compare);

    find_convex_hull(p, n);

    Out = fopen("OUT.dat", "w");
    if (Out == NULL) {
        printf("Ошибка создания выходного файла OUT.dat\n");
        free(p); free(hull);
        return 1;
    }

    for (i = 0; i < hull_size; i++) {
        fprintf(Out, "%d\n", hull[i].num);
    }
    fclose(Out);

    printf("Выпуклая оболочка построена. Найдено вершин: %d. Результат в OUT.dat\n", hull_size);

    free(p);
    free(hull);
    return 0;
}
