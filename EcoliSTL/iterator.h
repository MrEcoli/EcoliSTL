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


	//iterator class不包含任何数据成员，只提供型别定义，新的iterator继承它不会增加负担
	//因为已经提供了后3个型别参数的默认型别，所以在定义新的iterator时，只需要给予iterator_category以及指向的数据成员类型即可。
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