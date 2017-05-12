// heap_vs_quick.cpp : Defines the entry point for the console application.
/*Analyzation
Heap Sort:-a great advantage of heap-sort is that it provides the same time complexity in allthe 3 cases (best,worst,average), which is O(nlog),
		out of which O(n) is the build-heap (bottom-up) and the sorting itself takes O(nlogn) which in total gives us the O(nlogn time complexity)
		-best case : input is a heap -> no sinking is made, only comparisons (when buliding the heap)
		-worst case : input in an increasing array -> heapify takes O(n)
		-average case : input is a random array

Quick Sort:-it is not a stable sort, however in most of the cases (when not entering the worst case, which can be eliminated) is very efficient
		   -one of the worst cases would be to sort an array which has all the elements equal, this way each pair of numbers has to be swapped, with barely no use
	which gives us a time complexity of O(n^2)
		- the other one is to have a sorted array and to have as pivot the last element
		-in the average and best cases it behaves similarly, having a time complexity of O(nlogn)

*/



//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int a[10000];
int b[10000];
int A, C;

void swap(int *a, int *b) {
	int aux = *a;
	*a = *b;
	*b = aux;
}
void generateRandom(int n) {
	for (int i = 0; i < n; i++) {
		a[i] = rand();
	}

}

void generateUniqueRandom(int n) {
	for (int i = 0;i < n;i++) {
		a[i] = rand();
		for (int j = 0;j < i; j++) {
			if (a[i] == a[j]) {
				i--;
				break;
			}
		}
	}
}

void generateEqual(int n) {
	int number = rand();
	for (int i = 0; i < n; i++) {
		a[i] = rand()%5;
	}
}

void generateIncreasing(int n) {
	a[0] = rand();
	for (int i =1;i < n; i++) {
		a[i] = rand();
		if (a[i] < a[i - 1]) {
			i--;
		}
		
	}
}
void generateDecreasing(int n) {
	for (int i = 0;i < n; i++) {
		a[i] = n-i;

	}
}

int partition(int start, int end) {
	int x = a[end];
	int i = start - 1;
	for (int j = start; j < end ; j++) {
		C++;
		if (a[j] <= x) {
			i++;
			A = A + 3;
			swap(&a[i], &a[j]);
		}
	}
	A = A + 3;
	swap(&a[i + 1], &a[end]);
	return i + 1;
}
void quickSort(int start, int end) {
	if (start < end) {
		int q = partition(start, end);
		quickSort(start, q - 1);
		quickSort(q + 1, end);
	}
}
int randomized_partition(int start, int end) {
	int interv = end - start+1;
	int i = rand() % interv + start;
	A = A + 3;
	swap(&a[i], &a[end]);
	return partition(start, end);
}

int randomized_select(int start, int end, int i) {
	if (start == end) {
		return a[start];
	}
	int q = randomized_partition(start, end);
	int k = q - start+1 ;
	if (i == k) {
		return a[q];
	}
	else if (i < k) {
		return randomized_select(start, q - 1, i);
	}
	else return randomized_select(q + 1, end, i - k);

}
void randomized_quickSort(int start, int end) {

	if (start < end) {
		int q = randomized_partition(start, end);
		randomized_quickSort(start, q - 1);
		randomized_quickSort(q + 1, end);
	}
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

void sink_element(int index, int n) {

	int i = index;
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
		swap(&a[i], &a[index]);
		sink_element(i, n);
	}
	else {
		return;
	}

}

void BU_heap(int n) {
	A = 0;
	C = 0;
	int  current_ind = n - 1;
	for (int i = n / 2; i >= 0; i--) {
		sink_element(i, n);
	}


}

void heapSort(int n) {
	int len = n;
	for (int i = n - 1; i >= 1; i--) {
		A = A + 3;
		swap(&a[i], &a[0]);
		len--;
		sink_element(0, len);

	}
}
int main()
{
	int n, a1, a2, c1, c2;
	a1 = 0;
	a2 = 0;
	c1 = 0;
	c2 = 0;
	srand(time(NULL));
// ---Demo for quicksort correctness
	printf("QuickSort correctness: \n");
	generateRandom(10);
	for (int i = 0; i < 10; i++) {
		printf("%d ", a[i]);
	}
	printf("\n\n\n");
	randomized_quickSort(0, 9);
	for (int i = 0; i < 10; i++) {
		printf("%d ", a[i]);
	}
	printf("\n\n\n");

//--Demo for randomized select correctness
	printf("Randomized select correctness: \n");
	generateRandom(10);
	for (int i = 0; i < 10; i++) {
		printf("%d ", a[i]);
	}
	printf("\n\n\n");
	printf("%d ",randomized_select(0, 9, 5));


	FILE *out3 = fopen("worstAC.csv", "w");
	FILE *out6 = fopen("bestAC.csv", "w");
	FILE *out9 = fopen("averageAC.csv", "w");
	fprintf(out3, "n, HeapSort_A+C, QuickSort_A+C\n");
	fprintf(out6, "n, HeapSort_A+C, QuickSort_A+C\n");
	fprintf(out9, "n, HeapSort_A+C, QuickSort_A+C\n");
	


///--Analysis of heap and quicksort
	
	

//--Average

	for (int i = 1 ; i <= 100; i++) {
		n = i * 100;
		a1 = 0;
		a2 = 0;
		c1 = 0;
		c2 = 0;
		for (int j = 0; j < 5;j++) {
			generateRandom(n);
			for (int k = 0; k < n; k++) {
				b[k] = a[k];
			}
			BU_heap(n);
			heapSort(n);
			a1 += A;
			c1 += C;
			for (int k = 0; k < n; k++) {
				a[k] = b[k];
			}
			A = 0;
			C = 0;
			randomized_quickSort(0, n-1);
			a2 += A;
			c2 += C;

		}

		fprintf(out9, "%d, %d, %d\n", n, (a1 / 5 + c1 / 5), (a2 / 5 + c2 / 5));

	}
	
//--Best
	a1 = 0;
	a2 = 0;
	c1 = 0;
	c2 = 0;
	for (int i = 1; i <=100; i++) {
		n = i * 100;
		generateRandom(n);
		BU_heap(n);
		BU_heap(n);
		heapSort(n);
		a1 += A;
		c1 += C;

		generateUniqueRandom(n);
		A = 0;
		C = 0;
		randomized_quickSort(0, n-1);
		a2 += A;
		c2 += C;
		fprintf(out6, "%d, %d, %d\n", n, (a1 + c1), (a2  + c2 ));
	}

//--Worst
	a1 = 0;
	a2 = 0;
	c1 = 0;
	c2 = 0;
	for (int i = 1; i <=100; i++) {
		n = i * 100;
		generateIncreasing(n);
		BU_heap(n);
		heapSort(n);
		a1 += A;
		c1 += C;
		generateEqual(n);
		A = 0;
		C = 0;
		randomized_quickSort(0, n-1);
		a2 += A;
		c2 += C;
		fprintf(out3, "%d, %d, %d\n", n, (a1 + c1), (a2 + c2));
	}
	

    return 0;
}

