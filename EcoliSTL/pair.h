#ifndef _ECSTL_PAIR_H
#define _ECSTL_PAIR_H


namespace EcSTL{

	template<class T1, class T2>
	class pair;

	template<class T1, class T2>
	pair<T1, T2> make_pair(const T1 &x1, const T2 &x2){
		return pair<T1, T2>(x1, x2);
	}

/*
	template<class T1, class T2>
	class getKey{
	public:
		T1 operator(pair<T1, T2> &givien)const{
			return givien.first;
		}
	};

	template<class T1, class T2>
	class getValue{
	public:
		T2 operator(pair<T1, T2> &givien)const{
			return givien.second;
		}
	};

*/



	template<class T1, class T2>
	class pair{
	public:
		T1 first;
		T2 second;

		pair(const T1& x1, const T2& x2) :first(x1), second(x2){}
		pair(){}
	};


}

#endif