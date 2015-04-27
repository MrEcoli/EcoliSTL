#ifndef _ECSTL_PRORITY_QUEUE_H
#define _ECSTL_PRORITY_QUEUE_H

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
		priority_queue(Iterator first, Iterator last){
			vec(first, last);
			make_heap(vec.begin(), vec.end());
		}

		T top()const{
			return vec.front();
		}

		void pop(){


		}



	};



}

#endif