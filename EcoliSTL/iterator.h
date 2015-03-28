#ifndef _ECOLI_ITERATOR_H
#define _ECOLI_ITERATOR_H

#include "_type_trait.h"
#include <crtdefs.h>

namespace EcoliSTL{

	struct input_iterator_tag{};
	struct output_iterator_tag{};
	struct forward_iterator_tag: public input_iterator_tag{};
	struct bidirectional_iterator_tag : public forward_iterator_tag{};
	struct random_access_iterator_tag : public bidirectional_iterator_tag{};

	template <class I>
	struct iterator_traits{
		typedef typename I::iterator_category iterator_category;
		typedef typename I::value_type value_type;
		typedef typename I::different_type different_type;
		typedef typename I::pointer pointer;
		typedef typename I::reference reference;
	};

	template<class T>
	struct iterator_traits<T*>{
		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t different_type;
		typedef T* pointer;
		typedef T& reference;
	};

	template<class T>
	struct iterator_traits<const T*>{
		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t different_type;
		typedef const T* pointer;
		typedef const T& reference;
	};


	//iterator class�������κ����ݳ�Ա��ֻ�ṩ�ͱ��壬�µ�iterator�̳����������Ӹ���
	//��Ϊ�Ѿ��ṩ�˺�3���ͱ������Ĭ���ͱ������ڶ����µ�iteratorʱ��ֻ��Ҫ����iterator_category�Լ�ָ������ݳ�Ա���ͼ��ɡ�
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator{
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance different_type;
		typedef T* pointer;
		typedef T& reference;
	};
	

}



#endif