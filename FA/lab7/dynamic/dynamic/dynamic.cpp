// dynamic.cpp : Defines the entry point for the console application.
/*
Analysis
BUILD-TREE
	-the method I used does the following: it always selects the middle element feom an array and inserts it in the tree (left or right or root- at the beginning)
	-partion in two
	-insert recursively
	- it takes O(n) linear time to build the tree
	-it also sets the size of the node (nr of elements under + itself)
OS_SELECT:
	-the task  is to find the ith element in an array
	-one selection takes logn
OS_DELETE:
	-delete the selected element
	-takes logn+nr of operations to change the elements

increases linearly


*/
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

typedef struct NodeTag {
	int key;
	int size;
	struct NodeTag *left;
	struct NodeTag *right;
	struct NodeTag *parent;
}NodeT;

int a[10000];
int select, del;
NodeT* root;
void generateIncreasing(int n) {
	for (int i = 0; i <n ; i++) {
		a[i] = i + 1;
	}

}

void inorder(NodeT *root, int level) {
	if (root == NULL) {
		return;
	}
	inorder(root->left,level+1);
	for (int i = 0; i <= level; i++) {
		printf("  ");
	}
	printf("%d->%d\n ", root->key, root->size);
	inorder(root->right,level+1);
}
NodeT* tree_successor(NodeT* node) {
	del++;
	NodeT* pWalker = node->right;

	while (pWalker->left != NULL) {
		del++;
		pWalker = pWalker->left;
	}
	return pWalker;
}

NodeT* BUILD_TREE(int start, int end) {
	if (start == end) {
		NodeT* node = (NodeT*)malloc(sizeof(NodeT));
		node->left = NULL;
		node->right = NULL;
		node->key = a[start];
		node->size = 1;
		return node;
	}
	else if (start > end) {
		return NULL;
	}
	
	else {
		NodeT* node = (NodeT*)malloc(sizeof(NodeT));
		node->key = a[(start + end) / 2];
		node->left = BUILD_TREE(start, (start + end) / 2 - 1);
		node->right = BUILD_TREE((start + end) / 2 + 1, end);
		if(node->left!=NULL)node->left->parent = node;
		node->right->parent = node;
		if (node->left == NULL) {
			node->size = node->right->size + 1;
		}
		else {
			node->size =node->left->size+ node->right->size + 1;
		}
		return node;
	}
}

NodeT* OS_Select(NodeT* node, int i) {
	int r;
	if (node->left != NULL) {
		r = node->left->size + 1;
	}
	else r = 1;
	select++;
		if (i == r) {
			return node;
		}
		select++;
		 if (i < r) {
			return OS_Select(node->left, i);
		}
		return OS_Select(node->right, i - r);
	
	
}


NodeT* OS_Delete(NodeT* node) {
	NodeT* y;
	NodeT* x;
	NodeT*pWalker;
	if (node->left == NULL || node->right == NULL) {
		del++;
		y = node;
	}
	else {
		del++;
		y = tree_successor(node);
	}
	
	if (y->left != NULL) {
		del++;
		x = y->left;
	}
	else { 
		del++;
		x = y->right; 
	}
	if (x != NULL) {
		del++;
		x->parent = y->parent;
	}
	if (y->parent == NULL) {
		del++;
		root = x;
	}
	else if (y == y->parent->left) {
		del++;
		y->parent->left = x;
	}
	else {
		del++;
		y->parent->right = x;
	}
	if (y != node) {
		del++;
		node->key = y->key;
	}
	del++;
	pWalker = y->parent;
	while (pWalker != NULL) {
		del += 2;
		pWalker->size--;
		pWalker = pWalker->parent;
	}
	return y;
}

int main()
{
	srand(time(NULL));
	int n;
	//Demo
	n = 11;
	int index;
	generateIncreasing(n);
	root = (NodeT*)malloc(sizeof(NodeT));
	root = BUILD_TREE(0, n - 1);
	root->parent = NULL;
	printf("Original tree:\n");
	inorder(root,0);
	while (n != 0) {
		index = rand() % n + 1;
		free(OS_Delete(OS_Select(root,index)));
		printf("Deleting: %d\n", index);
		inorder(root, 0);
		printf("\n\n");
		n--;
	}

	//Analysis
	FILE * out = fopen("result.csv", "w");
	fprintf(out,"n, OS_SELECT, OS_DELETE\n");
	for (int i = 1; i <= 100; i++) {
		
		for (int j = 0; j < 5; j++) {
			n = i * 100;
			select = 0;
			del = 0;
			int m = n;
			generateIncreasing(n);
			root = BUILD_TREE(0, n - 1);
			root->parent = NULL;
			while (n != 0) {
				index = rand() % n + 1;
				free(OS_Delete(OS_Select(root, index)));
				//printf("%d ,",n);
				n--;
			}
			fprintf(out, "%d,%d,%d\n", m, select, del);
		}
	}
    return 0;
}

