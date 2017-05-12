// dir_sorting1.cpp : Defines the entry point for the console application.
/*After evaluating each algorithm in all the three cases, one can easily observe that:
	- in the average cases: -the bubble sort is the least efficent (seen even from the totel number of operations)
						    -the number of assignments is the least at selection sort, because it is only looking for the minimum element, if found, it needs only 3 assignments to put it in place 
							-the number of comparisons is the least at insertion sort, because it doesn't need to traverse the whole sequence of numbers
		In general, I think I would go for the insertion sort algorith, since in real life we have quite a few chances to sort arrays of 10000 elements and insertionsort is the one, that behaves the best on smaller sizes
		(ex: for 100 numbers the average number od the total operations is 4509, for selection 5334, for bubble 10874 - bubble id probably the worst choice in the average case)
	- in the worst cases: - considering the number of total operations, probably the worst choice would be the bubble sort (again) - it needs to traverse the array repeatedly too many times
					but selection is probably a good one
						  - lookig at the number of assignations, again selection is the most efficient, since at each swap it has to perform three of them, while the other two a whole sequence
						  - from the comparisons' point of view they are basically equally inefficient, because the selection sort has to go at the end of the sequence in each cycle, the insertion finds the element that is going
                    to be inserted in one step, but it has to go to the other end of the sequence to put it in place, while the bubble sort has to traverse with each element a large amount of numbers and continuously swapping them
		In this case the best choice would be the selection sort.
	- in the best case: -the worst choice is the selection sort - whoever the first element in the unsorted  part is the least, it still goes through the whole array, looking for the minimum
						-based on the number of assigments we cannot tell which one to choose - none of them makes any
						-based on the number of comparisons, the bubble and the insertion are equally good
		I would still choose the insertion sort.

Complexity: all three have the complexity of O(N^2) : -selection sort goes through almost n elements almost n times (it doesn't have cases and it is not optimal)
													  -insertion sort shifts almost n elements almost n times
													  -bubble sort swaps almost n elements almost n times
													  (not quite but theoretically)
Stability: - the stability of selection sort depends on the array and the way it is implemented- it may not reserve the relative position if the elemet that is swapped with the minimum has the smallest index in the orginal array out of the numbers with th same value
		   - insertion sort is stable if it inserts equal elements one after the other (stops the shifting when an equal element is met)
		   - bubble sort is similar to insertion sort - stable if not swapped when equal

*/							
//

