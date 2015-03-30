#include <iostream>
#include <string>
#include <new>
#include "allocator.h"
#include "iterator.h"
#include "vector.h"
#include <vector>
#include <set>

class Base{
public:

	Base(){
		std::cout << "constructing" << std::endl;
		val = st_val++;
		std::cout << val << std::endl;
	}

	Base(const Base &others){
		std::cout << "copy function" << std::endl;
		val = st_val++;
	}

	~Base(){
		std::cout << "destroying " << val << std::endl;
	}
	static int st_val;

	bool operator<(const Base& rhs)const{

		return this->val < rhs.val;
	}


	int val;
};

int Base::st_val = 1;

int main(){


	std::vector<Base> vec(4);
	std::set<Base> s;

	s.insert(Base()); s.insert(Base()); s.insert(Base()); s.insert(Base());

	for (auto iter = s.begin(); iter != s.end(); ++iter) {
		std::cout << iter->val << std::endl;
	}







	std::cout << "-------------" << std::endl;







	std::cout << "ending" << std::endl;
	std::cin.get();
	return 0;
}