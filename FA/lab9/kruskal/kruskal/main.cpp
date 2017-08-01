#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<stdio.h>
/*Analysis
The Kruskal algorithm is based on disjoint set operations - it solves the minimum spanning tree problem
	-first of all, creates a disjoint set from each node with MAKE_SET operation, resulting into a |V| nr. of sets of a single node, having as parent itself
	-the next step is to create |V|*4 nr of edges - it takes |V|*4 time (but this is not evaluated, not being a disjoint set operation)
	-next the edges are sorted in a non-decreasing order (kruskal being a greedy algorithm, always chooses the edge with the smallest weight) - |E|lg|E| time  - I used heap-sort
	-passing through the ordered list of edges, it tries to select each time the one with the smallest weight - only that edge  can be selected, which does not close a circle - with FIND_SET it is verified 
	whether the two endpoints of the edge belong to the same set or not
	-if not, they are added to the final treee and using the UNION operation, the edge united with the rest of the edges
	-the final running time of the algorithm is O(|E|lg|V|)
*/

int vertices[10000];
int make_op, find_op, union_op, total;
typedef struct _node {
	_node *parent;
	int key;
	int rank;
}NodeT;

typedef struct _edge {
	NodeT* start;
	NodeT* end;
	int weight;
}EdgeT;

EdgeT **A= (EdgeT**)malloc(40000 * sizeof(EdgeT*));
NodeT** vertex = (NodeT**)malloc(10000 * sizeof(NodeT*));
EdgeT** edges = (EdgeT**)malloc(40000*sizeof(EdgeT*));


void generateRandom(int n) {
	vertices[0] = rand() % 100;
	for (int i = 1; i < n; i++) {
		vertices[i] = vertices[i - 1] + 1 + rand() % 100;
	}
}

void generateEdges(int n) {
	int i;
	for (i = 0; i < n - 1; i++) {
		edges[i]->start = vertex[i];
		int newind =i+1+ rand() % (n-i-1);
		edges[i]->end = vertex[newind];
		edges[i]->weight = rand() % 10000;
	}
	while (i < 4 * n) {
		int ind1 = rand() % (n-1);
		int ind2 = ind1 + 1;
			edges[i]->start = vertex[ind1];
			edges[i]->end = vertex[ind2];
			edges[i]->weight = rand() % 10000;
			i++;
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
void sink_element(int index, int n) {

	int i = index;
	if (getLeftChild_index(index) < n) {
		if (edges[getLeftChild_index(index)]->weight > edges[index]->weight) {
			i = getLeftChild_index(index);
		}
		else {
			i = index;
		}
	}
	if (getRightChild_index(index) < n) {
		if (edges[getRightChild_index(index)]->weight > edges[i]->weight) {
			i = getRightChild_index(index);
		}
	}
	if (i != index) {
		EdgeT * aux;
		aux = edges[i];
		edges[i] = edges[index];
		edges[index] = aux;
		sink_element(i, n);
	}
	else {
		return;
	}

}

void BU_heap(int n) {

	int  current_ind = n - 1;
	for (int i = n / 2; i >= 0; i--) {
		sink_element(i, n);
	}


}
void heapSort(int n) {
	int len = n;
	for (int i = n - 1; i >= 1; i--) {
		EdgeT * aux;
		aux = edges[i];
		edges[i] = edges[0];
		edges[0] = aux;
		len--;
		sink_element(0, len);

	}
}

NodeT* make_set(int x, NodeT*newSet) {
	newSet->key = x;
	newSet->rank = 0;
	newSet->parent = newSet;
	make_op +=3;
	return newSet;
}

NodeT* find_set(NodeT* element) {
	find_op++;
	if (element == element->parent) {
		return element;
	}
	else {
		find_op++;
		element->parent = find_set(element->parent);
	}
}

NodeT* set_union(NodeT*x, NodeT* y) {
	NodeT * parent_x = find_set(x);
	NodeT* parent_y = find_set(y);
	union_op++;
	if (parent_x->rank > parent_y->rank) {
		union_op++;
		parent_y->parent = parent_x;
		return parent_x;
	}
	else {
		union_op++;
		parent_x->parent = parent_y;
		union_op++;
		if (parent_x->rank == parent_y->rank && parent_x!=parent_y) {
			union_op++;
			parent_y->rank++;
		}
		return parent_y;
	}
}

void sort(int n) {
	int swapped = 1;
	int lastPos = n - 1;
	int currentPos = 0;
	while (swapped) {
		swapped = 0;
		for (int i = 0; i < lastPos; i++) {

			if (edges[i]->weight > edges[i + 1]->weight) {
				EdgeT * aux;
				aux = edges[i];
				edges[i] = edges[i + 1];
				edges[i + 1] = aux;
				swapped = 1;
				currentPos = i;
			}

		}
		lastPos = currentPos;
	}
}

EdgeT** MST_kruskal(int n){
	int j = 0;
	for (int i = 0; i < n; i++) {
		vertex[i] = make_set(vertices[i],vertex[i]);
	}
	generateEdges(n);
	BU_heap(n * 4);
	heapSort(n*4);
	
	for (int i = 0; i < n * 4; i++) {
		NodeT* u = edges[i]->start;
		NodeT* v = edges[i]->end;
		if (find_set(u) != find_set(v)) {
			A[j] = edges[i];
			set_union(u, v);
		}
	}
	
	return A;

}

int main() {
	srand(time(NULL));
	int n;
	//Demo - make, find, union
	NodeT** sets = (NodeT**)malloc(10 * sizeof(NodeT*));
	for (int i = 0; i <10; i++) {
		sets[i] = (NodeT*)malloc(sizeof(NodeT));
		sets[i] = make_set(i,sets[i]);
	}

	for (int i = 0; i < 5; i++) {

		int x, y;
		x = rand() % 10;
		y = x;
		do {
			y = rand() % 10;
		} while (x == y);
		printf("Before: find_set(%d) = %d, rank:%d and find_set(%d) = %d, rank:%d\n ", sets[x]->key, find_set(sets[x])->key,find_set(sets[x])->rank, sets[y]->key, find_set(sets[y])->key, find_set(sets[y])->rank);
		set_union(sets[x], sets[y]);
		printf("After: find_set(%d) = %d, rank:%d and find_set(%d) = %d, rank:%d\n", sets[x]->key, find_set(sets[x])->key,find_set(sets[x])->rank, sets[y]->key, find_set(sets[y])->key,find_set(sets[y])->rank);
	}
	for (int i = 0; i < 10; i++) {
		free(sets[i]);
	}
	for (int i = 0; i < 10000; i++) {
		vertex[i] = (NodeT*)malloc(sizeof(NodeT));
	}
	for (int i = 0; i < 40000; i++) {

		edges[i] = (EdgeT*)malloc(sizeof(EdgeT));
	}
	FILE * out = fopen("kruskal.csv", "w");
	fprintf(out, "n,make_set,find_set,union,total\n");
	for (int i = 1; i <= 100; i++) {
		n = i * 100;
		generateRandom(n);
		union_op = 0;
		make_op = 0;
		find_op = 0;
		EdgeT** set = MST_kruskal(n);
		fprintf(out, "%d,%d,%d,%d,%d\n", n, make_op,find_op,union_op,make_op+union_op+find_op);

	}

	return 0;
}