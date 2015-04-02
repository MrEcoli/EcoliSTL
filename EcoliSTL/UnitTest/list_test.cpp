/*
#include <iostream>
#include <string>
#include <new>
#include "..\vector.h"
#include "..\functional.h"
#include "..\list.h"
using std::cout;
using std::endl;


int main(){


	EcSTL::greater<int> f;

	//没有数据成员的类的大小为1；
	cout << (sizeof f) << endl;



	//test constuctor 
	EcSTL::list<int> alist, blist(3, 1);


	for (int i = 1; i != 11; ++i) {
		if (i & 1){ alist.push_back(i); }
	}

	for (int i = 1; i != 12; ++i) {
		if (i & 1){ continue; }
		blist.push_back(i);
	}

	alist.print();
	alist.pop_back();
	alist.print();
	blist.print();
	alist.splice(alist.begin(), blist.begin());
	alist.print();

	alist.merge(blist);

	alist.print();

	cout << alist.size() << endl;
	cout << blist.size() << endl;
	cout << *(alist.begin()) << endl;
	cout << alist.front() << endl;
	cout << alist.back() << endl;

	alist.pop_back();
	alist.pop_back();
	alist.pop_back();
	alist.pop_front();
	alist.pop_front();
	alist.pop_front();
	alist.pop_front();

	alist.print();
	blist.push_back(13);
	blist.push_back(123);
	alist.print();
	blist.print();

	alist.swap(blist);

	cout << "after swap" << endl;
	cout << "alist is " << endl;
	alist.print();
	cout << "blist is " << endl;
	blist.print();

	cout << "\n\n" << endl;

	alist.splice(alist.end(), blist);
	alist.print();

	alist.print();
	alist.sort();

	cout << "sorting" << endl;
	alist.print();




	cout << "ending" << endl;
	cout << "*******************************" << endl;


	std::cin.get();
	return 0;
}*/