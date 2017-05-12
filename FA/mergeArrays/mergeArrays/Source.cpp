#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include "Profiler.h"

int a[10000];
Profiler profiler("Profiler");

typedef struct nodetype
{
	int key; /* an optional field */
	struct nodetype *next;
} NodeT;

struct header
{
	int size;
	NodeT* first;
	NodeT* last;
};


int heap_size, n1;

//x and y sent as reference
void swap(NodeT **x, NodeT **y) {
	NodeT* z = *x;
	*x = *y;
	*y = z;
}

void insert_beginning(struct header *head, int key) {
	NodeT* p = (NodeT*)(malloc(sizeof(NodeT)));
	p->key = key;
	if (head->first == NULL) {
		head->first = p;
		head->last = p;
		p->next = NULL;
		head->size = 1;
	}
	else {
		p->next = head->first;
		head->first = p;
		head->size++;
	}
}

void display(struct header *head) {
	NodeT *p = head->first;
	printf("List: ");
	while (p != NULL) {
		printf("%d ", p->key);
		p = p->next;
	}
	printf("\n");
}

void minHeapify(NodeT* a[], int n, int i) {
	int l = 2 * i;
	int r = 2 * i + 1;
	int smallest;

	profiler.countOperation("MergeTotal", n1, 2);
	if ((l <= heap_size) && (a[l]->key < a[i]->key)) smallest = l;
	else smallest = i;

	profiler.countOperation("MergeTotal", n1, 1);
	if ((r <= heap_size) && (a[r]->key < a[smallest]->key)) {
		profiler.countOperation("MergeTotal", n1, 1);
		smallest = r;
	}

	if (smallest != i) {
		profiler.countOperation("MergeTotal", n1, 3);
		swap(&a[i], &a[smallest]);
		minHeapify(a, n, smallest);
	}
}

void buildMinHeap(NodeT* a[], int n) {
	int i;
	for (i = n / 2; i > 0; i--) {
		minHeapify(a, n, i);
	}
}

void displayHeap(NodeT** heap, int k) {
	int i;
	printf("Heap: ");
	for (i = 1; i <= k; i++) {
		printf("%d ", heap[i]->key);
	}
	printf("\n");
}

int main() {
	struct header head;
	int k, n;
	printf("k = ");
	scanf("%d", &k);

	printf("n = ");
	scanf("%d", &n);

	//n = 10000;
	//for(k = 10; k < 500; k+=10) {
	//printf("%d ", k);
	//n1 = k;

	struct header * list_headers = (struct header*)malloc(k * sizeof(struct header));
	FillRandomArray(a, n, 10, 100, false, 2);

	int i;

	//make sure that lists are empty and correctly formatted
	for (i = 0; i < k; i++) {
		list_headers[i].first = list_headers[i].last = NULL;
	}

	//insert at least one element in each of them
	for (i = 0; i < k; i++) {
		insert_beginning(&list_headers[i], a[i]);
	}

	//distribute other elements randomly
	srand(time(NULL));
	for (i = k; i < n; i++) {

		int random = rand() % k;
		insert_beginning(&list_headers[random], a[i]);
	}

	//display all lists
	for (i = 0; i < k; i++) {
		display(&list_headers[i]);
	}

	printf("\n");

	NodeT **heap = (NodeT**)malloc((k + 1) * sizeof(NodeT*));

	for (i = 0; i < k; i++) {
		heap[i + 1] = list_headers[i].first;
	}

	int *final_array = (int*)malloc(n * sizeof(int));
	i = 0;
	heap_size = k;

	buildMinHeap(heap, heap_size);
	while (heap[1] != NULL) {
		displayHeap(heap, heap_size);
		final_array[i] = heap[1]->key;
		i++;
		heap[1] = heap[1]->next;

		if (heap[1] == NULL) {
			int j;
			for (j = 1; j < heap_size; j++) {
				heap[j] = heap[j + 1];
			}
			heap_size--;
			if ((heap_size >= 2) && (heap[1]->key > heap[2]->key)) {
				swap(&heap[1], &heap[2]);
			}
		}
		else {
			minHeapify(heap, heap_size, 1);
		}
	}


	printf("\nFinal list: ");
	for (i = 0; i < n; i++) {
		printf("%d ", final_array[i]);
	}
	//}

	//profiler.showReport();

	getch();
	return 0;
}