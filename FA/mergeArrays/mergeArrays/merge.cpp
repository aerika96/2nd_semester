/*Merging k arrays
The purpose of this algorithm is to merge k sorted arrays of the same size into one
This is realised by the following method:
	-fisrt we take the first element of each array and build a heap out of them
	-the heap is a minheap so we take the top elements (the root) which is for sure the smallest one
	-we need to remember in each node of the heap also the index of the array it came from
	-after we took the first element from the heap, we take another element from its "parent" array, if not empty;
	if it is empty, than we decrease the size of the heap and take the last element ank sink it
	-we continue this procedure until the size of the heap is 0 --> there are no more elments to insert in it (all the elements are 
	in the resulted array)

	This procedure takes logk to pop/push/heapify an  element and it has to be done n times --> it takes nlogk

	1.When k is fixed:  in this case the algorithm is linear, logk being just a constant --> n
	2.When n is fixed : in this case the algorithm is logarithmic, n being a constant and O being the function of k -->logk


*/

#include<stdlib.h>
#include<stdio.h>
#include<time.h>

typedef struct NodeTag {
	int key;
	struct NodeTag *next;
}NodeT;

typedef struct HeapTag {
	int key;
	int index;
}HeapT;

typedef struct {
	NodeT* first;
	NodeT*last;
}ListT;
int A, C;
int a[10000];
HeapT *heap;
void generateIncreasing(int n) {
	a[0] = rand() % 99;
	for (int i = 1;i < n; i++) {
		a[i] = a[i - 1] + rand() % 9;
	}

}
void swap(HeapT *a,  HeapT *b) {
	HeapT aux = *a;
	*a = *b;
	*b = aux;
}
int getParent_index(int index) {
	return index / 2;
}

int getLeftChild_index(int index) {
	return index * 2+1;
}

int getRightChild_index(int index) {
	return 2 * index + 2;
}
void sink_element(int index, int n) {

	int i = index;
	if (getLeftChild_index(index) < n) {
		C++;
		if ((heap+getLeftChild_index(index))->key < (heap+index)->key) {
			i = getLeftChild_index(index);
		}
		else {
			i = index;
		}
	}
	if (getRightChild_index(index) < n) {
		C++;
		if ((heap+getRightChild_index(index))->key < (heap+i)->key) {
			i = getRightChild_index(index);
		}
	}
	if (i != index) {
		A = A + 3;
		swap(&heap[i],&heap[index]);
		sink_element(i, n);
	}
	else {
		return;
	}

}

void BU_heap( int n) {
	A = 0;
	C = 0;
	int  current_ind = n - 1;
	for (int i = n / 2; i >= 0; i--) {
		sink_element(i,n);
	}


}

void insertNode(ListT* array, int number) {
	NodeT * pNew = (NodeT*)malloc(sizeof(NodeT));
	NodeT*pWalker = (NodeT*)malloc(sizeof(NodeT));
	pNew->next = NULL;
	pWalker = array->last;
	pWalker->next = pNew;
	array->last = pNew;
}
void createList(ListT* array, int n) {
	NodeT * pNew = (NodeT*)malloc(sizeof(NodeT));
	NodeT * pNew2 = (NodeT*)malloc(sizeof(NodeT));
	pNew->key = a[0];
	if (n == 1) {
		array->first = pNew;
		array->first->next = NULL;
	}
	else {
		pNew2->key = a[1];
		pNew2->next = NULL;
		array->last = pNew2;
		pNew->next = array->last;
		array->first = pNew;
		for (int i = 2; i < n; i++) {
			NodeT*pWalker = (NodeT*)malloc(sizeof(NodeT));
			NodeT*pAux;
			pWalker->key = a[i];
			pWalker->next = NULL;
			pAux = array->last;
			pAux->next = pWalker;
			array->last = pWalker;

		}
	}
}

