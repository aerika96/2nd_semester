/*
Analysis

T1: transfroms an array into an array of lists - I chose the lits data structure because of 2 reasons:
													1.One can insert into the list in O(1), the list aving a poiter to the first and the last element
													2. When transforming the lists into a binary form, it is easier to find the brother it the element (node) has a 
													pointer to it
	The total runnung time is O(n)
T2: transforms an array of lists into a binary form - here the idea was to  have a node type both to the children, brother, but also for the next element - easier  to set  the pointers
													- starting from the root, checks the list of the children an the vrother and sets the pointers
													- 2 recursive calls
													-n^0 outside the recursie calls
	The total running time is O(n)


*/
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
typedef struct NodeTag {
	int key;
	struct NodeTag *next;
	NodeTag* child;
	NodeTag *brother;
}NodeT;
typedef struct ListTag {
	NodeT *first;
	NodeT *last;

}ListT;
typedef struct TreeTag {
	
}TreeT;
NodeT * root;
ListT* parent_to_multi(int array[]) {
	ListT *lists = (ListT*)malloc(9 * sizeof(ListT));
	for (int i = 0; i <= 9; i++) {
		(lists+i)->first = NULL;
	}
	for (int i = 0; i < 9; i++) {
		NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));
		newNode->key = i+1;
		newNode->next = NULL;
		if (array[i] != -1) {
			if ((lists + array[i])->first == NULL) {
				(lists + array[i])->first = newNode;
				(lists + array[i])->last = newNode;
			}
			else {
				(lists + array[i])->last->next = newNode;
				(lists + array[i])->last = newNode;
			}
		}
		else {
			root = (NodeT*)malloc(sizeof(NodeT));
			root->key = i+1;
		}
	}
	return lists;
	
}

void multi_to_binary(NodeT* rt,ListT*lists) {
	if (rt == NULL) {
		return;
	}
	else {
		 if ((lists + rt->key)->first != NULL) {
			rt->child = (lists + rt->key)->first;
		}
		else rt->child = NULL;
		if (rt == root) {
			rt->brother = NULL;
		}
		else if (rt->next != NULL) {
			rt->brother = rt->next;
		}
		else rt->brother = NULL;
		multi_to_binary(rt->child,lists);
		if (rt != root) {
			multi_to_binary(rt->brother, lists);
		}

	}

}
void pretty_print(NodeT *rt, int level) {
	if (rt == NULL) {
		return;
	}
	for (int i = 0; i <= level; i++) {
		printf("  ");
	}
	printf("%d\n ", rt->key);

	pretty_print(rt->child, level + 1);
	pretty_print(rt->brother, level);
}

int main() {

	int parent[9] = { 2,7,5,2,7,7,-1,5,2 };
	ListT* result = (ListT*)malloc(10*sizeof(ListT));
	result = parent_to_multi(parent);
	for (int i = 0; i <= 9; i++) {
		if ((result + i)->first != NULL) {
			printf("%d: ", i);
			NodeT* pWalker = (result + i)->first;
			while (pWalker != NULL) {
				printf("%d ", pWalker->key);
				pWalker = pWalker->next;
			}
			printf("\n");
		}
	}
	multi_to_binary(root, result);

	pretty_print(root,0);

}