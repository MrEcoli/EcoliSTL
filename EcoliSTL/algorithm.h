#ifndef _ECOLISTL_ALGORITHM_H
#define _ECOLISTL_ALGORITHM_H

namespace EcSTL{

	template<class InputIterator, class OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator out){
		for (; first != last; ++first, ++out) {
			*out = *first;
		}
		return out;
	}

	template<class ForwardIterator1, class  ForwardIterator2>
	bool equal(ForwardIterator1 first, ForwardIterator2 last, ForwardIterator2 others){
		for (; first != last; ++others, ++first) {
			if (*first != *others){
				return false;
			}
		}
		return true;
	}

	template<class T>
	void swap(T& lhs, T& rhs){
		T tmp = T(lhs);
		lhs = rhs;
		rhs = tmp;
	}

	template<class BidrecIterator1, class BidrecIterator2>
	BidrecIterator2 copy_reverse(BidrecIterator1 first, BidrecIterator1 last, BidrecIterator2 result){
		--last; --result;

		for (; first <= last; --last, --result) {
			*result = *last;
		}

		return result;
	}

}


#endif