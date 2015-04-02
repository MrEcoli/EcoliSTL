#ifndef _ECOLI_ITERATOR_H
#define _ECOLI_ITERATOR_H

#include "_type_trait.h"
#include <crtdefs.h>

namespace EcSTL{

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator{
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef T* pointer;
		typedef T& reference;
	};


	struct input_iterator_tag{};
	struct output_iterator_tag{};
	struct forward_iterator_tag: public input_iterator_tag{};
	struct bidirectional_iterator_tag : public forward_iterator_tag{};
	struct random_access_iterator_tag : public bidirectional_iterator_tag{};

	template <class I>
	struct iterator_traits{
		typedef typename I::iterator_category iterator_category;
		typedef typename I::value_type value_type;
		typedef typename I::difference_type difference_type;
		typedef typename I::pointer pointer;
		typedef typename I::reference reference;
	};

	template<class T>
	struct iterator_traits<T*>{
		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
	};

	template<class T>
	struct iterator_traits<const T*>{
		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef const T* pointer;
		typedef const T& reference;
	};


	//iterator class不包含任何数据成员，只提供型别定义，新的iterator继承它不会增加负担
	//因为已经提供了后3个型别参数的默认型别，所以在定义新的iterator时，只需要给予iterator_category以及指向的数据成员类型即可。
	

	template<class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category iterator_category(const Iterator&){
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return category();
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator&){
		return (typename iterator_traits<Iterator>::value_type*)(0);
	}

	
	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type* difference_type(const Iterator&){
		return (typename iterator_traits<Iterator>::difference_type*)(0);
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type
		distance(Iterator first, Iterator last) {
			typedef typename iterator_traits<Iterator>::iterator_category category;
			return _distance(first, last, category());
		}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type
		_distance(Iterator first, Iterator last, input_iterator_tag){
			iterator_traits<Iterator>::difference_type n = 0;

			while (first != last) {
				++n;
				++first;
			}
			return n;
		}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type
		_distance(Iterator first, Iterator last, random_access_iterator_tag){
			return last - first;
		}


	template<class InputIterator, class Distance>
	inline void advance(InputIterator &iter, Distance dis){
		_advance(iter, dis, iterator_traits<InputIterator>::iterator_category());
	}

	template<class InputIterator, class Distance>
	inline void _advance(InputIterator &iter, Distance n, input_iterator_tag){
		while (n--){
			iter++;
		}
	}

	template<class InputIterator, class Distance>
	inline void _advance(InputIterator &iter, Distance n, forward_iterator_tag){
		_advance(iter, n, input_iterator_tag());
	}

	template<class InputIterator, class Distance>
	inline void _advance(InputIterator &iter, Distance n, bidirectional_iterator_tag){
		if (n >= 0){
			while (n--)
				iter++;
		}
		else{
			while (n++)
				iter--;
		}
	}

	template<class InputIterator, class Distance>
	inline void _advance(InputIterator &iter, Distance n, random_access_iterator_tag){
		iter += n;
	}
	
	template<class InputIterator>
	inline InputIterator next(InputIterator iter){
		return ++iter;
	}

	template<class InputIterator>
	inline InputIterator prev(InputIterator iter){
		return --iter;
	}



}

#endif