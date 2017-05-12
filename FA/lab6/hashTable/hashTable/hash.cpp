/*Analysis
HaSH Tables
	-hash function is given
	-with open addressing we rehash the key as many times as possible to find an empty slot for it where we can place it 
	(until the hash value exceeds the boundaries)
	-the size of the hash table (M) must be a prime number to decrease even by this the  collision occurence
	-alpha (filling) factor is given by n/M - the number of elements relative to the size of the table
	-if the filling factor is increasing -> the number of elements is also increasing
		- in case of search for those elements that should not be found, the number of element accesses increases, because the search only stops when the hash value 
		exceeds the size of the table or finds a NULL element - in our case there will be not many NULLs
		-in the case of search for those elements that should be found, the number of accesses also increases, but not that radically like in the previous case
		but if there are many elements -> there are may collisions handled - the number of steps to find and alresay inserted key is also greater.
*/

#include <stdlib.h>
#include<stdio.h>
#include<time.h>
#define M 9973
#define c1 1
#define c2 2
int table[M];
int a[10000];
int to_find[1500];
int not_to_find[1500];
int OP;
void generateRandom(int n) {
	a[0] = rand() % 99;
	for (int i = 1; i < n; i++) {
		a[i] = a[i - 1] + rand() % 5;
	}
}
int hash(int k, int i) {
	int h = (k % M + c1 *i + c2*i*i) % M;
	return h;
}

int hash_insert(int element) {
	int j, i = 0;
	do {
		j = hash(element, i);
		if (table[j] == NULL) {
			table[j] = element;
			return 1;
		}
		else {
			i++;
		}

	}while (i < M);
	
	return 0;
}
int hash_search(int element) {
	OP = 0;
	int i = 0;
	int j;
	do {
		j = hash(element, i);
		OP++;
		if (table[j] == element) {
			return 1;
		}
		i++;
	} while (table[j] != NULL && i < M);
	return 0;
}

