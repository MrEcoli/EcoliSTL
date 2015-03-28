#ifndef _ECOLISTL_CONSTRUCT_H
#define _ECOLISTL_CONSTRUCT_H

#include <new>
#include "_type_trait.h"
#include <sys\utime.h>

namespace EcoliSTL{

	//Ϊʲô������и�T2�أ���
	template<typename T1, typename T2>
	inline void construct(T1* ptr, const T2& val){
		//placement new;
		new (p)T1(T2); 
	}

	template<typename T>
	inline void destroy(T ptr){
		ptr->~T()��
	}

	template<typename ForwardIterator>
	inline void destroy(ForwardIterator first, ForwardIterator last){
		//�����value_type������Iterator��һ�����ú���������һ��ָ���ָ���T*;
		_destroy(first, last, value_type(first));
	}


	//���ݶ���T�Ƿ���trivial destructor ����ƫ�ػ���ȡ;
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


	//���char��wchar���ػ��汾�� _type_trait�в�δ�ػ�char��wchar

	inline void destroy(char*, char*){}

	inline void destory(wchar_t*, wchar_t*){}

}



#endif