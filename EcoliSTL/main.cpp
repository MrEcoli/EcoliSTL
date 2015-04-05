#include <iostream>
#include <string>
#include <new>
#include <ctime>
using std::cout;
using std::endl;
#include <allocators>

#include "stack.h"
#include <stack>
#include <queue>
#include "queue.h"

int main(){


	EcSTL::queue<int> que;


	for (int i = 0; i != 100; ++i) {
		que.push(i);
	}

	while (!que.empty()){
		cout << que.front() << endl;
		que.pop();
	}



	std::cin.get();
	return 0;
}