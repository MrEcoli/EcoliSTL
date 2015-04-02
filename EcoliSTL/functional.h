#ifndef _ECSTL_FUNCTIONAL_H
#define _ECSTL_FUNCTIONAL_H

//�º�����ͨ���������operator ()��ģ���˺����Ĺ���
//ͨ�������������Ŀ�����Է�ΪһԪ�Ͷ�Ԫ�º���
//���ݷº����Ĺ���functional��ķº������Է�Ϊ�������߼�����ϵ�����



namespace EcSTL {

	//STL���е�һԪ�º�������̳�������, �ͱ�����
	template<class T, class Result>
	class unary_function{
		typedef T argument_type;
		typedef Result result_type;
	};

	//STL���еĶ�Ԫ�º�������̳�������, �ͱ�����

	template<class Arg1, class Arg2, class Result>
	class binary_function{
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};
	

	//�����º���

	template<class T>
	struct plus:public binary_function < T, T, T > {
		T operator()(const T& x, const T& y) const {
			return x + y;
		}
	};


	template<class T>
	struct minus:public binary_function < T, T, T > {
		T operator()(const T& x, const T& y) const {
			return x - y;
		}
	};

	template<class T>
	struct multiplies:public binary_function < T, T, T > {
		T operator()(const T& x, const T& y) const {
			return x * y;
		}
	};

	template<class T>
	struct divides:public binary_function < T, T, T > {
		T operator()(const T& x, const T& y) const {
			return x / y;
		}
	};

	template<class T>
	struct modulus:public binary_function < T, T, T > {
		T operator()(const T& x, const T& y) const {
			return x % y;
		}
	};

	template<class T>
	struct negate :public unary_function < T, T > {
		T operator()(const T& x) const {
			return -x;
		}
	};




	//��ϵ������طº���

	template<class T>
	struct equal_to:public binary_function < T, T, bool > {
		bool operator()(const T& x, const T& y) const {
			return x == y;
		}
	};

	
	template<class T>
	struct not_equal_to:public binary_function < T, T, bool > {
		bool operator()(const T& x, const T& y) const {
			return x != y;
		}
	};


	template<class T>
	struct greater:public binary_function < T, T, bool > {
		bool operator()(const T& x, const T& y) const {
			return x > y;
		}
	};


	template<class T>
	struct greater_equal:public binary_function < T, T, bool > {
		bool operator()(const T& x, const T& y) const {
			return x >= y;
		}
	};


	template<class T>
	struct less:public binary_function < T, T, bool > {
		bool operator()(const T& x, const T& y) const {
			return x < y;
		}
	};


	template<class T>
	struct less_equal:public binary_function < T, T, bool > {
		bool operator()(const T& x, const T& y) const {
			return x <= y;
		}
	};


	
	//�߼�����º���
	template<class T>
	struct logical_and:public binary_function < T, T, bool > {
		bool operator()(const T& x, const T& y) const {
			return x && y;
		}
	};


	template<class T>
	struct logical_or:public binary_function < T, T, bool > {
		bool operator()(const T& x, const T& y) const {
			return x || y;
		}
	};

	template<class T>
	struct logical_not:public unary_function < T, bool > {
		bool operator()(const T& x) const {
			return !x;
		}
	};



	//֤ͬ��ѡ��Ͷ��º���

	template<class T>
	struct identity:public unary_function < T, T > {
		const T& operator()(const T& x) const { return x; }
	};
	

	template<class Pair>
	struct select1st :public unary_function < Pair, typename Pair::first_type> {
		const typename Pair::first_type& operator()(const Pair& x) const { return x.first; }
	};



	template<class Pair>
	struct select2nd :public unary_function < Pair, typename Pair::second_type > {
		const typename Pair::second_type& operator()(const Pair& x) const { return x.second; }
	};



	//Ͷ�亯��


	template<class T1, class T2>
	struct project1st:public binary_function < T1, T2, T1 > {
		T1 operator()(const T1& x, const T2& y)const{ return x; }
	};

	template<class T1, class T2>
	struct project2nd:public binary_function < T1, T2, T2 > {
		T2 operator()(const T1& x, const T2& y) const { return y; }
	};






}




#endif // !_ECSTL_FUNCTIONAL_H
