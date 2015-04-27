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


void printVal(int v){
	for (int i = 0; i != v; ++i) {
		cout << "*";
	}
	cout << endl;
}


int main(){

	int arr[] = { 34, 1, 33, 5, 7, 4 };

	EcSTL::priority_queue<int, EcSTL::vector<int>, EcSTL::greater<int>> pq;

	for (int i = 0; i != 30; ++i) {
		pq.push(rand() % 60);
	}


	pq.print();
	while (!pq.empty()){
		int val = pq.front();
		printVal(val);
		pq.pop();
	}


	//EcSTL priority_queue is compatible with std::vector;
	EcSTL::priority_queue<int, std::vector<int>, EcSTL::greater<int>> pq2(arr, arr + sizeof(arr) / sizeof(int));


	while (!pq2.empty()) {
		printVal(pq2.front());
		pq2.pop();
	}








	cin.get();
	return 0;
}*/