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

void printVal(int v){
	for (int i = 0; i != v; ++i) {
		cout << "*";
	}
	cout << endl;
}


//test function for d_heap

int main(){

	int arr[] = { 7, 6, 5, 5, 4, 3, 2, 2 };
	EcSTL::vector<int> ivec(arr, arr + 6);


	cout << EcSTL::lower_bound(arr, arr + 8, 2, EcSTL::greater<int>()) - arr << endl;

	cout << EcSTL::upper_bound(arr, arr + 8, 2, EcSTL::greater<int>()) - arr << endl;

	cout << EcSTL::binary_search(arr, arr + 8, 2, EcSTL::greater<int>()) << endl;
	cout << EcSTL::binary_search(arr, arr + 8, 1, EcSTL::greater<int>()) << endl;
	cout << EcSTL::binary_search(arr, arr + 8, 8, EcSTL::greater<int>()) << endl;

	cin.get();
	return 0;
}*/