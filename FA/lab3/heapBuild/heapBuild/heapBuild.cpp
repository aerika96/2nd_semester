// heapBuild.cpp : Defines the entry point for the console application.
/*Analysation:
		Even from the chart it can be seen, that the top-down method is less efficient than the bottom-up. The main reason is that the bottom-ip metjod only does n/r heapify calls, while the top-dwon n-1 calls.
		Top-down:-> Each individual "insertion" takes logn
				->Insertion is repeated n-1 times
				->this gives a time complexity of O(nlogn)
		Bottom-up:->is a linear method for building a heap
			->the insertion of each element takes logn time
			->at the bottom level there are 2^h elements which does not need to be heapified
			->this gives us a final complexity of O(n)

*/

//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int a[10000];
int b[10000];
int A, C;
void generateRandom(int n) {
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		a[i] = rand();
	}

}

void swap(int *a, int *b) {
	int aux = *a;
	*a = *b;
	*b = aux;
}

int getParent_index(int index) {
	return index / 2;
}

int getLeftChild_index(int index) {
	return index * 2;
}

int getRightChild_index(int index) {
	return 2 * index + 1;
}

void sink_element(int index,int n) {
	
		int i=index;
		if (getLeftChild_index(index) < n) {
			C++;
			if (a[getLeftChild_index(index)] > a[index]) {
				i = getLeftChild_index(index);
			}
			else {
				i = index;
			}
		}
		if (getRightChild_index(index) < n) {
			C++;
			if (a[getRightChild_index(index)] > a[i]) {
				i = getRightChild_index(index);
			}
		}
		if (i != index) {
			A = A + 3;
			swap(&a[i],&a[index]);
			sink_element(i, n);
		}
		else {
			return;
		}
	
}
void rise_element(int index) {

		int key = a[index];
		if (getParent_index(index) >= 0) {
			C++;
			if (a[getParent_index(index)] < a[index]) {
				A = A + 3;
				swap(&a[getParent_index(index)], &a[index]);
				rise_element(getParent_index(index));
			}
		}
		else {
			return;
		}

	
}

void BU_heap(int n) {
	A = 0;
	C = 0;
	int  current_ind = n-1;
	for (int i = n / 2; i >= 0; i--) {
		sink_element(i, n);
	}
	

}
void heapSort(int n) {
	A = 0;
	C = 0;
	int len = n;
	for (int i = n - 1; i >= 1; i--) {
		swap(&a[i], &a[0]);
		len--;
		sink_element(0, len);

	}
}

void TD_heap(int n) {
	A = 0;
	C = 0;
	for (int i = 1; i < n; i++) {
		rise_element(i);
	}

}
int main()
{
	int n,a1,a2,c1,c2;
	//Test correctness
	generateRandom(10);
	for (int i = 0; i < 10; i++) {
		printf("%d ", a[i]);
	}
	printf("\n\n\nTop-down:");
	TD_heap(10);
	for (int i = 0; i < 10; i++) {
		printf("%d ", a[i]);
	}
	printf("\n\n\nSorted:");
	heapSort(10);
	for (int i = 0; i < 10; i++) {
		printf("%d ", a[i]);
	}
	printf("\n\n\n");
	generateRandom(10);
	for (int i = 0; i < 10; i++) {
		printf("%d ", a[i]);
	}
	printf("\n\n\nBottom-up:");
	BU_heap(10);
	for (int i = 0; i < 10; i++) {
		printf("%d ", a[i]);
	}
	printf("\n\n\nSorted:");
	heapSort(10);
	for (int i = 0; i < 10; i++) {
		printf("%d ", a[i]);
	}
	printf("\n\n\n");

	//Analysis

	FILE *out1 = fopen("average.csv", "w");
	fprintf(out1, "n, Bottom-up_A+C, Top-down_A+C\n");
	for (int i = 1; i <=100; i++) {
		n = i * 100;
		a1 = 0;
		a2 = 0;
		c1 = 0;
		c2 = 0;
		for (int j = 0; j < 5; j++) {
			generateRandom(n);
			for (int k = 0;k < n; k++) {
				b[k] = a[k];
			}
			BU_heap(n);
			a1 = a1+A;
			c1 = c1+C;
			for (int k = 0;k < n; k++) {
				a[k] = b[k];
			}
			TD_heap(n);
			a2 = a2 + A;
			c2 = c2 + C;
		}
		fprintf(out1,"%d, %d, %d\n",n, (a1 / 5 + c1 / 5), (a2 / 5 + c2 / 5));

	}

    return 0;
}

