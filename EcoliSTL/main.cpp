#include <iostream>
#include <string>
#include <new>
#include <ctime>
using std::cout;
using std::cin;
using std::endl;
#include "vector.h"
#include "algorithm.h"

int main(){


	int arr[] = { 7, 5, 3, 6, 1, 5, 2 };

	EcSTL::vector<int> ivec(arr, arr + 7);

	ivec.print();

	EcSTL::make_heap(ivec.begin(), ivec.end());

	ivec.print();

	EcSTL::pop_heap(ivec.begin(), ivec.end());

	ivec.print();

	EcSTL::push_heap(ivec.begin(), ivec.end());

	ivec.print();

	cin.get();
	return 0;
}