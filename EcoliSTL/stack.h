#ifndef _ECSTL_STACK_H
#define _ECSTL_STACK_H

#include "deque.h"


namespace EcSTL{

	template<class T, class Container = deque<T>>
	class stack
	{
	public:
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::difference_type difference_type;
		typedef typename Container::reference reference;
		typedef stack<T, Container> self;

		stack(){}

		~stack(){
			stack_que.~Container();
		}

		size_type size()const{
			return stack_que.size();
		}


		bool empty()const{
			return stack_que.empty();
		}

		reference top(){
			return stack_que.back();
		}

		void pop(){
			stack_que.pop_back();
		}

		void push(const value_type& val){
			stack_que.push_back(val);
		}

		void swap(const self& others){
			stack_que.swap(others.stack_que);
		}

		self& operator=(const self& others){
			stack_que = others.stack_que;
			return *this;
		}

		bool operator==(const self& rhs)const{
			return stack_que == rhs.stack_que;
		}

		bool operator!=(const self& rhs)const{
			return stack_que != rhs.stack_que;
		}
		

	private:

		Container stack_que;


	};





}

#endif