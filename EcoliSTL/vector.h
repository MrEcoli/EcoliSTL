#ifndef _ECOLISTL_VECTOR_H
#define _ECOLISTL_VECTOR_H

#include "allocator.h"
#include "construct.h"
#include "_type_trait.h"
#include "iterator.h"
#include "algorithm.h"
#include <iostream>


namespace EcoliSTL{

	template<class T, class Alloc = allocator<T>>
	class vector{
	public:
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef value_type* pointer;
		typedef value_type* iterator;
		typedef const value_type* const_iterator;
		typedef value_type& reference;
		typedef size_t size_type;

	protected:
		enum { _DEFAULT_AOLLOCATE_STORE = 2 };
		iterator vec_start;
		iterator vec_end;
		iterator vec_reserve;
		

		void fill_initialize(size_type n, const T& val){
			vec_start = (iterator)(Alloc::allocate(n * _DEFAULT_AOLLOCATE_STORE));
			if (vec_start){
				vec_end = vec_start + n;
				vec_reserve = n * _DEFAULT_AOLLOCATE_STORE + vec_start;
			}
		}

		void insert_aux(iterator position, const T& v);


	public:
		iterator begin(){ return vec_start; }
		iterator end(){ return vec_end; }
		const_iterator cbegin()const { return vec_start; }
		const_iterator cend()const { return vec_end; }
		iterator empty() const { return vec_end == vec_start; }
		reference operator[](size_type n){ return *(vec_start + n); }
		size_type size() const { return vec_end - vec_start; }
		size_type capacity() const { return vec_reserve - vec_start; }

		vector() :vec_start(0), vec_end(0), vec_reserve(0){}
		vector(size_type n, const T& val){
			fill_initialize(n, val);
		}

		explicit vector(size_type n){
			vec_start = (iterator)(Alloc::allocate(n * _DEFAULT_AOLLOCATE_STORE));

			if (vec_start){
				vec_end = vec_start + n;
				vec_reserve = n * _DEFAULT_AOLLOCATE_STORE + vec_start;
				uninitialized_fill_n(vec_start, n, T());
			}


		}

		~vector(){
			destroy(vec_start, vec_end);
			if (vec_start){
				Alloc::deallocate(vec_start, vec_reserve - vec_start);
			}
		}

		iterator erase(iterator iter){
			copy(iter + 1, vec_end, iter);

			destroy(iter);
			vec_end--;

			return iter;

		}

		iterator erase(iterator first, iterator last){
			copy(last, vec_end, first);
			destroy(first + (last - vec_end), vec_end);
			vec_end -= (last - first);
			return first;
		}

		void clear(){
			erase(begin(), end());
		}

		void resize(size_type new_size){
			resize(new_size, T());
		}

		void resize(size_type new_size, const T& val){
			if (new_size < size ()){
				erase(begin() + new_size, end());
			}
			else{
				insert(end(), new_size - size(), val);
			}
		}

		void push_back(const T& v){
			if (vec_end != vec_reserve){
				construct(vec_end, v);
				++vec_end;
			}
			else{
				insert_aux(end(), v);
			}
		}

		void pop_back(){
			--vec_end;
			destroy(vec_end);
		}
		
		void insert_aux(iterator position, const T& val);
		void insert(iterator position, size_type n, const T& val);

		bool operator==(const vector<T, Alloc>& vec)const{

			return this->size() == vec.size() && equal(begin(), end(), vec.begin());
		}

		bool operator!=(const vector<T, Alloc>& vec)const{
			return this->size() != vec.size() || equal(begin(), end(), vec.begin());
		}

		void swap(vector<T, Alloc> &rhs);


};
	//insert_aux 在目的位置插入一个对象；
	template<class T, class Alloc>
	void vector<T, Alloc>::insert_aux(ierator position, const T& v){

		if (vec_end < vec_reserve){
			if (vec_end == position){
				construct(vec_end, v);
				vec_end++;
			}
			else{
				uninitialized_copy(position, vec_end, position + 1);
				construct(position, v);
				vec_end++;
			}
		}
		else{
			iterator tmp = Alloc::allocate(size() * _DEFAULT_AOLLOCATE_STORE);
			if (tmp == nullptr){
				tmp = Alloc::allocate(size() + 1);
				if (tmp == nullptr){
					std::cerr << "No enough memory" << std::endl;
					return;
				}
				else{
					size_type old_size = size();
					vec_start = tmp;
					vec_end = vec_start + old_size + 1;
					vec_reserve = vec_end;
					construct(vec_end - 1, v);
				}
			}
			else{
				size_type old_size = size();
				
				uninitialized_copy(vec_start, position, tmp);
				construct(tmp + (position - vec_start), v);
				uninitialized_copy(position, vec_end, tmp + (position - vec_start) + 1);
				
				vec_start = tmp;
				vec_end = vec_start + old_size + 1;
				vec_reserve = old_size * _DEFAULT_AOLLOCATE_STORE;
			}
		}
	}

	//insert 在目的位置插入多个对象

	template<class T, class Alloc>
	void vector<T, Alloc>::insert(iterator position, size_type n, const T& val) {
		if (n <= vec_reserve - vec_end){
			uninitialized_copy(pos, vec_end, pos + n);
			vec_end += n;
			uninitialized_fill_n(pos, n, val);
		}
		else{
			iterator tmp = Alloc::allocate((size() + n) * _DEFAULT_AOLLOCATE_STORE);
			size_type old_size = size();

			if (tmp == nullptr){
				tmp = Alloc::allocate(size() + n);
				if (tmp == nullptr){
					std::cerr << "No enough memory" << std::endl;
					return;
				}
				else{
					uninitialized_copy(vec_start, position, tmp);
					uninitialized_fill_n(tmp + (position - vec_start), n, val);

					uninitialized_copy(position, vec_end, tmp + (position - vec_start) + n);

					vec_start = tmp;

					vec_end = tmp + old_size + n;

					vec_reserve = vec_end;
				}
			}
			else{
				uninitialized_copy(vec_start, position, tmp);
				uninitialized_fill_n(tmp + (position - vec_start), n, val);
				uninitialized_copy(position, vec_end, tmp + (position - vec_start) + n);

				vec_start = tmp;
				vec_end = tmp + old_size + n;

				vec_reserve = (old_size + n) * _DEFAULT_AOLLOCATE_STORE;
			}

		}
	}





}


#endif