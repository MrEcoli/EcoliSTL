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
void testCase1(){

	EcSTL::unordered_map<int, int> umap;

	for (int i = 0; i != 10; ++i) {
		umap[i] = i*i;
	}

	for (auto it = umap.begin(); it != umap.end(); ++it) {
		cout << it->first << " " << it->second << endl;
	}

	cout << umap.size() << endl;

	umap.erase(3);
	umap.erase(9);
	umap.erase(0);

	for (auto it = umap.begin(); it != umap.end(); ++it) {
		cout << it->first << " " << it->second << endl;
	}

	cout << umap.size() << endl;

	cout << umap[3] << endl;
	umap[3] = 101;
	cout << umap[3] << endl;

	cout << umap.size() << endl;

}




int main(){

	testCase1();

	cin.get();
	return 0;
}*/