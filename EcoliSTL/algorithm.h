#ifndef _ECOLISTL_ALGORITHM_H
#define _ECOLISTL_ALGORITHM_H
#include <xutility>



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
		T tmp = (std::move(lhs));
		lhs = std::move(rhs);
		rhs = std::move(tmp);
	}

	//source area is [first, last), target area is [result - (last - first), result);
	//return (result - (last - first));
	template<class BidrecIterator1, class BidrecIterator2>
	BidrecIterator2 copy_reverse(BidrecIterator1 first, BidrecIterator1 last, BidrecIterator2 result){
		--last; --result;

		for (; first <= last; --last, --result) {
			*result = *last;
		}
		return result;
	}

	template<class T, class Cmp = greater<T>>
	T& max(const T& v1, const T& v2){

		Cmp cp = Cmp();

		if (cp(v1, v2)){
			return v1;
		}
		else{
			return v2;
		}
	}



	//function used in heap

	


}


#endif