#ifndef _ALGORITHM_TEST_H
#define _ALGORITHM_TEST_H
#include "construct.h"
#include "..\vector.h"
#include "_type_trait.h"
#include "..\functional.h"

void algorithm_testCopy(){

	
	printf("\n*********************** test algorithm function copy  **********************\n\n");

	int n = 20;

	EcSTL::vector<int> test_vecs1(n);
	EcSTL::vector<int> test_vecs2(n);

	for (auto v = test_vecs1.begin(); v != test_vecs1.end();++v) {
		*v = rand()%100;
	}

	EcSTL::copy(test_vecs1.begin(), test_vecs1.end(), test_vecs2.begin());

	for (auto v:test_vecs1) {
		printf("%d  ", v);
	}
	printf("\n");

	for (auto v:test_vecs2) {
		printf("%d  ", v);
	}
	printf("\n");
	printf("\n");
	printf("\n");
	printf ("test_vecs1 == test_vecs2 is %d" ,(test_vecs2 == test_vecs1) );
		
	printf("\n\n*********************** copy test end **********************\n\n");
}

void print_arr(int arr[], int n){
	for (int i = 0; i < n;++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void algorithm_test_equal(){
	
	printf("\n*********************** test algorithm function equal  **********************\n");
	int arr1[] = { 1, 2, 3, 4 };
	int arr2[] = { 1, 2, 3, 4 };
	int arr3[] = { 1 };
	int arr4[] = { 1, 2, 3, 4, 5, 6, 7 };
	int arr5[] = { 133, 12};
	printf("arr1 is "), print_arr(arr1, sizeof(arr1) / sizeof(int));
	printf("arr2 is "), print_arr(arr2, sizeof(arr2) / sizeof(int));
	printf("arr3 is "), print_arr(arr3, sizeof(arr3) / sizeof(int));
	printf("arr4 is "), print_arr(arr4, sizeof(arr4) / sizeof(int));
	printf("arr5 is "), print_arr(arr5, sizeof(arr5) / sizeof(int));

	printf("\n\n");
	printf("equal arr1 arr2 %d\n", EcSTL::equal(arr1, arr1 + 4, arr1));
	printf("equal arr1 arr2 %d\n", EcSTL::equal(arr1, arr1 + 4, arr2));
	printf("equal arr1 arr3 %d\n", EcSTL::equal(arr1, arr1 + 4, arr3));
	printf("equal arr1 arr4 %d\n", EcSTL::equal(arr1, arr1 + 4, arr4));
	printf("equal arr1 arr5 %d\n", EcSTL::equal(arr1, arr1 + 4, arr5));
	printf("\n\n");
	printf("\n*********************** euqal test end **********************\n");
}


void algorithm_test_accumulate(){

	printf("\n*********************** test algorithm function accumulate  *********************\n\n");
	EcSTL::vector<int> test_vec;

	for (int i = 1; i != 6; ++i) {
		test_vec.push_back(i);
	}

	for (auto v : test_vec) {
		printf("%d ", v);
	}
	printf("\n");

	int ret1 = EcSTL::accumulate(test_vec.begin(), test_vec.end(), 0);
	int ret2 = EcSTL::accumulate(test_vec.begin(), test_vec.end(), 0, EcSTL::minus<int>());
	double ret3 = EcSTL::accumulate(test_vec.begin(), test_vec.end(), 1.0, EcSTL::divides<double>());
	int ret4 = EcSTL::accumulate(test_vec.begin(), test_vec.end(), 1, EcSTL::multiplies<int>());
	printf("accumulate with plus is %d\n", ret1);
	printf("accumulate with minus is %d\n", ret2);
	printf("accumulate with divides is %lf\n", ret3);
	printf("accumulate with multiples is %lf\n", ret4);


	printf("\n\n*********************** euqal test end **********************\n");
}


void algorithm_test_find_count(){
	printf("\n*********************** test algorithm function find count **********************\n\n");

	int arr[] = { 1, 2, 3, 5, 2, 12, 3, 5, 11 };

	int n = sizeof(arr) / sizeof(int);
	
	printf("arr: { ");
	for (auto v :arr) {
		printf("%d, ", v);
	}
	printf("}\n\n");

	auto it = EcSTL::find(arr, arr + n, 11);

	printf("find 11 in arr is %d\n\n", (it != (arr + n)));

	printf("find 12 in arr is %d\n\n", ((arr +n) != EcSTL::find (arr, arr+n, 12)));

	printf("find 112 in arr is %d\n\n", (EcSTL::find (arr, arr+n, 112) != (arr + n)));

	
	printf("find if v < 0 is %d\n\n", (EcSTL::find_if(arr, arr + n, [](int v){ return v < 0; }) != arr + n));

	printf("find if v == 12 is %d is \n\n", (EcSTL::find_if(arr, arr + n, [](int v) {return v == 12; }) != arr + n));
	printf("find if v > 12 is %d\n\n", (EcSTL::find_if(arr, arr + n, [](int v) {return v > 12; }) != arr + n));

	printf("count of 3 is %d \n\n", (EcSTL::count_if(arr, arr + n, [](int v){return v == 3; })));
	printf("count of 12 is %d \n\n", (EcSTL::count_if(arr, arr + n, [](int v){return v == 12; })));
	printf("count of 100 is %d \n\n", (EcSTL::count_if(arr, arr + n, [](int v){return v == 100; })));
	

	printf("\n*********************** find count test end **********************\n");


	
}


void algorithm_test_binary_search_function(){
	
	printf("\n********************* test algorithm function Binary search function  ********************\n");
	EcSTL::vector<int> test_vec;
	for (int i = 0; i != 10; ++i) {
		test_vec.push_back(rand() % 35);
	}

	printf("origin vector is \n");
	test_vec.print();

	EcSTL::sort(test_vec.begin(), test_vec.end());
	test_vec.print();

	auto if_find = EcSTL::binary_search(test_vec.begin(), test_vec.end(), 11);

	printf("\nbinary_search for 11 is %d", (if_find));

	if_find = EcSTL::binary_search(test_vec.begin(), test_vec.end(), 9);
	printf("\nbinary_search for 9 is %d", (if_find));

	printf("\n\nsort vector with greater<int>, vector is \n");
	EcSTL::sort(test_vec.begin(), test_vec.end(), EcSTL::greater<int>());
	test_vec.print();

	
	if_find = EcSTL::binary_search(test_vec.begin(), test_vec.end(), 9, EcSTL::greater<int>());
	printf("\nbinary_search for 9 is %d", (if_find));
	
	
	if_find = EcSTL::binary_search(test_vec.begin(), test_vec.end(), 11, EcSTL::greater<int>());
	printf("\nbinary_search for 11 is %d", (if_find));


	printf("\n********************* binary_search  test end **********************\n");
}


void algorithm_test_upper_lower_bound(){

	printf("\n********************* test algorithm function upper_bound and lower_bound function  ********************\n");
	EcSTL::vector<int> test_vec;
	for (int i = 0; i != 20; ++i) {
		test_vec.push_back(rand() % 15);
	}

	printf("origin vector is \n");
	test_vec.print();

	EcSTL::sort(test_vec.begin(), test_vec.end());
	printf("\n after default sort (less<int>)\n");
	test_vec.print();

	auto pos1 = EcSTL::lower_bound(test_vec.begin(), test_vec.end(), 10);

	printf("\n\nlower_bound search for 10, pos is %d\n", (pos1 - test_vec.begin()));

	auto pos2 = EcSTL::upper_bound(test_vec.begin(), test_vec.end(), 10);

	printf("\n\nupper_bound search for 10, pos is %d\n", (pos2 - test_vec.begin()));

	printf("\n\nelement numebr of 10 is %d\n", (pos2 - pos1));

	EcSTL::sort(test_vec.begin(), test_vec.end(), EcSTL::greater<int>());
	
	printf("\n\nafter sort with greater<int>\n");
	test_vec.print();

	pos1 = EcSTL::lower_bound(test_vec.begin(), test_vec.end(), 12, EcSTL::greater<int>());
	pos2 = EcSTL::upper_bound(test_vec.begin(), test_vec.end(), 12, EcSTL::greater<int>());

	printf("\n\nlower_bound search for 12 with greater<int>, pos1 is %d\n", (pos1 - test_vec.begin()));
	printf("\n\nupper_bound search for 12 with greater<int>, pos2 is %d\n", (pos2 - test_vec.begin()));

	printf("\n\nelement numebr of 12 is %d\n", (pos2 - pos1));
	
	printf("\n********************* upper lower bound  test end **********************\n");

}


void algorithm_test_sort_partition(){
	
	printf("\n********************* test algorithm function sort partition  ********************\n");
	EcSTL::vector<int> test_vec;
	for (int i = 0; i != 10; ++i) {
		test_vec.push_back(rand() % 30);
	}

	printf("origin vector is \n");
	test_vec.print();

	printf("\nafter partition with front: %d\n", test_vec.front ());
	EcSTL::partition(test_vec.begin(), test_vec.end(), EcSTL::bind2nd(EcSTL::less_equal<int>(), test_vec.front()));
	test_vec.print();

	printf("\nafter partition with back: %d\n", test_vec.back ());
	EcSTL::partition(test_vec.begin(), test_vec.end(), EcSTL::bind2nd(EcSTL::greater_equal<int>(), test_vec.front()));
	test_vec.print();


	printf("\nsort with default less<int> is \n");
	EcSTL::sort(test_vec.begin(), test_vec.end());
	test_vec.print();


	printf("\nafter sort with greater<int> is \n");
	EcSTL::sort(test_vec.begin(), test_vec.end(), EcSTL::greater<int>());
	test_vec.print();
		
	printf("\n********************* sort parition test end **********************\n");

}





void algorithm_test_all(){
	algorithm_testCopy();
	algorithm_test_equal();
	algorithm_test_accumulate();
	algorithm_test_binary_search_function();
	algorithm_test_upper_lower_bound();
	algorithm_test_sort_partition();
}




#endif //_ALGORITHM_TEST_H