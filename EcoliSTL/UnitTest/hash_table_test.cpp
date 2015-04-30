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
		ht.insert_equal(rand());
	}
	ht.print();
	cout << ht.size();
}


//insert_unique function
void unitTest3(){
	EcSTL::hashtable<int, int, EcSTL::hash<int>, EcSTL::identity<int>, EcSTL::equal_to<int>> ht(1, EcSTL::hash<int>(), EcSTL::equal_to<int>());
	for (size_t i = 0; i < 1000; i++)
	{
		ht.insert_unique(rand());
	}
	ht.print();
	cout << ht.size();
}

//find and count function
void unitTest4(){
	EcSTL::hashtable<int, int, EcSTL::hash<int>, EcSTL::identity<int>, EcSTL::equal_to<int>> ht(1, EcSTL::hash<int>(), EcSTL::equal_to<int>());
	for (size_t i = 0; i < 1000; i++)
	{
		ht.insert_equal(rand() % 100);
	}
	ht.print();
	cout << ht.size() << endl;

	cout << ht.count(25) << endl;

}

//equal_range test; erase; 
void unitTest5(){
	EcSTL::hashtable<int, int, EcSTL::hash<int>, EcSTL::identity<int>, EcSTL::equal_to<int>> ht(1, EcSTL::hash<int>(), EcSTL::equal_to<int>());
	for (size_t i = 0; i < 20; i++)
	{
		ht.insert_equal(rand() % 5);
	}
	ht.print();

	auto retPair = ht.equal_range(3);

	cout << EcSTL::distance(retPair.first, retPair.second);

	cout << "################################  ending  ################################" << endl;

	ht.erase(retPair.first, retPair.second);
	ht.print();

	cout << ht.erase(1) << endl;;
	ht.print();

	for (auto iter = ht.begin(); iter != ht.end(); ++iter) {
		cout << (*iter) << " ";
	}
	cout << endl;

}






// begin(), front ,back function test;
void unitTest6(){
	EcSTL::hashtable<int, int, EcSTL::hash<int>, EcSTL::identity<int>, EcSTL::equal_to<int>> ht(1, EcSTL::hash<int>(), EcSTL::equal_to<int>());
	for (size_t i = 0; i < 1000; i++)
	{
		ht.insert_equal(rand() % 100);
	}
	ht.print();
	cout << ht.size() << endl;

	cout << ht.front() << endl;
	cout << ht.back() << endl;
}


//insert_unique;
void unitTest7(){
	EcSTL::hashtable<int, int, EcSTL::hash<int>, EcSTL::identity<int>, EcSTL::equal_to<int>> ht(1, EcSTL::hash<int>(), EcSTL::equal_to<int>());
	for (size_t i = 0; i < 20; i++)
	{
		ht.insert_unique(rand() % 5);
	}
	ht.print();

	auto retPair = ht.equal_range(3);

	cout << EcSTL::distance(retPair.first, retPair.second);

	cout << "################################  ending  ################################" << endl;

	ht.erase(retPair.first, retPair.second);
	ht.print();

	cout << ht.erase(1) << endl;;
	ht.print();

	for (auto iter = ht.begin(); iter != ht.end(); ++iter) {
		cout << (*iter) << " ";
	}
	cout << endl;

}




int main(){

	unitTest7();



	cin.get();
	return 0;
}*/