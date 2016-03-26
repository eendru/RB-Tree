#include <stdio.h>
#include "rbtree.h"

int main() {

	size_t N = 12;
	int i = 0;
	int A[N] = {0};
	srand(time(NULL));
	for (i = 0; i < N; ++i) {
		A[i] = rand() % N + 1;
		std::cout << A[i] << " ";
	}
	std::cout << "\n";

	rb_tree_t *r = create_binary_tree(A, N);
	postorder(r, 0);

	return 0;
}
