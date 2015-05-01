/*
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
	int color;
	rb_node() :left(nullptr), right(nullptr), parent(nullptr), color(Black){}
	rb_node(int v) :val(v), left(nullptr), right(nullptr), parent(nullptr), color(Black){}
};

size_t max(size_t a, size_t b){
	return a > b ? a : b;
}

typedef rb_node* pNode;

void rb_insert(pNode &root, int val);
void insert_rebalance(pNode &root, pNode cur);
void print_rb_tree(pNode root);
void right_ratate(pNode &root, pNode current_node);
void left_rotate(pNode &root, pNode current_node);

void print_rb_tree(pNode root){
	if (root){
		print_rb_tree(root->left);
		cout << root->val << " ";
		print_rb_tree(root->right);
	}
}

void left_rotate(pNode &root, pNode current_node){
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
		else{
			root = node_b;
		}
		node_a->parent = node_b;
		node_b->left = node_a;
	}
}


void right_ratate(pNode &root, pNode current_node){
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
		else{
			root = node_b;
		}
		node_b->right = node_a;
		node_a->parent = node_b;
	}
}

void rb_insert(pNode &root, int val){
	if (!root){
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
		if (prev->color == Red){
			insert_rebalance(root, prev->left);
		}
	}
	else{
		prev->right = new rb_node(val);
		prev->right->parent = prev;
		prev->right->color = Red;
		if (prev->color == Red){
			insert_rebalance(root, prev->right);
		}
	}

}

void insert_rebalance(pNode& root, pNode cur){
	while (cur->parent && cur->parent->color == Red){
		if (cur->parent == cur->parent->parent->left){
			if (cur->parent->parent->right && cur->parent->parent->right->color == Red){ //case 1
				cur->parent->color = Black;
				cur->parent->parent->color = Red;
				cur->parent->parent->right->color = Black;
				cur = cur->parent->parent;
			}
			else{
				if (cur == cur->parent->left){											//case 2
					cur->parent->color = Black;
					cur->parent->parent->color = Red;
					right_ratate(root, cur->parent->parent);
					break;
				}
				else{																	//case 3
					cur = cur->parent;
					left_rotate(root, cur);
				}
			}
		}
		else
		{
			if (cur->parent->parent->left && cur->parent->parent->left->color == Red){
				cur->parent->color = Black;
				cur->parent->parent->color = Red;
				cur->parent->parent->left->color = Black;
				cur = cur->parent->parent;
			}
			else
			{
				if (cur == cur->parent->right){
					cur->parent->color = Black;
					cur->parent->parent->color = Red;
					left_rotate(root, cur->parent->parent);
					break;
				}
				else
				{
					cur = cur->parent;
					right_ratate(root, cur);
				}
			}
		}
		root->color = Black;
	}
	root->color = Black;
}

size_t deep_of_tree(pNode root){
	if (!root){
		return 0;
	}

	return max(deep_of_tree(root->left), deep_of_tree(root->right)) + 1;
}


pNode getBegin(pNode cur){
	while (cur->left) {
		cur = cur->left;
	}
	return cur;
}

pNode getEnd(pNode cur){
	while (cur->right) {
		cur = cur->right;
	}
	return cur;
}

size_t blackheight(pNode cur){
	size_t bheight = 0;

	while (cur) {
		if (cur->color == Black){
			++bheight;
		}
		cur = cur->parent;
	}
	return bheight;
}


void print_rb_tree_v2(pNode _x){
	while (_x) {
		print_rb_tree_v2(_x->left);
		cout << _x->val << " ";
		_x = _x->right;
	}
}




int main(){

	pNode root = new rb_node(10);

	for (int i = 0; i != 100; ++i) {
		rb_insert(root, i);
	}

	print_rb_tree_v2(root);

	cout << endl;

	cout << deep_of_tree(root->left) << endl;
	cout << deep_of_tree(root->right) << endl;


	cout << blackheight(getBegin(root)) << endl;
	cout << blackheight(getEnd(root)) << endl;





	cin.get();
	return 0;
}*/