void printList(ListT* array) {
	NodeT *pWalker = array->first;
	while (pWalker != NULL) {
		printf("%d ", pWalker->key);
		pWalker = pWalker->next;
	}
	printf("\n\n");
}
void mergeArrays(ListT *arrays, int k, int size) {
	heap = (HeapT*)malloc((k+1)* sizeof(HeapT));
	int length = 0;
	int* result = (int*)malloc(k*size*sizeof(int));
	for (int i = 0; i < k; i++) {
		(heap+i)->key = (arrays+i)->first->key;
		(heap + i)->index = i;
		(arrays+i)->first = (arrays+i)->first->next;
		length++;
	}
	BU_heap(k);
	/*for (int i = 0; i < k; i++) {
		printf("%d ", (heap + i)->key);
	}*/
	//printf("\n\n");
	int i = 1;
	int index_to_take;
	result[0] = heap->key;
	index_to_take = heap->index;
	while (length != 0) {
		if ((arrays + index_to_take)->first == NULL) {
			length--;
			heap->key = (heap + length)->key;
			heap->index = (heap + length)->index;
			sink_element(0, length);
		}
		else {
			heap->key = (arrays + index_to_take)->first->key;
			heap->index = index_to_take;
			(arrays + index_to_take)->first = (arrays + index_to_take)->first->next;
			sink_element(0, length);
		}
		*(result + i) = heap->key;
		index_to_take = heap->index;
		i++;
	}
	for (int i = 0; i < k*size; i++) {
		printf("%d ", *(result + i));
	}

	//free(heap);

}

int main() {
	int n,k,size;
	int a1, a2, a3, c1, c2, c3;
	srand(time(NULL));
	ListT *arrays = (ListT*)malloc(sizeof(ListT)*500);
	//----Demo
	generateIncreasing(20);
	createList(&arrays[0], 20);
	printList(&arrays[0]);
	generateIncreasing(20);
	createList(&arrays[1], 20);
	printList(&arrays[1]);
	generateIncreasing(20);
	createList(&arrays[2], 20);
	printList(&arrays[2]);
	generateIncreasing(20);
	createList(&arrays[3], 20);
	printList(&arrays[3]);
	mergeArrays(arrays, 4, 20);

	//--Analysis


	FILE *out1 = fopen("average.csv", "w");
	FILE *out2 = fopen("fixed_n.csv", "w");
	if (out1 == NULL || out2 == NULL) {
		printf("Cannot open file");
		exit(1);
	}
	fprintf(out1, "n, k==5, k==10, k==100\n");
	//k fixed,  k==5, k==10, k==100
	for (int i = 1; i <= 100; i++) {
		n = i * 100;
		k = 5;
		size = n / k;
	//	for(int l=0; l<5; l++){
		for (int j = 0; j < k; j++) {
			generateIncreasing(size);
			createList(&arrays[j], size);
			//printList(&arrays[j]);
		}
		mergeArrays(arrays, k, size);
		a1 = A;
		c1 = C;

		k = 10;
		size = n / k;
		for (int j = 0; j < k; j++) {
			generateIncreasing(size);
			createList(&arrays[j], size);
			//printList(&arrays[j]);
		}
		mergeArrays(arrays, k, size);
		a2 = A;
		c2 = C;

		k = 100;
		size = n / k;
		for (int j = 0; j < k; j++) {
			generateIncreasing(size);
			createList(&arrays[j], size);
			//printList(&arrays[j]);
		}
		mergeArrays(arrays, k, size);
		a3 = A;
		c3 = C;
	//}
		fprintf(out1,"%d,%d,%d,%d\n",n,(a1+c1),(a2+c2),(a3+c3));


	}

	// n fixed, n==10000
	n = 10000;
	fprintf(out2,"k, A+C\n");
	for (int i = 1; i <= 50; i++) {
		//for (int l = 0; l < 5; l++) {
			k = i * 10;
			int db = n / k;
			for (int j = 0; j < k; j++) {
				generateIncreasing(db);
				createList(&arrays[j], db);
			}
			mergeArrays(arrays, k, db);
			a3 = A;
			c3 = C;
		//}
		fprintf(out2,"%d,%d\n", k,( a3 + c3));

	}
	
	
	
	return 0;
}