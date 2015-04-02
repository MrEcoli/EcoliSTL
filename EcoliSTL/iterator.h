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


	//iterator class�������κ����ݳ�Ա��ֻ�ṩ�ͱ��壬�µ�iterator�̳����������Ӹ���
	//��Ϊ�Ѿ��ṩ�˺�3���ͱ������Ĭ���ͱ������ڶ����µ�iteratorʱ��ֻ��Ҫ����iterator_category�Լ�ָ������ݳ�Ա���ͼ��ɡ�
	

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