#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
int C, A;
int a[100000];
int b[100000];
int sortedArray(int array[], int n) {
	for (int i = 0; i < n - 1; i++) {
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

void generateRandom(int n) {
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		a[i] = rand();
	}

}

void generateWorst(int n) {

	for (int i = 0; i < n; i++) {
		a[i] = n - i;
	}



}

void generateBest(int n) {

	for (int i = 0; i < n; i++) {
		a[i] = i + 1;
	}

	


}
void BubbleSort( int n) {
	A = 0;
	C = 0;
	int swapped = 1;
	int lastPos = n - 1;
	int currentPos = 0;
	while (swapped) {
		swapped = 0;
		for (int i = 0; i < lastPos; i++) {
			C++;
			if (a[i] > a[i + 1]) {
				swap(&a[i], &a[i + 1]);
				A = A + 3;
				swapped = 1;
				currentPos = i;
			}

		}
		lastPos = currentPos;
	}
}

void InsertionSort( int n) {
	A = 0;
	C = 0;
	int selected;
	for (int i = 1; i < n; i++) {
		selected = a[i];
		int j;
		C++;
		for (j = i - 1; j >= 0 && a[j] > selected;j--, C++) {
			a[j + 1] = a[j];
			A++;
		}
		if (j != i - 1) {
			a[j+1] = selected;
			A++;
		}

	}
}

void SelectionSort( int n) {
	C = 0;
	A = 0;
	for (int i = 0; i < n - 1;i++) {
		int minind = i;
		for (int j = i; j < n; j++) {
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
	FILE *out1 = fopen("worstA.csv", "w");
	FILE *out2 = fopen("worstC.csv", "w");
	FILE *out3 = fopen("worstAC.csv", "w");
	FILE *out4 = fopen("bestA.csv", "w");
	FILE *out5 = fopen("bestC.csv", "w");
	FILE *out6 = fopen("bestAC.csv", "w");
	FILE *out7 = fopen("averageA.csv", "w");
	FILE *out8 = fopen("averageC.csv", "w");
	FILE *out9 = fopen("averageAC.csv", "w");
	fprintf(out1, "n, Bubble_A, Insert_A, Selection_A\n" );
	fprintf(out2, "n, Bubble_C, Insert_C, Selection_C\n");
	fprintf(out3, "n, Bubble_A+C, Insertion_A+C, Selection_A+C\n");
	fprintf(out4, "n, Bubble_A, Insert_A, Selection_A\n");
	fprintf(out5, "n, Bubble_C, Insert_C, Selection_C\n");
	fprintf(out6, "n, Bubble_A+C, Insertion_A+C, Selection_A+C\n");
	fprintf(out7, "n, Bubble_A, Insert_A, Selection_A\n");
	fprintf(out8, "n, Bubble_C, Insert_C, Selection_C\n");
	fprintf(out9, "n, Bubble_A+C, Insertion_A+C, Selection_A+C\n");


	generateRandom(30);

	for (int l = 0; l < 30; l++)
		printf("%d ", a[l]);
	printf("\n\n\n");
	BubbleSort(30);

	for (int l = 0; l < 30; l++)
		printf("%d ", a[l]);
	printf("\n\n\n");

	generateRandom(30);

	for (int l = 0; l < 30; l++)
		printf("%d ", a[l]);
	printf("\n\n\n");
	InsertionSort(30);

	for (int l = 0; l < 30; l++)
		printf("%d ", a[l]);
	printf("\n\n\n");
	
	generateRandom(30);

	for (int l = 0; l < 30; l++)
		printf("%d ", a[l]);
	printf("\n\n\n");
	SelectionSort(30);

	for (int l = 0; l < 30; l++)
		printf("%d ", a[l]);
	printf("\n\n\n");
	

	for (int i = 1; i <= 100; i++) {

		n = i * 100;
		int a1 = 0;
		int a2 = 0;
		int a3 = 0;
		int c1 = 0;
		int c2 = 0;
		int c3 = 0;
		for (int j = 0; j < 5; j++) {
			generateRandom(n);
			for (int k = 0; k < n; k++) {
				b[k] = a[k];
			}
			BubbleSort(n);
			a1 = a1+ A;
			c1 = c1+C;
			for (int k = 0; k< n; k++) {
				a[k] = b[k];
			}
			InsertionSort(n);
			a2 =a2+ A;
			c2 =c2+ C;
			for (int k = 0; k < n; k++) {
				a[k] = b[k];
			}
			SelectionSort(n);
			a3 =a3+ A;
			c3 =c3+C;
		}
		a1 = a1 / 5;
		a2 = a2 / 5;
		a3 = a3 / 5;
		c1 = c1 / 5;
		c2 = c2 / 5;
		c3 = c3 / 5;
		fprintf(out7, "%d, %d, %d, %d\n", n, a1, a2, a3);
		fprintf(out8, "%d, %d, %d, %d\n", n, c1, c2, c3);
		fprintf(out9, "%d, %d, %d, %d\n", n, a1+c1, a2+c2, a3+c3);

		
	}
	for (int i = 1; i <= 100; i++) {

		n = i * 100;
		int a1, a2, a3, c1, c2, c3;
		generateWorst(n);
		
		BubbleSort(n);

		a1 = A;
		c1 = C;
		generateWorst(n);

		InsertionSort(n);
		
		a2 = A;
		c2 = C;
		generateWorst(n);
		SelectionSort(n);
		a3 = A;
		c3 = C;
		fprintf(out1, "%d, %d, %d, %d\n", n, a1, a2, a3);
		fprintf(out2, "%d, %d, %d, %d\n", n, c1, c2, c3);
		fprintf(out3, "%d, %d, %d, %d\n", n, a1 + c1, a2 + c2, a3 + c3);


	}
	for (int i = 1; i <= 100; i++) {

		n = i * 100;
		int a1, a2, a3, c1, c2, c3;
		generateBest(n);
		BubbleSort(n);
		a1 = A;
		c1 = C;
		generateBest(n);

		InsertionSort(n);
		a2 = A;
		c2 = C;
		generateBest(n);
		SelectionSort(n);
		a3 = A;
		c3 = C;
		fprintf(out4, "%d, %d, %d, %d\n", n, a1, a2, a3);
		fprintf(out5, "%d, %d, %d, %d\n", n, c1, c2, c3);
		fprintf(out6, "%d, %d, %d, %d\n", n, a1 + c1, a2 + c2, a3 + c3);


	}
	return 0;
}

