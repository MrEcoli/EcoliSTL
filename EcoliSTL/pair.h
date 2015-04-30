#ifndef _ECSTL_PAIR_H
#define _ECSTL_PAIR_H




namespace EcSTL{

	template<class T1, class T2>
	class pair;
	template<class T1, class T2>
	class getKey;
	template<class T1, class T2>
	class getValue;

	template<class T1, class T2>
	class pair{
	public:
		typedef T1 first_type;
		typedef T2 second_type;
		T1 first;
		T2 second;

		pair(const T1& x1, const T2& x2) :first(x1), second(x2){}
		pair(){}
	};


	template<class T1, class T2>
	pair<T1, T2> make_pair(const T1 &x1, const T2 &x2){
		return pair<T1, T2>(x1, x2);
	}



}

#endif