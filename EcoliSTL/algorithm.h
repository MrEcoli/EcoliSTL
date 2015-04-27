#ifndef _ECOLISTL_ALGORITHM_H
#define _ECOLISTL_ALGORITHM_H
#include <xutility>
#include "iterator.h"



namespace EcSTL{
	template<class InputIterator, class OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator out){
		for (; first != last; ++first, ++out) {
			*out = *first;
		}
		return out;
	}


	template<class ForwardIterator1, class  ForwardIterator2>
	bool equal(ForwardIterator1 first, ForwardIterator2 last, ForwardIterator2 others){
		for (; first != last; ++others, ++first) {
			if (*first != *others){
				return false;
			}
		}
		return true;
	}

	template<class T>
	void swap(T& lhs, T& rhs){
		T tmp = (std::move(lhs));
		lhs = std::move(rhs);
		rhs = std::move(tmp);
	}

	//source area is [first, last), target area is [result - (last - first), result);
	//return (result - (last - first));
	template<class BidrecIterator1, class BidrecIterator2>
	BidrecIterator2 copy_reverse(BidrecIterator1 first, BidrecIterator1 last, BidrecIterator2 result){
		--last; --result;

		for (; first <= last; --last, --result) {
			*result = *last;
		}
		return result;
	}

	template<class T, class Cmp = greater<T>>
	T& max(const T& v1, const T& v2){

		Cmp cp = Cmp();

		if (cp(v1, v2)){
			return v1;
		}
		else{
			return v2;
		}
	}








	//make_heap support random_access_iterator
	//default version use less<T>();
	/*
			node(n)
			/  \
		   /    \
		  /      \
	  n*2+1      n*2 +2
		 
	son = n ==> father = (n -1) /2;

	*/

	template<class Iterator>
	void make_heap(Iterator first, Iterator last){
		typedef int difference_type;
		difference_type n = (last - first);

		if (n == 0 || n == 1){
			return;
		}

		difference_type mid = (n - 2) >> 1;
		if (n && 1 == 0){
			if (*(last - 1) < *(first + mid)){
				swap(*(last - 1), *(first + mid));
			}
			mid--;
		}

		for (difference_type cur_pos = mid; cur_pos >= 0; --cur_pos) {
			adjustNode(first, cur_pos, n);
		}
	}

	//adjust node of heap
	//default function is less<T>
	template<class Iterator>
	void adjustNode(Iterator start,  int pos, int n){
		Iterator father = start + pos;
		Iterator left_son = start + pos * 2 + 1;
		Iterator right_son = start + pos * 2 + 2;
		Iterator last = start + n;
		if (left_son >= last){
			return;
		}

		if (right_son == last){
			if (*left_son < *father){
				swap(*left_son, *father);
				return;
			}
		}

		if (*left_son < *father && *left_son <= *right_son){
			swap(*left_son, *father);
			adjustNode(start, pos * 2 + 1, n);
			return;
		} else if (*right_son < *father && *right_son <= *left_son){
			swap(*right_son, *father);
			adjustNode(start, pos * 2 + 2, n);
			return;
		}

	}
	
	//adjust heap after push operation
	//time complexity O(logn)
	template<class Iterator>
	void push_heap(Iterator first, Iterator last){
		typedef int difference_type;
		difference_type n = last - first;

		if (n == 1 && n == 0){
			return;
		}

		difference_type cur_pos = n - 1;
		difference_type parent = (cur_pos - 1) >> 1;
		while (cur_pos != 0 && *(first + cur_pos) < *(first +parent)) {
			swap(*(first + cur_pos), *(first + parent));
			cur_pos = parent;
			parent = (cur_pos - 1) >> 1;
		}
	}

	//functions for heap with two parameter
	template<class Iterator, class Cmp>
	void adjustNode(Iterator start, int pos, int n, Cmp cmpfunc){
		int left = pos * 2 + 1;
		int right = pos * 2 + 2;
		int choices = pos;
		

		if (left < n && cmpfunc(*(start + left), *(start + pos))){
			choices = left;
		}

		if (right < n && cmpfunc(*(start + right), *(start + choices))){
			choices = right;
		}

		if ( choices != pos){
			swap(*(start + choices), *(start + pos));
			adjustNode(start, choices, n, cmpfunc);
		}
	}


	template<class Iterator, class Cmp>
	void make_heap(Iterator first, Iterator last, Cmp cmpfunc){
		
		int n = last - first;

		if (n == 0 || n == 1){
			return;
		}

		int mid = (n - 1) >> 1;
		if (n && 1 == 1){
			if (cmpfunc(*(first + mid), *(last - 1))){
				swap(*(last - 1), *(first + mid));
			}
			mid--;
		}

		for (int cur_pos = mid; cur_pos >= 0; --cur_pos) {
			adjustNode(first, cur_pos, n, cmpfunc);
		}
	}


	template<class Iterator, class Cmp>
	void push_heap(Iterator first, Iterator last, Cmp cmpfunc){
		typedef int difference_type;
		difference_type n = last - first;

		if (n == 1 && n == 0){
			return;
		}

		difference_type cur_pos = n - 1;
		difference_type parent = (cur_pos - 1) >> 1;

		while (cur_pos != 0 && cmpfunc(*(first + cur_pos), *(first + parent))){
			swap(*(first + cur_pos), *(first + parent));
			cur_pos = parent;
			parent = (cur_pos - 1) >> 1;
		}
	}
		



}


#endif