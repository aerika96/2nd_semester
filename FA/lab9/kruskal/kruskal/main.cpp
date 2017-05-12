#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<stdio.h>

int vertices[10000];
int op;
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


NodeT* make_set(int x, NodeT*newSet) {
	newSet->key = x;
	newSet->rank = 0;
	newSet->parent = newSet;
	op += 3;
	return newSet;
}

NodeT* find_set(NodeT* element) {
	op++;
	if (element == element->parent) {
		return element;
	}
	else {
		op++;
		element->parent = find_set(element->parent);
	}
}

NodeT* set_union(NodeT*x, NodeT* y) {
	NodeT * parent_x = find_set(x);
	NodeT* parent_y = find_set(y);
	op++;
	if (parent_x->rank > parent_y->rank) {
		op++;
		parent_y->parent = parent_x;
		return parent_x;
	}
	else {
		op++;
		parent_x->parent = parent_y;
		op++;
		if (parent_x->rank == parent_y->rank) {
			op++;
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
	
	sort(n*4);
	
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
	fprintf(out, "n,operations\n");
	for (int i = 1; i <= 100; i++) {
		n = i * 100;
		generateRandom(n);
		op = 0;
		EdgeT** set = MST_kruskal(n);
		fprintf(out, "%d,%d\n", n, op);

	}

	return 0;
}