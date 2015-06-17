#ifndef _ECSTL_FUNCTIONAL_H
#define _ECSTL_FUNCTIONAL_H

//仿函数，通过重载类的operator ()，模仿了函数的功能
//通过给予参数的数目，可以分为一元和二元仿函数
//根据仿函数的功能functional里的仿函数可以分为算术，逻辑，关系运算等



namespace EcSTL {

	//STL所有的一元仿函数必须继承以下类, 型别声明
	template<class T, class Result>
	class unary_function{
	public:
		typedef T argument_type;
		typedef Result result_type;
	};

	//STL所有的二元仿函数必须继承以下类, 型别声明

	template<class Arg1, class Arg2, class Result>
	class binary_function{
	public:
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};
	

	//算术仿函数

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




	//关系运算相关仿函数

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


	
	//逻辑运算仿函数
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



	//证同，选择，投射仿函数

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



	//投射函数


	template<class T1, class T2>
	struct project1st:public binary_function < T1, T2, T1 > {
		T1 operator()(const T1& x, const T2& y)const{ return x; }
	};

	template<class T1, class T2>
	struct project2nd:public binary_function < T1, T2, T2 > {
		T2 operator()(const T1& x, const T2& y) const { return y; }
	};



	template <class _Operation>
	class binder1st
		: public unary_function < typename _Operation::second_argument_type,
		typename _Operation::result_type > {
	protected:
		_Operation op;
		typename _Operation::first_argument_type value;
	public:
		binder1st(const _Operation& __x,
			const typename _Operation::first_argument_type& __y)
			: op(__x), value(__y) {}
		typename _Operation::result_type
			operator()(const typename _Operation::second_argument_type& __x) const {
			return op(value, __x);
		}
	};

	template <class _Operation, class _Tp>
	inline binder1st<_Operation>
		bind1st(const _Operation& __fn, const _Tp& __x)
	{
		typedef typename _Operation::first_argument_type _Arg1_type;
		return binder1st<_Operation>(__fn, _Arg1_type(__x));
	}

	template<class _Operation>
	class binder2nd
		:public unary_function < typename _Operation::first_argument_type,
		typename _Operation::result_type > {
	protected:
		_Operation _op;
		typename _Operation::second_argument_type _v;
	public:
		binder2nd(const _Operation& _x, const typename _Operation::second_argument_type& _y) :_op(_x), _v(_y){}

		typename typename _Operation::result_type
			operator()(const typename _Operation::first_argument_type& _x){
			return _op(_x, _v);
		}
	};

	template<class Operation, class T>
	inline binder2nd<Operation> bind2nd(const Operation& bi_func, const T& _x){
		typedef typename Operation::second_argument_type _arg_type;
		return binder2nd<Operation>(bi_func, _arg_type(_x));
	}

	
}




#endif // !_ECSTL_FUNCTIONAL_H
