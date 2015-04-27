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
			if (*(last - 1) > *(first + mid)){
				swap(*(last - 1), *(first + mid));
			}
			mid--;
		}

		for (difference_type cur_pos = mid; cur_pos >= 0; --cur_pos) {
			adjustNode(first, cur_pos);
		}
	}

	//adjust node of heap
	//default function is less<T>
	template<class Iterator>
	void adjustNode(Iterator start, size_t pos){
		Iterator father = start + pos;
		Iterator left_son = start + pos * 2 + 1;
		Iterator right_son = start + pos * 2 + 2;

		if (*left_son < *father){
			swap(*left_son, *father);
		}

		if (*right_son < *father){
			swap(*right_son, *father);
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

		//existence of last node
		if (cur_pos && 1 == 1){
			difference_type cur_father = (cur_pos - 1) >> 1;
			if (*(first + cur_father) > *(first + cur_pos)){
				swap(*(first + cur_father), *(first + cur_pos));
			}
			cur_pos = cur_father;
		}
		

		while (cur_pos) {
			difference_type cur_father = (cur_pos - 1) >> 1;
			adjustNode(first, cur_father);
			cur_pos = cur_father;
		}

	}

	//adjust heap after pop operator
	//time complexity O(logn)
	template<class Iterator>
	void pop_heap(Iterator first, Iterator last){
		typedef int difference_type;
		difference_type n = last - first;

		//if heap is emtpy or has only one element
		if (n == 0 || n == 1){
			return;
		}

		difference_type current_pos = 0;
		while (current_pos < n) {
			difference_type left_idx = current_pos * 2 + 1;
			difference_type right_idx = current_pos * 2 + 2;

			if (right_idx < n){
				if (*(first + left_idx) < *(first + right_idx)){
					swap(*(first + left_idx), *(first + current_pos));
					current_pos = left_idx;
				}
				else{
					swap(*(first + right_idx), *(first + current_pos));
					current_pos = right_idx;
				}
			}
			else if (right_idx > n){
				swap(*(first + current_pos), *(first + n - 1));
				current_pos = n;
			}
			else{
				swap(*(first + left_idx), *(first + current_pos));
				current_pos = left_idx;
			}
			
		}
	}

	//functions for heap with two parameter

	template<class Iterator, class Cmp>
	void adjustNode(Iterator start, size_t pos, Cmp cmpfunc){
		Iterator father = start + pos;
		Iterator left_son = start + pos * 2 + 1;
		Iterator right_son = start + pos * 2 + 2;

		if (cmpfunc(*left_son, *father)){
			swap(*left_son, *father);
		}

		if (cmpfunc(*right_son, *father)){
			swap(*right_son, *father);
		}
	}

	template<class Iterator, class Cmp>
	void make_heap(Iterator first, Iterator last, Cmp cmpfunc){
		size_t n = (size_t)(last - first);

		if (n == 0 || n == 1){
			return;
		}

		difference_type mid = (n - 1) >> 1;
		if (n && 1 == 1){
			if (cmpfunc(*(last - 1), *(first + mid))){
				swap(*(last - 1), *(first + mid));
			}
			mid--;
		}

		for (difference_type cur_pos = mid; cur_pos >= 0; --cur_pos) {
			adjustNode(first, cur_pos, cmpfunc);
		}
	}

	
	





}


#endif