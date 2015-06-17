#ifndef _ECSTL_VECTOR_TEST_H
#define _ECSTL_VECTOR_TEST_H
#include "..\vector.h"
#include "..\string.h"


void vector_test_Constructor(){

	printf("************************ vector constructor test ******************\n\n");

	int n = 20;
	EcSTL::vector<int> test_vecs1(n);
	EcSTL::vector<int> tes_vecs2(n, 111);

	EcSTL::string ss = "abc";

	EcSTL::vector<EcSTL::string> test_vecs3(n, ss);
	EcSTL::vector<EcSTL::string> test_vec4(test_vecs3.begin(), test_vecs3.end());
	test_vecs1.print();
	tes_vecs2.print();
	test_vecs3.print();
	test_vec4.print();

	printf("\n\n********************* vector constructor test end *************************\n\n");
	
}

void vector_test_iterator(){

	printf("************************ vector iterator test ******************\n\n");

	int n = 10;
	EcSTL::vector<int> test_vecs;

	for (int i = 0; i != n; ++i) {
		test_vecs.push_back(rand() % 100);
	}

	printf("\norigin vector is \n");

	test_vecs.print();


	printf("\nfront vector is %d\n", (*(test_vecs.begin())));

	printf("\nback element is %d\n\n", (*(test_vecs.end()-1)));
	
	
	auto rfirst = test_vecs.rbegin();
	auto rlast = test_vecs.rend();


	

	while (rfirst != rlast)
		printf("%d ", (*rfirst++));

	
	printf("\n\n********************* vector iterator test end *************************\n\n");
}

void vector_test_motify(){
	printf("************************ vector iterator test ******************\n\n");
	int n = 10;
	EcSTL::vector<int> test_vecs1;

	for (int i = 0; i != n; ++i) {
		test_vecs1.push_back(rand() % 100);
	}

	printf("\norigin vector is \n");

	test_vecs1.print();


	EcSTL::vector<int> test_vecs2(n, 11);


	printf("\nafter insertion of five integer 11 at begin()\n");
	test_vecs1.insert(test_vecs1.begin(), 5, 11);
	test_vecs1.print();

	printf("\nafter insertion of 20 integer 101 at end()\n");
	test_vecs1.insert(test_vecs1.end(), 20, 101);
	test_vecs1.print();

	printf("\nafter insertion of 100 integer 99 at (begin()+2)\n");

	test_vecs1.insert(test_vecs1.begin() + 2, 100, 99);
	test_vecs1.print();



}




void vector_test_all(){
	vector_test_Constructor();
	vector_test_iterator();

}



#endif	//_ECSTL_VECTOR_TEST_H