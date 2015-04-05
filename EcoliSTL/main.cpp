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
#include <allocators>


int main(){

	//构造函数test
	EcSTL::deque<int> dq_default;
	cout << "constructor Test" << endl;
	EcSTL::deque<int, EcSTL::allocator<int>, 2> dq(3, 10);

	//push_back操作
	dq[0] = 101;
	dq[1] = 1;
	dq[2] = 3;
	dq.push_back(1023);
	dq.push_back(4);
	dq.push_back(4);
	dq.push_back(5);
	dq.push_back(5);
	dq.push_back(6);
	dq.push_back(6);

	dq.print();

	cout << dq.size() << endl;

	//push_front操作


	cout << "\n\npush_font function test\n\n" << endl;

	for (size_t i = 0; i < 5; i++)
	{
		dq.push_front(i);
	}

	cout << dq.size() << endl;

	dq.print();
	
	//pop_front funtion
	cout << "\npop_front function test\n\n" << endl;

	dq.pop_front();
	dq.pop_front();
	dq.pop_front();
	dq.pop_front();
	dq.print();


	//pop_back funtion

	cout << "\n\npop_back funtion test \n" << endl;

	dq.pop_back();
	dq.pop_back();
	dq.pop_back();
	dq.print();

	//clear function

	cout << "\n clear function test\n" << endl;
	dq.clear();
	cout << dq.size() << endl;
	cout << std::boolalpha << dq.empty() << endl;






	
	std::cin.get();
	return 0;
}