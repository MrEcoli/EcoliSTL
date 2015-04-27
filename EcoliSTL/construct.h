#ifndef _ECOLISTL_CONSTRUCT_H
#define _ECOLISTL_CONSTRUCT_H

#include <new>
#include "_type_trait.h"
#include <sys\utime.h>

namespace EcSTL{

	//为什么这里会有个T2呢？？
	template<typename T1, typename T2>
	inline void construct(T1* ptr, const T2& val){
		//placement new;
		new (ptr) T1(val);
	}

	template<class ForwardIterator, class T>
	inline void construct(ForwardIterator first, ForwardIterator last, const T& val){
		typedef typename _type_trait<T>::has_trivial_default_constructor constructor;

		_construct(first, last, val, constructor());
	}

	template<class ForwardIterator, class T>
	inline void construct(ForwardIterator first, ForwardIterator last, const T& val, _true_type){
		for (; first != last; ++first) {
			*first = val;
		}
	}

	template<class ForwardIterator, class T>
	inline void construct(ForwardIterator first, ForwardIterator last, const T& val, _false_type){
		for (; first != last; ++first) {
			construct(&*first, val);
		}
	}







	//调用不同版本的析构函数
	template<typename T>
	inline void destroy(T* ptr){
		if (ptr){
			ptr->~T();
		}
	}

	template<typename ForwardIterator>
	inline void destroy(ForwardIterator first, ForwardIterator last){
		//这里的value_type函数是Iterator的一个内置函数，返回一个指向空指针的T*;
		_destroy(first, last, value_type(first));
	}


	//根据对象T是否有trivial destructor 进行偏特化萃取;
	template<typename ForwardIterator, typename T>
	inline void _destroy(ForwardIterator first, ForwardIterator last, T*){
		typedef typename _type_trait<T>::has_trivial_default_destructor trivial_destructor;
		__destroy_aux(first, last, trivial_destructor());
	}


	template<typename ForwardIterator>
	inline void __destroy_aux(ForwardIterator first, ForwardIterator last, _false_type x){
		for (; first < last; ++first){
			destroy(&(*first));
		}
	}

	template<typename ForwardIterator>
	inline void __destroy_aux(ForwardIterator first, ForwardIterator last, _true_type x) {}


	//参数为两个指针的destroy函数；

	template<class ForwardIterator, class Distance>
		inline void destory(ForwardIterator iter, Distance dis){
		_destroy(iter, dis, value_type(iter));
	}

	template<class ForwardIterator, class Distance, class T>
	inline void _destroy(ForwardIterator iter, Distance dis, T*){
		typedef typename _type_trait<T>::has_trivial_default_destructor desturctor;
		__destroy_aux(iter, dis, desturctor());
	}

	template<class ForwardIterator, class Distance>
	inline void __destroy_aux(ForwardIterator iter, Distance dis, _true_type){}

	template<class ForwardIterator, class Distance>
	inline void __destroy_aux(ForwardIterator iter, Distance dis, _false_type){
		Distance n = 0;
		for (; n != dis; ++n, ++iter) {
			destory(&*iter);
		}
	}









	//针对char与wchar的特化版本， _type_trait中并未特化char与wchar




	inline void destroy(char*, char*){}

	inline void destory(wchar_t*, wchar_t*){}


	//首先萃取iterator的value_type
	template<class InputIterator, class ForwardIterator>
	inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator out){
		return _uninitialized_copy(first, last, out, value_type(first));
	}

	template<class InputIterator, class ForwardIterator, class T>
	inline ForwardIterator _uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator out, T*){
		typedef typename _type_trait<T>::is_POD_type _is_POD;
		return _uninitialized_copy_aux(first, last, out, _is_POD());
	}

	template<class InputIterator, class ForwardIterator>
	inline ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator out, _true_type){
		for (; first != last; ++first, ++out){
			*out = *first;
		}
		return out;
	}

	template<class InputIterator, class ForwardIterator>
	inline ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator out, _false_type){
		
		for (; first != last; ++first, ++out) {
			construct(&*out, *first);
		}
		return out;
	}



	//利用type_trait选择最优的的函数实现uninitialized_fill
	template<class ForwardIterator, class T>
	inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& v){
		typedef typename _type_trait<T>::is_POD_type is_POD;
		_uninitialized_fill_aux(first, last, v, is_POD());
	}

	template<class ForwardIterator, class T>
	inline void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& v, _false_type){
		while (first != last){
			construct(&*first, v);
			++first;
		}
	}

	template<class ForwardIterator, class T>
	inline void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& v, _true_type){
		while (first != last){
			*first = v;
			++first;
		}
	}


	//利用type_trait选择最优的的函数实现uninitialized_fill
	template<class ForwardIterator, class Distance, class T>
	inline void uninitialized_fill_n(ForwardIterator first, Distance dis, const T& v){
		typedef typename _type_trait<T>::is_POD_type is_POD;
		_uninitialized_fill_n_aux(first, dis, v, is_POD());
	}


	template<class ForwardIterator, class Distance, class T>
	inline void _uninitialized_fill_n_aux(ForwardIterator first, Distance dis, const T& v, _false_type){
		Distance size = 0;
		while (size != dis) {
			++size;
			construct(&*first, v);
			++first;
		}
	}

	template<class ForwardIterator, class Distance, class T>
	inline void _uninitialized_fill_n_aux(ForwardIterator first, Distance dis, const T& v, _true_type){
		Distance size = 0;
		while (size != dis) {
			++size;
			*first = v;
			++first;
		}
	}


}



#endif