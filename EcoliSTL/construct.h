#ifndef _ECOLISTL_CONSTRUCT_H
#define _ECOLISTL_CONSTRUCT_H

#include <new>
#include "_type_trait.h"
#include <sys\utime.h>

namespace EcoliSTL{

	//为什么这里会有个T2呢？？
	template<typename T1, typename T2>
	inline void construct(T1* ptr, const T2& val){
		//placement new;
		new (p)T1(T2); 
	}

	template<typename T>
	inline void destroy(T ptr){
		ptr->~T()；
	}

	template<typename ForwardIterator>
	inline void destroy(ForwardIterator first, ForwardIterator last){
		//这里的value_type函数是Iterator的一个内置函数，返回一个指向空指针的T*;
		_destroy(first, last, value_type(first));
	}


	//根据对象T是否有trivial destructor 进行偏特化萃取;
	template<typename ForwardIterator, typename T>
	inline void _destroy(ForwardIterator first, ForwardIterator last, T*){
		typedef typename _type_traits<T>::has_trival_destructor trival_destructor;
		_destroy_aux(first, last, trival_destructor());
	}


	template<typename ForwardIterator>
	inline void __destroy_aux(ForwardIterator first, ForwardIterator last, _false_type x){
		for (; first < last; ++first){
			destroy(&(*first));
		}
	}

	template<typename ForwardIterator>
	inline void __destroy_aux(ForwardIterator first, ForwardIterator last, _true_type x) {}


	//针对char与wchar的特化版本， _type_trait中并未特化char与wchar

	inline void destroy(char*, char*){}

	inline void destory(wchar_t*, wchar_t*){}

}



#endif