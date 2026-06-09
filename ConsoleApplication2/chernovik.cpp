#define FindMaxArr(Arr,n,OutMkr) {int MaxArr=Arr[0]; for (int i=0; i<n; i++) {if (Arr[i] > MaxArr) MaxArr = Arr[i]; } *(OutMkr) = MaxArr;}
#include <stdio.h>
int main(void) {
	int TArr[5] = { 1,2,3,4,5 };
	int RezMax;
	FindMaxArr(TArr, 5, &RezMax);
	printf("Result: %i\n", RezMax);
	return 0;
}

