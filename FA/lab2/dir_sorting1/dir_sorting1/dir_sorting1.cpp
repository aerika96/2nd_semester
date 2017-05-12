// dir_sorting1.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
int C, A;
int sortedArray(int array[], int n) {
	for (int i = 0; i < n-1; i++) {
		if (array[i] > array[i + 1]) {
			return 0;
		}
	}
	return 1;
}
void swap(int *a, int *b) {
	int aux = *a;
	*a = *b;
	*b = aux;
}

int * generateRandom(int n) {
	int *array = (int *)malloc(sizeof(int)*n);
	if (array == NULL) {
		printf("Array not allocated");
		exit(1);
	}
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		array[i] = rand() ;
	}

    return array;


}

int * generateWorst(int n) {
	int *array = (int *)malloc(sizeof(int)*n);
	if (array == NULL) {
		printf("Array not allocated");
		exit(1);
	}
	for (int i = 0; i < n; i++) {
		array[i] = n-i;
	}

	return array;


}

int * generateBest(int n) {
	int *array = (int *)malloc(sizeof(int)*n);
	if (array == NULL) {
		printf("Array not allocated");
		exit(1);
	}
	for (int i = 0; i < n; i++) {
		array[i] = i + 1;
	}

	return array;


}
void BubbleSort(int *array, int n) {
	A = 0;
	C = 0;
	int swapped = 1;
	int lastPos = n - 1;
	int currentPos = 0;
	while (swapped) {
		swapped = 0;
		for (int i = 0; i < lastPos; i++) {
			C++;
			
			if (array[i] > array[i + 1]) {
				swap(&array[i], &array[i + 1]);
				A = A + 3;
				swapped = 1;
				currentPos = i;
			}
			
		}	
		lastPos = currentPos;
	}
	for (int i = 0; i < n; i++) {
		printf("%d ", array[i]);
	}
}

void InsertionSort(int *a, int n) {
	A = 0;
	C = 0;
	int selected;
	for (int i =1 ; i < n; i++) {
		selected = a[i];
		int j;
		for (j = i - 1; j >= 0 && a[j] > selected;j--,C++) {
			a[j + 1] = a[j];
			A++;
		}
		a[j] = selected;

	}
}

void SelectionSort(int *a, int n) {
	C = 0;
	A = 0;
	for (int i = 0; i < n - 1;i++) {
		int minind = i;
		for (int j = i; j < n ; j++) {
			C++;
			if (a[minind] > a[j]) {
				minind = j;
			}
		}
		if (minind != i) {
			swap(&a[i], &a[minind]);
			A = A + 3;
		}
	}
}

int main()
{
	int n;
	FILE *out = fopen("data.csv", "w");
	fprintf(out, "n, A, C, A+C");
	for (int i = 1; i <= 10; i++) {

		n = i*100;
		int *a = generateRandom(n);
		SelectionSort(a, n);
		for (int i = 0; i < n; i++) {
			printf("%d ", a[i]);
		}
		printf("\n\n\n");
	}
	return 0;
}

