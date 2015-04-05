/*
#include <iostream>
#include <string>
#include <new>
#include "..\deque.h"
#include "..\allocator.h"
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

	auto it = dq.begin();
	cout << *it << endl;
	it++;
	cout << *it << endl;
	it++;
	cout << *it << endl;

	auto it2 = dq.begin() + 2;

	cout << *it2 << endl;
	cout << dq[2] << endl;
	dq[2] = 99;

	cout << dq[2] << endl;

	//insert function


	cout << "\ninsert function test\n\n" << endl;

	dq.insert(dq.begin(), 10);
	dq.print();
	dq.insert(dq.end(), 10);
	dq.print();
	dq.insert(dq.begin() + 2, 20);
	dq.print();


	dq.insert(dq.begin() + 2, 21);
	dq.insert(dq.begin() + 2, 22);
	dq.insert(dq.begin() + 2, 23);
	dq.insert(dq.begin() + 2, 24);
	dq.insert(dq.end() - 1, 33);
	dq.insert(dq.end() - 1, 34);
	dq.insert(dq.end() - 1, 35);
	dq.insert(dq.end() - 1, 36);
	dq.print();

	dq.pop_front();
	dq.pop_front();
	dq.pop_front();
	dq.pop_front();

	dq.pop_back();
	dq.pop_back();
	dq.pop_back();


	dq.print();
	//clear function

	/ *
	cout << "\nclear function test\n" << endl;
	dq.clear();
	cout << dq.size() << endl;
	cout << std::boolalpha << dq.empty() << endl;* /



	//copy function, swap funciton, assignment operator;

	cout << "\n\ncopy function, swap funciton, assignment operator; \n\n" << endl;
	EcSTL::deque<int, EcSTL::allocator<int>, 2> dq3 = dq;

	dq3.print();

	EcSTL::deque<int, EcSTL::allocator<int>, 2> dq4(dq);

	dq4.print();

	EcSTL::deque<int, EcSTL::allocator<int>, 2> dq5(5, 7);

	dq5.swap(dq4);

	dq5.print();
	dq4.print();


	for (int i = 0; i != 100; ++i) {
		dq.push_back(i);
	}

	while (!dq.empty()){
		cout << dq.back() << "  ";
		dq.pop_back();
	}




	std::cin.get();
	return 0;
}*/