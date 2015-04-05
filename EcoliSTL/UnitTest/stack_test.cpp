/*
#include <iostream>
#include <string>
#include <new>
#include <ctime>
using std::cout;
using std::endl;
#include <allocators>

#include "..\stack.h"
#include <stack>

int main(){

	EcSTL::stack<int> istack;
	std::stack<int> std_stack;
	long long tcost1, tcost2;

	time_t start1, end1, start2, end2;

	start1 = clock();
	for (int i = 0; i != 10000; ++i) {
		istack.push(i);
	}

	while (!istack.empty()){
		cout << istack.top() << " ";
		istack.pop();

	}

	end1 = clock();

	start2 = clock();

	for (int i = 0; i != 10000; ++i) {
		std_stack.push(i);
	}

	while (!std_stack.empty()){
		cout << std_stack.top() << " ";
		std_stack.pop();

	}

	end2 = clock();


	cout << end1 - start1 << endl;

	cout << end2 - start2 << endl;



	std::cin.get();
	return 0;
}*/