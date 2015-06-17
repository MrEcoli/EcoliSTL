#ifndef _D_HEAP_H
#define _D_HEAP_H
#include "algorithm.h"
namespace EcSTL{
	
	template<class Iterator, class Cmp>
	void adjust_dheap_node(Iterator start, int current_pos, int n, Cmp cmpfunc, int d){
		int choice = current_pos;

		for (int idx = 1; idx <= d && current_pos*d + idx < n; ++idx) {
			if (cmpfunc(*(start + current_pos*d + idx), *(start + choice))) {
				choice = current_pos*d + idx;
			}
		}
		if (choice != current_pos){
			swap(*(start + current_pos), *(start + choice));
			adjust_dheap_node(start, choice, n, cmpfunc, d);
		}
	}

	template<class Iterator, class Cmp>
	void push_dheap(Iterator first, Iterator last, Cmp cmpfunc, int d){
		int n = last - first;

		if (n == 0 || n ==1){
			return;
		}

		int curpos = n - 1;
		int parent = (n - 2) / d;

		while (curpos && cmpfunc(*(first + curpos), *(first + parent))) {
			swap(*(first + curpos), *(first + parent));
			curpos = parent;
			parent = (curpos - 1) / d;
		}
	}

	template<class Iterator, class Cmp>
	void make_dheap(Iterator first, Iterator last, Cmp cumfunc, int d){
		int n = last - first;

		if (n == 0 || n == 1){
			return;
		}

		for (int i = (n - 2) / d; i >= 0; --i) {
			adjust_dheap_node(first, i, cmpfunc, d);
		}

	}


	template<class T, int d = 2, class Seq = vector<T>, class Cmp = less<T>>
	class dheap_pq{
	private:
		Seq container;
		Cmp cmpfunc;
	public:
		dheap_pq(){}
		template<class Iterator>
		dheap_pq(Iterator first, Iterator last) :container(first, last){
			make_dheap(first, last, cmpfunc, d);
		}

		const T& front()const{
			return container.front();
		}

		void pop(){
			EcSTL::swap(container.front(), container.back());

			container.pop_back();

			adjust_dheap_node(container.begin(), 0, container.size(), cmpfunc, d);
		}

		void push(const T& v){
			container.push_back(v);
			push_dheap(container.begin(), container.end(), cmpfunc, d);
		}

		bool empty(){
			return container.empty();
		}

		size_t size(){
			return container.size();
		}

		void swap(dheap_pq &rhs){
			rhs.container.swap(this->container);
			swap(rhs.cmpfunc, this->cmpfunc);
		}

		void print(){
			container.print();
		}

	};
}

#endif