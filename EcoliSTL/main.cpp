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
#include "rb_tree.h"
//base function





int main(){

	EcSTL::rb_tree<int, int, EcSTL::identity<int>, EcSTL::less<int>> rb;


	for (int i = 0; i != 10; ++i) {
		rb.insert_equal(i);
	}

	rb.print_prev();


	auto iter = rb.begin();

	cout << (*iter) << endl;


	for (auto it = rb.begin(); it != rb.end(); ++it) {
		cout << (*it) << endl;
	}



	for (auto it = --rb.end(); it != rb.begin(); --it) {
		cout << (*it) << endl;
	}

	cout << "################ ending ##################" << endl;

	cin.get();
	return 0;
}