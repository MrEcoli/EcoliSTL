/*
#include "..\vector.h"
#include <iostream>
#include <limits.h>

using std::cout;
using std::endl;

int main(){

	std::cout << "EcSTL vector unit test" << std::endl;
	std::cout << "******************************************" << std::endl;
	//construct function test

	cout << "construct function test" << endl;
	EcSTL::vector<int> vec1(10, 1);
	vec1.print();

	EcSTL::vector<int> vec2(vec1);
	vec2.print();

	EcSTL::vector<int> vec3(3);
	vec3.print();

	std::cout << "******************************************" << std::endl;

	//check insert member function
	cout << "check insert member function" << endl;
	vec1.insert(vec1.begin (), 3, 10);
	vec1.print();
	vec1.insert_aux(vec1.begin() + 2, 321);
	vec1.print();

	cout << "******************************************" << endl;

	//clear function;

	cout << "Test clear function" << endl;

	vec1.clear();
	vec1.print();
	cout << vec1.empty() << endl;
	
	cout << "******************************************" << endl;

	//Test push_back and pop_back operation;

	cout << "Test push_back and pop_back operation;" << endl;

	vec1.push_back(10);
	vec1.print();
	vec1.push_back(INT_MAX);
	vec1.print();
	vec1.push_back(INT_MIN);
	vec1.print();
	vec1.pop_back();
	vec1.print();

	//Test operator == != [] swap func


	cout << "Test //operator == != []" << endl;
	vec1.print();
	vec2.print();
	vec2 = vec1;
	vec1.print();
	vec2.print();

	EcSTL::vector<int> vec4 = vec1;

	vec4.print();
	vec4[0] = 101;
	vec4[1] = 102;
	vec4.print();
	vec4.swap(vec1);

	vec1.print();
	vec4.print();

	cout << "******************************************" << endl;




	


	std::cin.get();
	return 0;
}


*/
