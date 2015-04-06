#include <iostream>
#include <string>
#include <new>
#include <ctime>
using std::cout;
using std::endl;
#include "queue.h"
#include "deque.h"

#include "ec_timer.h"
#include <windows.h>


int main(){

	EcSTL::timer t1;
	EcSTL::deque<int> dq;

	t1.startCounter();

	for (int i = 0; i != 1000; ++i) {
		dq.push_back(i);
	}

	while (!dq.empty()){
	/*	cout << dq.back() << " ";*/
		printf("%d ", dq.back());
		dq.pop_back();
	}

	t1.endCounter();

	cout << t1.getCounter() << endl;


	std::cin.get();
	return 0;
}