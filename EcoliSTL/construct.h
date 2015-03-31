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








	template<typename T>
	inline void destroy(T* ptr){
		ptr->~T();
	}

	template<typename ForwardIterator>
	inline void destroy(ForwardIterator first, ForwardIterator last){
		//�����value_type������Iterator��һ�����ú���������һ��ָ���ָ���T*;
		_destroy(first, last, value_type(first));
	}


	//���ݶ���T�Ƿ���trivial destructor ����ƫ�ػ���ȡ;
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


	//���char��wchar���ػ��汾�� _type_trait�в�δ�ػ�char��wchar

	inline void destroy(char*, char*){}

	inline void destory(wchar_t*, wchar_t*){}


	//������ȡiterator��value_type
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
		for (; first != last; first++, out++){
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



	//����type_traitѡ�����ŵĵĺ���ʵ��uninitialized_fill
	template<class ForwardIterator, class T>
	inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& v){
		typedef typename _type_trait<T>::is_POD_type is_POD;
		_uninitialized_fill_aux(first, last, v, is_POD());
	}

	template<class ForwardIterator, class T>
	inline void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& v, _false_type){
		while (first != last){
			construct(&*first, v);
			first++;
		}
	}

	template<class ForwardIterator, class T>
	inline void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& v, _true_type){
		while (first != last){
			*first = v;
			first++;
		}
	}


	//����type_traitѡ�����ŵĵĺ���ʵ��uninitialized_fill
	template<class ForwardIterator, class Distance, class T>
	inline void uninitialized_fill_n(ForwardIterator first, Distance dis, const T& v){
		typedef typename _type_trait<T>::is_POD_type is_POD;
		_uninitialized_fill_n_aux(first, dis, v, is_POD());
	}


	template<class ForwardIterator, class Distance, class T>
	inline void _uninitialized_fill_n_aux(ForwardIterator first, Distance dis, const T& v, _false_type){
		Distance size = 0;
		while (size != dis) {
			size++;
			construct(&*first, v);
			first++;
		}
	}

	template<class ForwardIterator, class Distance, class T>
	inline void _uninitialized_fill_n_aux(ForwardIterator first, Distance dis, const T& v, _true_type){
		Distance size = 0;
		while (size != dis) {
			size++;
			*first = v;
			first++;
		}
	}


}



#endif