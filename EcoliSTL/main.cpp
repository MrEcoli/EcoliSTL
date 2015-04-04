#include <iostream>
#include <string>
#include <new>
#include "vector.h"
#include "functional.h"
#include "list.h"
#include "deque.h"
#include "allocator.h"
using std::cout;
using std::endl;


int main(){

	//构造函数test
	EcSTL::deque<int> dq_default;
	cout << "构造函数 Test" << endl;
	EcSTL::deque<int, EcSTL::allocator<int>, 2> dq(3, 10);
	dq[1] = 1;
	dq[2] = 3;
	dq[0] = 101;
	dq.push_back(1023);

	for (auto it = dq.begin(); it != dq.end(); ++it) {
		cout << *it << endl;
	}


	
	
	std::cin.get();
	return 0;
}