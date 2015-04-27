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

void printVal(int v){
	for (int i = 0; i != v; ++i) {
		cout << "*";
	}
	cout << endl;
}


//test function for d_heap

int main(){

	int arr[] = { 34, 1, 33, 5, 7, 4 };

	EcSTL::dheap_pq<int, 4, EcSTL::vector<int>, EcSTL::greater<int>> pq;

	for (int i = 0; i != 50; ++i) {
		pq.push(rand() % 50);
	}


	pq.print();
	cout << pq.size();
	cout << endl;

	while (!pq.empty()){
		cout << pq.front() << endl;
		pq.pop();
	}

	cout << pq.size() << endl;


	cin.get();
	return 0;
}*/