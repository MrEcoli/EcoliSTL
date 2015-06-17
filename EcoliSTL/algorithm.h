#ifndef _ECOLISTL_ALGORITHM_H
#define _ECOLISTL_ALGORITHM_H
#include <xutility>
#include "iterator.h"
#include "algorithm.h"



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

	template<typename Bidirect_iterator>
	void reverse(Bidirect_iterator _first, Bidirect_iterator _last){
		--_last;

		while (_first < _last)
		{
			swap(*_first, *_last);
			++_first;
			--_last;
		}

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


	template<class Iterator, class T>
	Iterator lower_bound(Iterator first, Iterator last, const T& val){
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return lower_bound_help(first, last, val, category());
	}

	template<class Iterator, class T>
	Iterator lower_bound_help(Iterator first, Iterator last, const T& val, random_access_iterator_tag){
		Iterator mid = first;
		while (first < last){
			mid = first + ((last - first) >> 1);

			if (*mid >= val){
				last = mid;
			}
			else{
				first = mid+1;
			}

		}
		return first;
	}

	template<class Iterator, class T>
	Iterator lower_bound_help(Iterator first, Iterator last, const T& val, forward_iterator_tag){
		typedef Iterator::difference_type difference_type;
		difference_type n = distance(first, last);
		Iterator mid = first;
		difference_type half;
		while (n) {
			half = n >> 1;
			mid = advance(first, half);
			if (*mid < val){
				first = ++mid;
				n = n - half - 1;
			}
			else{
				n = half;
			}
		}
		return first;
	}


	template<class Iterator, class T, class Cmp>
	Iterator lower_bound(Iterator first, Iterator last, const T& val, Cmp cmpfunc){
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return lower_bound_help(first, last, val, cmpfunc, category());
	}


	template<class Iterator, class T, class Cmp>
	Iterator lower_bound_help(Iterator first, Iterator last, const T& val, Cmp cmpfunc, random_access_iterator_tag){
		Iterator mid = first;

		while (first < last) {
			mid = first + ((last - first) >> 1);

			if (cmpfunc(*mid, val)){
				first = mid + 1;
			}
			else{
				last = mid;
			}

		}
		return first;
	}

	template<class Iterator, class T, class Cmp>
	Iterator lower_bound_help(Iterator first, Iterator last, const T& val, Cmp cmpfunc, forward_iterator_tag){
		Iterator mid = first;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		difference_type n = distance(first, last);
		difference_type half;

		while (n) {
			half = n >> 1;
			mid = first;
			advance(first, half);

			if (cmpfunc(*mid, val)){
				first = mid++;
				n = n - half - 1;
			}
			else
				n = half;
		}
		return first;
	}


	template<class Iterator, class T>
	Iterator upper_bound(Iterator first, Iterator last, const T& val){
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		difference_type n = distance(first, last);
		Iterator mid;
		while (n) {
			difference_type half = n >> 1;
			mid = first;
			advance(mid, half);
			if (val < *mid){
				n = half;
			}
			else{
				n = n - half - 1;
				first = ++mid;
			}
		}
		return first;
	}



	template<class Iterator, class T, class Cmp>
	Iterator upper_bound(Iterator first, Iterator last, const T& val, Cmp cmpfunc){
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		difference_type n = distance(first, last);
		Iterator mid;
		difference_type half;

		while (n) {
			half = n >> 1;
			mid = first;
			advance(mid, half);

			if (cmpfunc(val, *mid)){
				n = half;
			}
			else{
				first = ++mid;
				n = n - half - 1;
			}
		}
		return first;
	}



	template<class Iterator, class T>
	bool binary_search(Iterator first, Iterator last, const T& val){
		Iterator result = lower_bound(first, last, val);
		return result != last && val ==  *result;
	}

	template<class Iterator, class T, class Cmp>
	bool binary_search(Iterator first, Iterator last, const T& val, Cmp cmpfunct){
		Iterator result = lower_bound(first, last, val, cmpfunct);
		return result != last && !cmpfunct(val, *result);
	}


	template<class Iterator, class Pred>
	Iterator partition(Iterator first, Iterator last, Pred _pred){
		if (first == last) return first;

		while (_pred(*first))
			if (++first == last)
				return first;

		Iterator nxt_pos = first;


		while (++nxt_pos != last) {
			if (_pred(*nxt_pos)){
				swap(*first, *nxt_pos);
				++first;
			}
		}
		return first;
	}

	template<typename Iterator>
	void sort(Iterator first, Iterator last){
		typedef typename iterator_traits<Iterator>::value_type value_type;
		if (first == last) return;

		Iterator from = next(first);

		Iterator pos = partition(from, last, bind2nd(less<value_type>(), *first));

		swap(*first, *(prev(pos)));
		
		sort(first, prev(pos));
		sort(pos, last);
	}

	template<typename Iterator, typename Pred>
	void sort(Iterator first, Iterator last, Pred _pred_func){
		typedef typename iterator_traits<Iterator>::value_type value_type;
		if (first == last) return;

		Iterator from = next(first);

		Iterator pos = EcSTL::partition(from, last, EcSTL::bind2nd(_pred_func, *first));
		
		swap(*first, *(prev(pos)));
		

		EcSTL::sort(first, prev (pos), _pred_func);
		EcSTL::sort(pos, last, _pred_func);
		
	}




	template<typename Iterator, typename T>
	Iterator find(Iterator first, Iterator last, const T& _v){
		while (first != last && *first != _v)
			++first;
		return first;
	}

	template<typename Iterator, typename Cond_func>
	Iterator find_if(Iterator first, Iterator last, Cond_func _cond_func){
		while (first != last && !_cond_func(*first)) 
			++first;
		return first;
	}

	template<typename Iterator, typename _Pred>
	typename iterator_traits<Iterator>::difference_type count_if(Iterator first, Iterator last, _Pred _pred_func){
		typename iterator_traits<Iterator>::difference_type n = 0;
		while (first != last)
			if (_pred_func(*first++)) ++n;

		return n;
	}


	template<typename Iterator, typename T>
	T accumulate(Iterator first, Iterator last, T _x){
		while (first != last){
			T _y = *first++;
			_x = plus<T>()(_x, _y);
		}
		
		return _x;
	}

	template<typename Iterator, typename T, typename Func>
	T accumulate(Iterator first, Iterator last, T _x, Func _func){
		while (first != last){
			T _y = *first++;
			_x = _func(_x, _y);

		}

		return _x;
	}

	template<typename Iterator1, typename Iterator2>
	inline void iter_swap(Iterator1 rhs, Iterator2 lhs){
		typename iterator_traits<Iterator1>::value_type tmp = *rhs;
		*rhs = *lhs;
		*lhs = tmp;
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