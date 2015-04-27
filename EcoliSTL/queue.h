#ifndef _ECSTL_QUEUE_H
#define _ECSTL_QUEUE_H


namespace EcSTL{

	template<class T, class Seq = deque<T>>
	class queue{
	private:
		Seq sequence;

	public:

		typedef typename Seq::value_type value_type;
		typedef typename Seq::difference_type difference_type;
		typedef typename Seq::size_type size_type;
		typedef typename Seq::reference reference;
		typedef typename Seq::const_reference const_reference;
		typedef queue<T, Seq> self;


		queue(){}

		queue(const self& others){
			sequence = others.sequence;
		}

		void pop(){
			sequence.pop_front();
		}

		void push(const value_type& val){
			sequence.push_back(val);
		}

		reference front(){
			return sequence.front();
		}

		const_reference front()const{
			return sequence.front();
		}


		reference back(){
			return sequence.back();
		}

		const_reference back()const{
			return sequence.back();
		}

		
		bool empty()const{
			return sequence.empty();
		}
		
		size_type size(){
			return sequence.size();
		}

		
		void swap(self& others){
			sequence.swap(others.sequence);
		}
		
		void operator=(self& rhs)const{
			sequence = rhs.sequence;
		}

		bool operator==(const self& rhs)const{
			return sequence == rhs.sequence;
		}

		bool operator!=(const self& rhs)const{
			return sequence != rhs.sequence;
		}



	};


}














#endif