#include <iostream>
#include <string>
#include <new>
#include <vector>
#include <ctime>
using std::cout;
using std::cin;
using std::endl;
#include "vector.h"
#include "algorithm.h"
#include "priority_queue.h"
#include <random>
#include "d_heap.h"
#include <algorithm>
#include "hashtable.h"
#include "stl_hash_function.h"
#include <stdlib.h>
#include "unordered_set.h"
#include "unordered_map.h"
//base function

enum color{
	Red = 0,
	Black = 1
};

struct rb_node{
	int val;
	rb_node* left;
	rb_node* right;
	rb_node* parent;
	bool color;
	rb_node() :left(nullptr), right(nullptr), parent(nullptr), color(Black){}
	rb_node(int v) :val(v), left(nullptr), right(nullptr), parent(nullptr), color(Black){}
};


typedef rb_node* pNode;

void print_rb_tree(pNode root){
	if (root){
		print_rb_tree(root->left);
		cout << root->val << " ";
		print_rb_tree(root->right);
	}
}

void left_rotate(pNode current_node){
	if (current_node->right){
		pNode node_a = current_node;
		pNode node_b = node_a->right;
		node_a->right = node_b->left;
		if (node_b->left){
			node_b->left->parent = node_a;
		}
		node_b->parent = node_a->parent;
		if (node_a->parent){
			if (node_a == node_a->parent->left){
				node_a->parent->left = node_b;
			}
			else{
				node_a->parent->right = node_b;
			}
		}
		node_a->parent = node_b;
		node_b->left = node_a;
	}
}


void right_ratate(pNode current_node){
	if (current_node->left){
		pNode node_a = current_node;
		pNode node_b = current_node->left;

		node_a->left = node_b->right;
		if (node_b->right){
			node_b->right->parent = node_a;
		}
		node_b->parent = node_a->parent;
		if (node_a->parent){
			if (node_a == node_a->parent->left){
				node_a->parent->left = node_b;
			}
			else
			{
				node_a->parent->right = node_b;
			}
		}
		node_b->right = node_a;
		node_a->parent = node_b;
	}
}

void insert(pNode root, int val){
	if (root){
		root = new rb_node(val);
		root->color = Black;
		return;
	}

	pNode cur = root;
	pNode prev = nullptr;
	while (cur) {
		prev = cur;
		if (val < cur->val){
			cur = cur->left;
		}
		else
		{
			cur = cur->right;
		}
	}

	if (val < prev->val){
		prev->left = new rb_node(val);
		prev->left->parent = prev;
		prev->left->color = Red;
	}
	else{
		prev->right = new rb_node(val);
		prev->right->parent = prev;
		prev->right->color = Red;
	}

	if (prev->color == Red){
		insert_balance_rbtree(p);
	}

}






int main(){

	rb_node root;
	root.val = 10;

	print_rb_tree(&root);

	cin.get();
	return 0;
}