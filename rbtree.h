#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>

struct rb_tree_s;
enum rb_color_e {
	RED = 0,
	BLACK = 1,
};

struct rb_tree_s {
	int key;

	rb_tree_s *parent;
	rb_tree_s *left;
	rb_tree_s *right;

	rb_color_e color;
};

typedef rb_tree_s rb_tree_t;
typedef rb_tree_t rb_element_t;

//
void postorder(rb_tree_t* p, int indent)
{
	if(p != NULL) {
		if(p->right)
			postorder(p->right, indent + 4);

		if (indent)
			std::cout << std::setw(indent) << ' ';

		if (p->right)
		    std::cout<<" /\n" << std::setw(indent) << ' ';
		if (p->color == RED)
			std::cout<< p->key << "  RED"  << "\n ";
		else
			std::cout<< p->key << " BLACk " << "\n ";

		if(p->left) {
			std::cout << std::setw(indent) << ' ' <<" \\\n";
			postorder(p->left, indent + 4);
		}
	}
}
//

rb_element_t *create_element(int k) {

	rb_element_t *element = (rb_tree_t*) malloc(sizeof(rb_tree_s));

	element->key = k;
	element->parent = NULL;
	element->left = NULL;
	element->right = NULL;
	element->color = RED;

	return element;
}

rb_tree_t *insert_to_tree(rb_tree_t *T, rb_element_t *z) {

	rb_element_t *y = NULL;
	rb_element_t *x = T;

	while (x != NULL) {
		y = x;
		if (z->key < x->key)
		    x = x->left;
		else
		    x = x->right;
	}

	z->parent = y;
	if (y == NULL)
		T = z;
	else
		if (z->key < y->key)
			y->left = z;
		else
			y->right = z;
	return T;
}

rb_tree_t *rb_left_rotate(rb_tree_t *T, rb_element_t *x) {

	rb_element_t *y;
	y = x->right;
	x->right = y->left;

	if (y->left != NULL)
		y->left->parent = x;
	y->parent = x->parent;

	if(x->parent == NULL) {
		T = y;
	}
	else {
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}

	y->left = x;
	x->parent = y;

	return T;
}

rb_tree_t *rb_right_rotate(rb_tree_t *T, rb_element_t *y) {

	rb_element_t *x;
	x = y->left;
	y->left = x->right;

	if (x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == NULL){
		T = x;
	}
	else {
		if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
	}
	x->right = y;
	y->parent = x;

	return T;
}

rb_tree_t *rb_insert(rb_tree_t *T, rb_element_t *x) {
	T = insert_to_tree(T, x);
	rb_element_t *y = NULL;
	rb_tree_t *t = T;

	while ((x != T) && (x->parent->color == RED)) {

		if(x->parent == x->parent->parent->left)
		{
			y = x->parent->parent->right;
			if (y != NULL && y->color == RED) {
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else {
				if (x == x->parent->right) {
					x = x->parent;
					T = rb_left_rotate(T, x);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				T = rb_right_rotate(T, x->parent->parent);
			}
		}
		else {
				y = x->parent->parent->left;
				if (y != NULL && y->color == RED) {
					x->parent->color = BLACK;
					y->color = BLACK;
					x->parent->parent->color = RED;
					x = x->parent->parent;
				}
				else {
					if (x == x->parent->left) {
						x = x->parent;
						T = rb_right_rotate(T, x);
					}
					x->parent->color = BLACK;
					x->parent->parent->color = RED;
					T = rb_left_rotate(T, x->parent->parent);
				}
		}
	}

	T->color = BLACK;
	return T;
}

rb_tree_t *create_binary_tree(int *A, size_t N) {
	rb_tree_t *result;
	int B[N] = {1, 6, 5, 10, 12, 11, 1, 12, 1, 2, 9, 6};

//	if (N == 0 || A == NULL)
//		return NULL;

	result = create_element(A[0]);
	result->color = BLACK;
	result->parent = 0;


	int i = 1;
	for (i = 1; i < N; ++i) {
		rb_element_t *x = create_element(A[i]);
		result = rb_insert(result, x);
	}

	return result;
}
