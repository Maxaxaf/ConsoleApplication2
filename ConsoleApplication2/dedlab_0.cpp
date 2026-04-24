#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sieve(int n) {

    int size_in_bytes = (n / 8) + 1;
    unsigned char* bitArray = (unsigned char*)malloc(size_in_bytes);
    memset(bitArray, 0xFF, size_in_bytes);

    bitArray[0] &= ~(1 << 0);
    bitArray[0] &= ~(1 << 1);

    for (int p = 2; p * p <= n; p++) {
        if (bitArray[p >> 3] & (1 << (p & 7))) {
            for (int i = p * p; i <= n; i += p) {
                bitArray[i >> 3] &= ~(1 << (i & 7));
            }
        }
    }

    printf("Simple numbers up to %d:\n", n);
    for (int i = 2; i <= n; i++) {
        if (bitArray[i >> 3] & (1 << (i & 7))) {
            printf("%d ", i);
        }
    }
    printf("\n");

    free(bitArray);
}

int main() {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n < 2) {
        printf("Invalid input.\n");
        return 1;
    }

    sieve(n);
    return 0;
}

