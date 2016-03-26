#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>

struct RB_tree_s;

struct RB_tree_s {
	int key;
	RB_tree_s *parent;
	RB_tree_s *left;
	RB_tree_s *right;	
};

typedef RB_tree_s RB_tree_t;
typedef RB_tree_t RB_element_t;

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
//
void postorder(RB_tree_t* p, int indent)
{
	if(p != NULL) {
		if(p->right) 
			postorder(p->right, indent + 4);
		
		if (indent) 
			std::cout << std::setw(indent) << ' ';
		
		if (p->right)
		    std::cout<<" /\n" << std::setw(indent) << ' ';
		
		std::cout<< p->key << "\n ";
		if(p->left) {
			std::cout << std::setw(indent) << ' ' <<" \\\n";
			postorder(p->left, indent + 4);
		}
	}
}

//




RB_element_t *create_element(int k) {
	
	RB_element_t *element = (RB_tree_t*) malloc(sizeof(RB_tree_s));

	element->key = k;
	element->parent = NULL;
	element->left = NULL;
	element->right = NULL;

	return element;
}

void insert_to_tree(RB_tree_t *T, int k) {
	RB_element_t *z = create_element(k);

	RB_element_t *y = NULL;
	RB_element_t *x = T;

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
}


RB_tree_t *create_binary_tree(int *A, size_t N) {
	RB_tree_t *result;
	if (N == 0 || A == NULL)
		return NULL;

	result = create_element(A[0]);

	int i = 0;
	for (i = 0; i < N; ++i) {
		insert_to_tree(result, A[i]);		
	}

	return result;
}
