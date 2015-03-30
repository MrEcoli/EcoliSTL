#ifndef _ECOLISTL_ALGORITHM_H
#define _ECOLISTL_ALGORITHM_H

namespace EcoliSTL{

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
			if (!(*first == *others)){
				return false;
			}
		}
		return true;
	}


}


#endif