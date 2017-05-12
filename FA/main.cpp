#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"

/*
    both operations appear to be linear, altough delete has a bigger multiplicative constance, since is has to find the node, and then to delete it.
*/

typedef struct TreeNodeTag {
	int value;
	int nr_elements;
	struct TreeNodeTag *left;
	struct TreeNodeTag *right;
}TreeNodeT;

int delete_op = 0;
int select_op = 0;
Profiler profiler = Profiler();

TreeNodeT* create_TreeNodeT(int value)
{
	TreeNodeT* node = (TreeNodeT*)malloc(sizeof(TreeNodeT));
	if (node == NULL) {
		return NULL;
	}

	node->nr_elements = 1;
	node->value = value;
	node->left = node->right = NULL;

	return node;
}

int get_nr_elements(TreeNodeT* node)
{
	if (node == NULL) {
		return 0;
	}
	return node->nr_elements;
}

TreeNodeT* recursive_build_PBT(int *array, int start, int end)
{
	if (start > end) {
		return NULL;
	}

	int m = (start + end) / 2;
	TreeNodeT* node = create_TreeNodeT(array[m]);
	node->left = recursive_build_PBT(array, start, m - 1);
	node->right = recursive_build_PBT(array, m + 1, end);
	node->nr_elements = 1 + get_nr_elements(node->left) + get_nr_elements(node->right);

	return node;
}

TreeNodeT* os_select(TreeNodeT* root, int index)
{
	int root_index = get_nr_elements(root->left) + 1;
	select_op++;
	if (index == root_index) {
		return root;
	}
	
	select_op++;
	if (index < root_index) {
		return os_select(root->left, index);
	}

	return os_select(root->right, index - root_index);
}

TreeNodeT* find_successor(TreeNodeT* root)
{
	delete_op++;
	root = root->right;
	while (root->left != NULL) {
		delete_op++;
		root = root->left;
	}

	return root;
}

TreeNodeT* os_delete(TreeNodeT* root, int index)
{
	int root_index = get_nr_elements(root->left) + 1;
	delete_op++;
	if (index == root_index) {
		//found the element to be deleted
		if (root->left == NULL && root->right == NULL) {
			free(root);
			return NULL;
		}

		if (root->left == NULL && root->right != NULL) {
			delete_op++;
			TreeNodeT* aux = root->right;
			free(root);
			return aux;
		}

		if (root->left != NULL && root->right == NULL) {
			delete_op++;
			TreeNodeT* aux = root->left;
			free(root);
			return aux;
		}

		TreeNodeT* successor = find_successor(root);
		delete_op += 2;
		root->value = successor->value;
		return os_delete(root, index + 1);
	}
	delete_op += 2;
	if (index < root_index) {
		root->left = os_delete(root->left, index);
	} else {
		root->right = os_delete(root->right, index - root_index);
	}

	delete_op++;
	root->nr_elements--;
	return root;
}

TreeNodeT* build_PBT(int *array, int lenght)
{
	return recursive_build_PBT(array, 0, lenght - 1);
}

void free_Tree(TreeNodeT* root)
{
	if (root == NULL) {
		return;
	}

	free_Tree(root->left);
	free_Tree(root->right);
	free(root);
}

void pretty_print_TreeNodeT(TreeNodeT* root, int level)
{
	if (root == NULL) {
		return;
	}

	pretty_print_TreeNodeT(root->left, level + 1);
	for(int i = 0; i < level; i++) {
		printf("    ");
	}
	printf("%d:%d\n", root->value, root->nr_elements);
	pretty_print_TreeNodeT(root->right, level + 1);
}

void increasingarray(int *array, int n)
{
	for(int i = 0; i < n; i++) {
		array[i] = i + 1;
	}
}

int get_rand_index(int n)
{
	return (rand() % n) + 1;
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	int ntest = 11;
	int *incarray = (int*)malloc(sizeof(int) * 10000);
	increasingarray(incarray, ntest);
	TreeNodeT* roottest = build_PBT(incarray, ntest);
	pretty_print_TreeNodeT(roottest, 0);

	for(int i = 0; i < 3; i++) {
		int rand_index = get_rand_index(ntest--);
		printf("selected: %d, with index: %d\n", os_select(roottest, rand_index)->value, rand_index);
		roottest = os_delete(roottest, rand_index);
		pretty_print_TreeNodeT(roottest, 0);
	}

	increasingarray(incarray, 10000);
	for(int i = 1; i <= 100; i++) {
		printf("i: %d\n", i);
		int n = i * 100;
		select_op = delete_op = 0;

		for(int j = 0; j < 5; j++) {
			TreeNodeT* root = build_PBT(incarray, n);
			for(int k = 0; k < n; k++) {
				int rand_index = get_rand_index(n - k);
				os_select(root, rand_index);
				root = os_delete(root, rand_index);
			}
		}
		select_op /= 5;
		delete_op /= 5;
		profiler.countOperation("select", n, select_op);
		profiler.countOperation("delete", n, delete_op);
	}
	profiler.createGroup("order statistics", "select", "delete");
	profiler.showReport();

	system("pause");
}