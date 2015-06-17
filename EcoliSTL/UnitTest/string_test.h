#pragma once
#ifndef _STRING_TEST_CPP
#define _STRING_TEST_CPP
#include <iostream>
#include <new>
#include <vector>
#include <ctime>
#include "..\string.h"
using std::cout;
using std::cin;
using std::endl;

using EcSTL::string;

//base function

void testConstructor(){

	string s0;
	string s1 = "operator = function test ";
	string s2('h');
	string s3('o', 10);

	string s4("hello world");
	string s5("four", 4);

	//move constuctor
	string s6(string("this is move constructor"));
	string s7(s3);


	cout << "default function " << s0 << endl;
	cout << "opeator= function  " << s1 << endl;
	cout << "Single Charctor constructor function      " << s2 << endl;
	cout << "Multiple Charctor constructor function   " << s3 << endl;
	cout << "inline basic_string(const _Char_t* _x);   " << s4 << endl;
	cout << "inline basic_string(const _Char_t* _x, size_type n);   " << s5 << endl;
	cout << "rvalue move constructor function   " << s6 << endl;
	cout << "copy function " << s7 << endl;
}


void testStatus(){

	std::cout << "******************* test Status function **********************" << std::endl;
	string s0;
	string s1 = "hello world";
	string s2(s1);
	string s4(s1);
	cout << "size of empty string is  " << s0.size() << endl;
	cout << "capcity of empty string is  " << s0.capacity() << endl;

	cout << "size of hello world is " << s1.size() << endl;
	cout << "capcity of hello world is " << s1.capacity() << endl;

	cout << "empty function on emtpty string " << s0.empty() << endl;
	cout << "empty function on non-empty string " << s1.empty() << endl;


	cout << endl;
	cout << "after resize" << endl;
	s1.resize(3);

	cout << s1 << endl;
	cout << s1.size() << endl;
	cout << s1.capacity() << endl;

}


void testCopyOnWrite(){
	string s0;
	string s1 = "hello world";
	string s2(s1);
	const string s3(s2);
	string s4(s1);
	const string s5(s1);
	string s6(s0);

	std::cout << "****************** Test copy on write ******************************" << std::endl;
	std::cout << "before write opeation, these string using the same heap area" << std::endl;
	std::cout << (int*)(s1.data()) << std::endl;
	std::cout << (int*)(s2.data()) << std::endl;
	std::cout << (int*)(s3.data()) << std::endl;
	std::cout << (int*)(s4.data()) << std::endl;
	std::cout << (int*)(s5.data()) << std::endl;

	s2[0];
	s3[0];
	s4.at(0);
	s5.at(0);

	std::cout << "no const string operator " << (int*)(s2.data()) << std::endl;
	std::cout << "const string operator    " << (int*)(s3.data()) << std::endl;
	std::cout << "no const string operator " << (int*)(s4.data()) << std::endl;
	std::cout << "const string operator    " << (int*)(s5.data()) << std::endl;
}




void testOperator(){
	std::cout << "****************** test Operator *****************" << std::endl;
	string s1('h', 4);
	string s2('h', 10);
	string s3(s1);
	string s4("hhhh");
	string s5("hello world");


	std::cout << s1 << " == " << s2 << " is " << (s1 == s2) << std::endl;

	std::cout << s1 << " == " << s3 << " is " << (s1 == s3) << std::endl;

	std::cout << s4 << " == " << s1 << " is " << (s1 == s4) << std::endl;

	std::cout << s1 << " == " << s5 << " is " << (s1 == s5) << std::endl;

	s1 += s2;
	s2 = s3 + s5;
	cout << s1 << endl;
	cout << s2 << std::endl;

}



void testSubstr(){
	string s1 = "hello_world";

	std::cout << s1 << std::endl;
	std::cout << s1.substr() << std::endl;
	std::cout << s1.substr(1) << std::endl;
	std::cout << s1.substr(2) << std::endl;
	std::cout << s1.substr(2, 2) << std::endl;
	std::cout << s1.substr(2, 4) << std::endl;


}


void testErase(){

	string s1 = "hello_world!";

	s1.erase(s1.begin());

	cout << s1 << endl;

	s1.erase(s1.begin(), s1.begin() + 2);

	cout << s1 << endl;

	s1.erase(2);

	cout << s1 << endl;

	string s2 = s1.erase(2, 2);

	cout << s1 << endl;
	cout << s2 << endl;
}


void testAppend(){

	std::cout << "*************** test append *************************" << std::endl;
	string s1 = "hello";
	string s2 = "world";
	string s3(s1);
	string s4(s1);

	cout << s1.append(s2) << endl;
	cout << s3.append(s1) << endl;
	cout << s3.append(s1) << endl;
	cout << s3.append("ddasdd").append(s3) << endl;
	cout << s3.append('0') << endl;
	cout << s3.append('1', 40) << endl;
	cout << s3.append('1', 40) << endl;

}




void testAll(){
	testConstructor();
	testCopyOnWrite();
	testErase();
	testOperator();
	testStatus();
	testSubstr();
	testAppend();
}

#endif // !_STRING_TEST_CPP
