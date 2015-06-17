#ifndef _ECSTL_PRORITY_QUEUE_H
#define _ECSTL_PRORITY_QUEUE_H

#include "vector.h"
#include "functional.h"
namespace EcSTL{

	//priority_queue has 3 type parameter
	template<class T, class Container = vector<T>, class Cmp = less < T > >
	class priority_queue{
	private:
		Container vec;
		Cmp cmpfunc;
	public:
		priority_queue(){};
		template<class Iterator>
		priority_queue(Iterator first, Iterator last):vec(first, last){
			make_heap(vec.begin(), vec.end(), cmpfunc);
		}

		T front()const{
			return vec.front();
		}

		void pop(){
			swap(vec.front(), vec.back());
			vec.pop_back();
			adjustNode(vec.begin(), 0, vec.size(), cmpfunc);
		}

		void push(const T& v){
			vec.push_back(v);
			push_heap(vec.begin(), vec.end(), cmpfunc);
		}

		bool empty()const{
			return vec.empty();
		}

		void print(){
			vec.print();
		}

	};
}

#endif