int main() {

	//Demo
	/*int demo[10] = { 1,2,4,6,8,10,12,14,16,18};
	for (int i = 0; i < M; i++) {
		table[i] = NULL;
	}
	for (int i = 0; i < 10; i++) {
		hash_insert(demo[i]);
	}
	for (int i = 0; i < M; i++) {
		if (table[i] != NULL) {
			printf("%d ", table[i]);
		}
	}*/

	double n, alpha;
	int i,nf,f,i_n, max_effort_f,avg_effort_f, max_effort_nf, avg_effort_nf;
	srand(time(NULL));
	FILE  *out = fopen("hash.csv", "w");
	fprintf(out, "Filling Factor, Avg. Effort-foun,Max. Effort-found, Avg.Effort-not found, Max. Effort-not found\n");
	for (int r = 0; r < 5; r++) {
		//alpha = 0.8;
		alpha = 0.8;
		n = 0;
		i = 0;
		nf = 0;
		i_n = 0;
		generateRandom(10000);
		for (int i = 0; i < M; i++) {
			table[i] = NULL;
		}
		//	FILLING UP THE HASH TABLE WITH n ELEMENTS
		while ((n / M) < alpha) {
			if (hash_insert(a[i])) {
				n = n + 1;
				i_n++;

			}
			i++;
			if (i >= 10000) {
				generateRandom(10000);
				i = 0;
			}
		}
		// FILLING UP THE not_to_find array
		for (int j = 0; j < 1500; j++) {
			if (!hash_search(a[i])) {
				not_to_find[j] = a[i];
			}
			else {
				j--;
			}
			i++;
			if (i >= 10000) {
				generateRandom(10000);
				i = 0;
			}
		}
		// FILLING UP THE to_find array
		f = 0;
		int index;
		while (f < 1500) {
			index=rand()%M;
			 if (index < 0) index = M - 1;
			printf("%d ", index);
			if (table[index] != NULL) {
				to_find[f] = table[index];
				f++;
			}
			
		}
		max_effort_f = 0;
		avg_effort_f = 0;
		for (int j = 0; j < 1500; j++) {
			OP = 0;
			if (hash_search(to_find[j]) == 0) {
				printf("This should have been found\n");
			}
			else {
				if (OP > max_effort_f) {
					max_effort_f = OP;
				}
				avg_effort_f += OP;
			}
		}
		avg_effort_f = avg_effort_f / 1500;

		max_effort_nf = 0;
		avg_effort_nf = 0;
		for (int j = 0; j < 1500; j++) {
			OP = 0;
			if (hash_search(not_to_find[j]) == 1) {
				printf("This should not have been found\n");
			}
			else {
				if (OP > max_effort_nf) {
					max_effort_nf = OP;
				}
				avg_effort_nf += OP;
			}
		}
		avg_effort_nf = avg_effort_nf / 1500;
		fprintf(out, "%lf, %d, %d, %d, %d\n", alpha, avg_effort_f, max_effort_f, avg_effort_nf, max_effort_nf);

		// alpha = 0.85
		alpha = 0.85;
		n = 0;
		i = 0;
		nf = 0;
		i_n = 0;
		generateRandom(10000);
		for (int i = 0; i < M; i++) {
			table[i] = NULL;
		}
		//	FILLING UP THE HASH TABLE WITH n ELEMENTS
		while ((n / M) < alpha) {
			if (hash_insert(a[i])) {
				n = n + 1;
				i_n++;

			}
			i++;
			if (i > 10000) {
				generateRandom(10000);
				i = 0;
			}
		}
		// FILLING UP THE not_to_find array
		for (int j = 0; j < 1500; j++) {
			if (!hash_search(a[i])) {
				not_to_find[j] = a[i];
				//printf("%d ", j);
			}
			else {
				j--;
			}
			i++;
			if (i > 10000) {
				generateRandom(10000);
				i = 0;
			}
		}
		// FILLING UP THE to_find array
		f = 0;
		while (f < 1500) {
			index = rand() % M;
			if (index < 0) index = M - 1;
			if (table[index] != NULL) {
				to_find[f] = table[index];
				f++;
			}
		}
		max_effort_f = 0;
		avg_effort_f = 0;
		for (int j = 0; j < 1500; j++) {
			OP = 0;
			if (hash_search(to_find[j]) == 0) {
				printf("This should have been found\n");
			}
			else {
				if (OP > max_effort_f) {
					max_effort_f = OP;
				}
				avg_effort_f += OP;
			}
		}
		avg_effort_f = avg_effort_f / 1500;

		max_effort_nf = 0;
		avg_effort_nf = 0;
		for (int j = 0; j < 1500; j++) {
			OP = 0;
			if (hash_search(not_to_find[j]) == 1) {
				printf("This should have been found\n");
			}
			else {
				if (OP > max_effort_nf) {
					max_effort_nf = OP;
				}
				avg_effort_nf += OP;
			}
		}
		avg_effort_nf = avg_effort_nf / 1500;
		fprintf(out, "%lf, %d, %d, %d, %d\n", alpha, avg_effort_f, max_effort_f, avg_effort_nf, max_effort_nf);
		// alpha = 0.9
		alpha = 0.9;
		n = 0;
		i = 0;
		nf = 0;
		i_n = 0;
		generateRandom(10000);
		for (int i = 0; i < M; i++) {
			table[i] = NULL;
		}
		//	FILLING UP THE HASH TABLE WITH n ELEMENTS
		while ((n / M) < alpha) {
			if (hash_insert(a[i])) {
				n = n + 1;
				i_n++;

			}
			i++;
			if (i > 10000) {
				generateRandom(10000);
				i = 0;
			}
		}
		// FILLING UP THE not_to_find array
		for (int j = 0; j < 1500; j++) {
			if (!hash_search(a[i])) {
				not_to_find[j] = a[i];
				//printf("%d ", j);
			}
			else {
				j--;
			}
			i++;
			if (i > 10000) {
				generateRandom(10000);
				i = 0;
			}
		}
		// FILLING UP THE to_find array
		f = 0;
		while (f < 1500) {
			index = rand() % M;
			if (index < 0) index = M - 1;
			if (table[index] != NULL) {
				to_find[f] = table[index];
				f++;
			}
		}
		max_effort_f = 0;
		avg_effort_f = 0;
		for (int j = 0; j < 1500; j++) {
			OP = 0;
			if (hash_search(to_find[j]) == 0) {
				printf("This should have been found\n");
			}
			else {
				if (OP > max_effort_f) {
					max_effort_f = OP;
				}
				avg_effort_f += OP;
			}
		}
		avg_effort_f = avg_effort_f / 1500;

		max_effort_nf = 0;
		avg_effort_nf = 0;
		for (int j = 0; j < 1500; j++) {
			OP = 0;
			if (hash_search(not_to_find[j]) == 1) {
				printf("This should have been found\n");
			}
			else {
				if (OP > max_effort_nf) {
					max_effort_nf = OP;
				}
				avg_effort_nf += OP;
			}
		}
		avg_effort_nf = avg_effort_nf / 1500;
		fprintf(out, "%lf, %d, %d, %d, %d\n", alpha, avg_effort_f, max_effort_f, avg_effort_nf, max_effort_nf);

		//alpha=0.95
		alpha = 0.95;
		n = 0;
		i = 0;
		nf = 0;
		i_n = 0;
		generateRandom(10000);
		for (int i = 0; i < M; i++) {
			table[i] = NULL;
		}
		//	FILLING UP THE HASH TABLE WITH n ELEMENTS
		while ((n / M) < alpha) {
			if (hash_insert(a[i])) {
				n = n + 1;
				i_n++;

			}
			i++;
			if (i > 10000) {
				generateRandom(10000);
				i = 0;
			}
		}
		// FILLING UP THE not_to_find array
		for (int j = 0; j < 1500; j++) {
			if (!hash_search(a[i])) {
				not_to_find[j] = a[i];
				//printf("%d ", j);
			}
			else {
				j--;
			}
			i++;
			if (i > 10000) {
				generateRandom(10000);
				i = 0;
			}
		}
		// FILLING UP THE to_find array
		f = 0;
		while (f < 1500) {
			index = rand() % M;
			if (index < 0) index = M - 1;
			if (table[index] != NULL) {
				to_find[f] = table[index];
				f++;
			}
		}
		max_effort_f = 0;
		avg_effort_f = 0;
		for (int j = 0; j < 1500; j++) {
			OP = 0;
			if (hash_search(to_find[j]) == 0) {
				printf("This should have been found\n");
			}
			else {
				if (OP > max_effort_f) {
					max_effort_f = OP;
				}
				avg_effort_f += OP;
			}
		}
		avg_effort_f = avg_effort_f / 1500;

		max_effort_nf = 0;
		avg_effort_nf = 0;
		for (int j = 0; j < 1500; j++) {
			OP = 0;
			if (hash_search(not_to_find[j]) == 1) {
				printf("This should have been found\n");
			}
			else {
				if (OP > max_effort_nf) {
					max_effort_nf = OP;
				}
				avg_effort_nf += OP;
			}
		}
		avg_effort_nf = avg_effort_nf / 1500;
		fprintf(out, "%lf, %d, %d, %d, %d\n", alpha, avg_effort_f, max_effort_f, avg_effort_nf, max_effort_nf);

		//alpha=0.99
		alpha = 0.99;
		n = 0;
		i = 0;
		nf = 0;
		i_n = 0;
		generateRandom(10000);
		for (int i = 0; i < M; i++) {
			table[i] = NULL;
		}
		//	FILLING UP THE HASH TABLE WITH n ELEMENTS
		while ((n / M) < alpha) {
			if (hash_insert(a[i])) {
				n = n + 1;
				i_n++;

			}
			i++;
			if (i > 10000) {
				generateRandom(10000);
				i = 0;
			}
		}
		// FILLING UP THE not_to_find array
		for (int j = 0; j < 1500; j++) {
			if (!hash_search(a[i])) {
				not_to_find[j] = a[i];
				//printf("%d ", j);
			}
			else {
				j--;
			}
			i++;
			if (i > 10000) {
				generateRandom(10000);
				i = 0;
			}
		}
		// FILLING UP THE to_find array
		f = 0;
		while (f < 1500) {
			index = rand() % M;
			if (index < 0) index = M-1;
			if (table[index] != NULL) {
				to_find[f] = table[index];
				f++;
			}
		}
		max_effort_f = 0;
		avg_effort_f = 0;
		for (int j = 0; j < 1500; j++) {
			OP = 0;
			if (hash_search(to_find[j]) == 0) {
				printf("This should have been found\n");
			}
			else {
				if (OP > max_effort_f) {
					max_effort_f = OP;
				}
				avg_effort_f += OP;
			}
		}
		avg_effort_f = avg_effort_f / 1500;

		max_effort_nf = 0;
		avg_effort_nf = 0;
		for (int j = 0; j < 1500; j++) {
			OP = 0;
			if (hash_search(not_to_find[j]) == 1) {
				printf("This should have been found\n");
			}
			else {
				if (OP > max_effort_nf) {
					max_effort_nf = OP;
				}
				avg_effort_nf += OP;
			}
		}
		avg_effort_nf = avg_effort_nf / 1500;
		fprintf(out, "%lf, %d, %d, %d, %d\n", alpha, avg_effort_f, max_effort_f, avg_effort_nf, max_effort_nf);
	}
	return 0;
}