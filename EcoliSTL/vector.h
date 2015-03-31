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

		vector<T, Alloc>& operator=(const vector<T, Alloc>& rhs){
			if (size () >= rhs.size ()){
				Alloc::deallocate(vec_start, size ());
				uninitialized_copy(vec_start, vec_end, rhs.begin());
				vec_end = vec_start + rhs.size();
			}
			else{

				
				iterator tmp = Alloc::allocate(rhs.size());
				if (tmp == nullptr){
					std::cerr << "No enough memory" << std::endl;
					return;
				}

				Alloc::destroy(begin(), end());
				Alloc::deallocate(begin(), vec_reserve - begin());
				
				copy(rhs.begin(), rhs.end(), tmp);
				vec_start = tmp;
				vec_end = tmp + rhs.size();
				vec_reserve = vec_end;
			}

			return *this;
		}

		void swap(vector<T, Alloc> &rhs);

		void print()const;


};
	//insert_aux ��Ŀ��λ�ò���һ������
	template<class T, class Alloc>
	void vector<T, Alloc>::insert_aux(iterator position, const T& v){

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
			//Ĭ�Ϸ���_DEFAULT_AOLLOCATE_STORE*(ԭʼ�����С���ڴ�)
			iterator tmp = (iterator)Alloc::allocate((size() + 1)* _DEFAULT_AOLLOCATE_STORE);
			//����ڴ治�����������С�ڴ��;			
			if (tmp == nullptr){
				tmp = (iterator)Alloc::allocate(size() + 1);
				if (tmp == nullptr){
					std::cerr << "No enough memory" << std::endl;
					return;
				}
				else{
					//��С�ڴ����䷽����Ч�Ļ�������ԭʼ�ڴ�
					size_type old_size = size();
					uninitialized_copy(vec_start, position, tmp);
					construct(tmp + (position - vec_start), v);
					uninitialized_copy(position, vec_end, tmp + (position - vec_start) + 1);

					destroy(vec_start, vec_end);

					Alloc::deallocate(vec_start, vec_reserve - vec_start);

					vec_start = tmp;
					vec_end = vec_start + old_size + 1;
					vec_reserve = vec_end;
				}
			}
			else{
				size_type old_size = size();
				
				uninitialized_copy(vec_start, position, tmp);
				construct(tmp + (position - vec_start), v);
				uninitialized_copy(position, vec_end, tmp + (position - vec_start) + 1);
				
				if (vec_start){
					destroy(vec_start, vec_end);
					Alloc::deallocate(vec_start, vec_reserve - vec_start);
				}

				vec_start = tmp;
				vec_end = vec_start + old_size + 1;
				vec_reserve = (old_size + 1) * _DEFAULT_AOLLOCATE_STORE + vec_start;
			}
		}
	}

	//insert ��Ŀ��λ�ò���������

	template<class T, class Alloc>
	void vector<T, Alloc>::insert(iterator position, size_type n, const T& val) {
		if (n <= capacity () - size ()){
			copy_reverse(position, vec_end, vec_end + n);
			vec_end += n;
			uninitialized_fill_n(position, n, val);
		}
		else{
			iterator tmp = (iterator)Alloc::allocate((size() + n) * _DEFAULT_AOLLOCATE_STORE);
			size_type old_size = size();
			//��������ڴ�ʧ�ܣ��򽵵�Ϊ��СҪ�����·��䣻
			if (tmp == nullptr){
				tmp = (iterator)Alloc::allocate(size() + n);
				if (tmp == nullptr){
					std::cerr << "No enough memory" << std::endl;
					return;
				}
				else{

					//����ʽ����/���죺1��position֮ǰ�ģ�2����Ҫ�����n������3��postion֮��Ķ���
					uninitialized_copy(vec_start, position, tmp);
					uninitialized_fill_n(tmp + (position - vec_start), n, val);
					uninitialized_copy(position, vec_end, tmp + (position - vec_start) + n);
					if (vec_start){

						destroy(vec_start, vec_start + size());
						Alloc::deallocate(vec_start, vec_reserve - vec_start);
					}


					vec_start = tmp;

					vec_end = tmp + old_size + n;

					vec_reserve = vec_end;
				}
			}
			else{
				uninitialized_copy(vec_start, position, tmp);
				uninitialized_fill_n(tmp + (position - vec_start), n, val);
				uninitialized_copy(position, vec_end, tmp + (position - vec_start) + n);

				if (vec_start){
					destroy(vec_start, vec_start + size());
					Alloc::deallocate(vec_start, vec_reserve - vec_start);
				}


				vec_start = tmp;
				vec_end = tmp + old_size + n;

				vec_reserve = tmp + (old_size + n) * _DEFAULT_AOLLOCATE_STORE;
			}
		}
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::swap(vector<T, Alloc>& rhs){
		EcoliSTL::swap(this->vec_start, rhs.vec_start);
		EcoliSTL::swap(this->vec_end, rhs.vec_end);
		EcoliSTL::swap(this->vec_reserve, rhs.vec_reserve);
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::print()const{

		for (iterator it = vec_start; it != vec_end; ++it) {

			std::cout << *it << " " ;
		}

		std::cout << std::endl;
	}

}


#endif