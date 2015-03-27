#include <iostream>
#include <string>
#include <new>
#include <vector>
using namespace std;



class X
{
public:
	X(int x) {
		cout << "constructor of X" << endl;
		cout << "init value is " << x << endl;
	}
	~X() { cout << "destructor of X" << endl; }



	void operator delete(void* pointee)
	{
		cout << "operator delete" << endl;
		::operator delete(pointee);
	}

	int getVal(){
		return this->num;
	}

private:
	int num;
};


int f1(){
	cout << "this is function ONE" << endl;

	return 0;
}

int plusx(int a, int b){
	return a + b;
}

int minusx(int a, int b){
	return a - b;
}

int multpyx(int a, int b){
	return a*b;
}

int divx(int a, int b){
	return a / b;
}


int main(){
	//using 语法同样可以达到typedef的效果
	using pf = int(*)(int, int);

	vector<pf> farr = { multpyx, divx, plusx, minusx };

	for (auto f : farr){
		cout << (f(33, 100)) << endl;
	}




	std::cin.get();
	return 0;
}