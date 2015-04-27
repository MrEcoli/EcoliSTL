#ifndef _ECSTL_QUART_HEAP_H
#define _ECSTL_QUART_HEAP_H

namespace EcSTL{

	//heap with four child
	template<class T, int Dnode, class Container = vector<T>, class Cmp = less < T > >
	class priority_queue{
	private:
		Container vec;
		Cmp cmpfunc;
	public:
		priority_queue(){};
		template<class Iterator>
		priority_queue(Iterator first, Iterator last) :vec(first, last){
			make_heap(first, last);
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

	private:

	};


}

#endif // !_ECSTL_QUART_HEAP_H
