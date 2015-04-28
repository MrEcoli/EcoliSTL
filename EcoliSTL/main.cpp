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
void printVal(int v){
	for (int i = 0; i != v; ++i) {
		cout << "*";
	}
	cout << endl;
}


//test function for d_heap

void unitTest1(){
	int arr[] = { 7, 6, 5, 5, 4, 3, 2, 2 };

	EcSTL::hashtable<int, int, EcSTL::hash<int>, EcSTL::identity<int>, EcSTL::equal_to<int>> ht(1, EcSTL::hash<int>(), EcSTL::equal_to<int>());

	for (size_t i = 0; i < 8; i++)
	{
		ht.insert_unique(i);
	}

	ht.print();
}


void unitTest2(){
	EcSTL::hashtable<int, int, EcSTL::hash<int>, EcSTL::identity<int>, EcSTL::equal_to<int>> ht(1, EcSTL::hash<int>(), EcSTL::equal_to<int>());
	for (size_t i = 0; i < 1000; i++)
	{
		ht.insert_equal(rand ());
	}
	ht.print();
	cout << ht.size();
}

void unitTest2(){
	EcSTL::hashtable<int, int, EcSTL::hash<int>, EcSTL::identity<int>, EcSTL::equal_to<int>> ht(1, EcSTL::hash<int>(), EcSTL::equal_to<int>());
	for (size_t i = 0; i < 1000; i++)
	{
		ht.insert_unique(rand());
	}
	ht.print();
	cout << ht.size();
}






int main(){

	unitTest2();



	cin.get();
	return 0;
}