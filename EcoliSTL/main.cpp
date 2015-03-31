#include <iostream>
#include <string>
#include <new>
#include "allocator.h"
#include "iterator.h"
#include "vector.h"
#include <vector>
#include <set>

#include "UnitTest/123.cpp"




int main(){


	EcoliSTL::vector<int> vec1;



	vec1.insert(vec1.begin (), 10, 10);

	vec1.print();
	
	EcoliSTL::vector<int> vec2 = vec1;

	vec2.print();


	




	std::cout << "ending" << std::endl;
	std::cin.get();
	return 0;
}