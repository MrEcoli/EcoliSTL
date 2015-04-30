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

//base function
void testCase1(){

	EcSTL::unordered_set<int> uset;

	for (int i = 0; i != 100; ++i) {
		uset.insert(rand() % 300);
	}

	for (auto it = uset.begin(); it != uset.end(); ++it) {
		cout << (*it) << " ";
	}
	cout << endl;
}


//test insert, erase;
void testCase2(){

	EcSTL::unordered_set<int> uset;
	cout << uset.empty() << endl;

	for (int i = 0; i != 100; ++i) {
		uset.insert(rand() % 5);
	}

	for (auto it = uset.begin(); it != uset.end(); ++it) {
		cout << (*it) << " ";
	}
	cout << endl;
	cout << uset.size() << endl;

	uset.erase(3);
	for (auto it = uset.begin(); it != uset.end(); ++it) {
		cout << (*it) << " ";
	}
	cout << endl;
	cout << uset.size() << endl;

	cout << uset.empty() << endl;
}


//test size(), empty()
void testCase3(){

	EcSTL::unordered_set<int> uset;
	cout << uset.empty() << endl;

	for (int i = 0; i != 100; ++i) {
		uset.insert(rand() % 5);
	}

	for (auto it = uset.begin(); it != uset.end(); ++it) {
		cout << (*it) << " ";
	}
	cout << endl;
	cout << uset.size() << endl;

	for (int i = 0; i != 5; ++i) {
		uset.erase(i);
	}

	for (auto it = uset.begin(); it != uset.end(); ++it) {
		cout << (*it) << " ";
	}
	cout << endl;
	cout << uset.size() << endl;
	cout << uset.empty() << endl;


}


//test find, erase function
void testCase4(){

	EcSTL::unordered_set<int> uset;

	for (int i = 0; i != 30; ++i) {
		uset.insert(rand() % 10);
	}


	for (auto it = uset.begin(); it != uset.end(); ++it) {
		cout << (*it) << " ";
	}
	cout << endl;

	auto iter = uset.find(3);
	uset.erase(iter);

	for (auto it = uset.begin(); it != uset.end(); ++it) {
		cout << (*it) << " ";
	}
	cout << endl;


}



int main(){

	testCase4();


	cin.get();
	return 0;
}*/