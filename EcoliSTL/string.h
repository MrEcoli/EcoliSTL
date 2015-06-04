#ifndef _ECSTL_STRING_H
#define _ECSTL_STRING_H
#include "allocator.h"
#include "construct.h"
#include "algorithm.h"
#include <iosfwd>

namespace EcSTL{

	//use copy-On-write with base_string
	struct _Rep{
		typedef size_t size_type;
		size_type _M_capcity;
		size_type _M_length;
		size_type _M_reference_count;	//0 means leak, 
	};

	template<class _Char_t, class Aloc = allocator<_Char_t>>
	class basic_string{
	public:
		typedef _Char_t value_type;
		typedef _Char_t& reference;
		typedef _Char_t* pointer;
		typedef pointer iterator;
		typedef const _Char_t& const_reference;
		typedef _Char_t* const_iterator;
		typedef const _Char_t* const_pointer;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef basic_string<_Char_t, Aloc> self;
		typedef basic_string<_Char_t, Aloc> self_ref;
		typedef ptrdiff_t difference_type;

		
		static size_type npos;
		static size_type max_size(){ return (size_type(-1) - sizeof(_Rep) - sizeof(_Char_t)) / sizeof(_Char_t); }

		size_type size()const{
			return _M_pos->_M_length;
		}

		size_type capacity()const{	return _M_pos->_M_capcity;	}

		bool empty()const{	return size() == 0;	}

		const_iterator begin()const{ return (const_pointer)_m_date(); }

		const_iterator end()const{ return (const_iterator)(_m_date() + _M_pos->_M_length);	}

		const_iterator cbegin()const{ return (const_iterator)_m_date(); }

		const_iterator cend()const{ return (const_iterator)_m_date(); }

		iterator begin(){
			if (is_shared ()){
				_M_pos = creat_new(_M_pos);
			}
			return _m_date();
		}

		iterator end(){
			if (is_shared ()){
				_M_pos = creat_new(_M_pos);
			}
			return (_m_date() + _M_pos->_M_length);
		}

		void swap(basic_string<_Char_t, Aloc>& others){	EcSTL::swap(this->_M_pos, others._M_pos);	}

		void clear(){ this->~basic_string(); }

		void resize(size_type n){
			return resize(n, _Char_t());
		}

		void resize(size_type n, _Char_t ch){
			
			if (n < _M_pos->_M_length){
				_M_pos->_M_length = n;
				_m_date()[n] = 0;
			}
			else{
				append(ch, n - _M_pos->_M_length);
			}
		}


		basic_string() :_M_pos(reinterpret_cast<_Rep*>(_empty_string)){}

		inline basic_string(_Char_t ch, size_t n);
		
		inline basic_string(_Char_t ch);

		explicit inline basic_string(size_type n){
			this->swap(basic_string<_Char_t, Aloc>(_Char_t(), n));
		}

		inline basic_string(const _Char_t* _x);

		inline basic_string(const _Char_t* _x, size_type n);

		inline basic_string(const self& others):_M_pos(others._M_pos){ ++this->_M_pos->_M_reference_count; }

		inline basic_string(self&& others){ this->swap(others);}

		self& operator=(const self& rhs);

		//if the parameter is a rvalue, just move the _M_pos;
		self& operator=(self &&rhs){
			EcSTL::swap(this->_M_pos, rhs._M_pos);
			return *this;
		}

		self& operator+=(const self& rhs){ return append(rhs); }
		
		bool operator==(const self& rhs)const;
		
		const_reference operator[](size_type n)const{ return _m_date()[n]; 	}

		reference operator[](size_type n){
			if (is_shared ()){
				_M_pos = creat_new(_M_pos);
			}
			return _m_date()[n];
		}

		reference at(size_type n){ return this->operator[](n); }
		const_reference at(size_type n)const { 	return this->operator[](n); }

		self& erase(iterator _where);
		self& erase(size_type n);
		self& erase(iterator first, iterator last);
		self& erase(size_type fromt, size_type count);

		self& assign(const _Char_t& ch);
		self& assign(const _Char_t& ch, size_type n);
		self& assign(self& others);
		self& assign(const _Char_t* ch);
		self& assign(const _Char_t* ch, size_type n);

		template<class Iterator>
		self& assign(Iterator first, size_type n);

		template<class Iterator>
		self& assign(Iterator first, Iterator last);


		self& append(_Char_t ch);
		self& append(_Char_t ch, size_type n);
		self& append(const _Char_t* ch);
		self& append(const _Char_t* ch, size_type n);
		self& append(const self& others);
		
		template<class Iterator>
		self& append(Iterator first, size_type n);

		template<class Iterator>
		self& append(Iterator first, Iterator last);

		self substr(size_type start = 0, size_type n = npos){
			if (start == 0 && n == npos){
				return *this;
			}
			size_type sz = n;
			if ( n == npos){
				sz = size() - start;
			}

			return basic_string<_Char_t, Aloc>(this->c_str ()+ start, sz);
		}


		size_type find_first_of(_Char_t ch);
		size_type find_first_not_of(_Char_t ch);
		size_type find_last_of(_Char_t ch);
		size_type find_last_not_of(_Char_t ch);

		const _Char_t* c_str()const{
			return _m_date();
		}




		~basic_string(){
			if (_M_pos){
				--_M_pos->_M_reference_count;
			}

			if (is_leak()){
				_S_deallocator(_M_pos);
			}
		}

		const _Char_t* data()const{
			return reinterpret_cast<_Char_t*>(_M_pos);
		}


	private:
		_Rep* _M_pos;
		

		//all the _M_pos of empty string point here
		static char _empty_string[];



		//重新在堆中分配一块区域给n个_Char_t对象
		//如果内存空间充足，则会分配_length*2的空间;
		static _Rep* creat_n(size_type n){
			_Rep* ret = nullptr;
			size_type sz = sizeof(_Char_t)*(n + 1) + sizeof(_Rep);
			size_type _cap = sz;
			if (n < max_size ()){
				if (n * 2 < max_size ()){
					_cap = sz * 2;
				}
				ret = _S_allocator(_cap);
				//需要减去末尾的空字符和_Rep结构体的大小
				ret->_M_capcity = _cap - sizeof(_Rep) - sizeof(_Char_t);
				ret->_M_length = n;
				ret->_M_reference_count = 1;

				_Char_t *date = reinterpret_cast<_Char_t*>(ret + 1);
				//设置结尾
				date[n] = 0;
			}

			return ret;
		}


		//before use of the function, the valid of origin pointer is tested: whether is the pointer point to empty string; whether is the reference count of the string is over 1; this should be done using is_shared() function;
		static _Rep* creat_new(_Rep *origin){
			--origin->_M_reference_count;
			_Rep* ret = _S_allocator(origin->_M_capcity);
			ret->_M_length = origin->_M_length;
			ret->_M_capcity = origin->_M_capcity;
			ret->_M_reference_count = 1;
			_Char_t *from = reinterpret_cast<_Char_t*>(origin + 1);
			_Char_t *to = reinterpret_cast<_Char_t*>(ret + 1);

			//length+1, the last element represent ;
			uninitialized_copy(from, from + ret->_M_length + 1, to);
			return ret;
		}


		static _Rep* _S_allocator(size_type n){
			return (_Rep*)Aloc::allocate(n);
		}

		static size_type _allocator_length(size_type n){
			return sizeof(_Char_t) (n + 1) + sizeof(_Rep);
		}

		static void _S_deallocator(void* _x){
			if (_x && _x != _empty_string)
				return Aloc::deallocate((_Char_t*)_x);
		}

		_Char_t* _m_date(){
			return reinterpret_cast<_Char_t*>(_M_pos + 1);
		}

		const _Char_t* _m_date()const{
			return reinterpret_cast<_Char_t*>(_M_pos + 1);
		}

		_Rep* _m_rep(){
			return _M_pos;
		}

		bool is_leak(){
			if (_M_pos && _M_pos != reinterpret_cast<_Rep*>(_empty_string) && _M_pos->_M_reference_count == 0){
				return true;
			}
			return false;
		}

		bool is_shared(){
			if (_M_pos->_M_reference_count > 1 || _M_pos == (_Rep*)_empty_string){
				return true;
			}
			return false;
		}


		





	};

	template<class _Char_t, class A>
	typename basic_string<_Char_t, A>::size_type basic_string<_Char_t, A>::npos = (max_size() +1);

	template<class _Char_t, class A>
	char basic_string<_Char_t, A>::_empty_string[sizeof(_Rep) + sizeof(A)];



	//Constructors
	template<class _Char_t, class A>
	basic_string<_Char_t, A>::basic_string(const _Char_t* _x, size_type n){
		_M_pos = creat_n(n);
		uninitialized_copy(_x, _x + n, _m_date());
	}

	template<class _Char_t, class A>
	basic_string<_Char_t, A>::basic_string(const _Char_t* _x){
		size_type n = strlen(_x);
		//使用移动语义，将base_string(const _Char_t* _x, size_type n)构造的临时对象与*this进行交换
		(*this).swap(basic_string(_x, n));
	}

	template<class _Char_t, class A>
	basic_string<_Char_t, A>::basic_string(_Char_t ch, size_t n){
		_M_pos = creat_n(n);
		uninitialized_fill_n(_m_date(), n, ch);
	}

	template<class _Char_t, class A>
	basic_string<_Char_t, A>::basic_string(_Char_t ch){
		_M_pos = creat_n(1);
		uninitialized_fill_n(_m_date(), 1, ch);
	}


	template<class _Char_t, class A>
	typename basic_string<_Char_t, A>::self& basic_string<_Char_t, A>::operator=(const self& rhs){
		//destructor the origin memroy allocated
		this->~basic_string();
		this->_M_pos = rhs._M_pos;
		++this->_M_pos->_M_reference_count;
		return *this;
	}

	template<class _Char_t, class A>
	bool basic_string<_Char_t, A>::operator==(const basic_string<_Char_t, A>& rhs)const{
		//if the _M_pos is same, the strings used to compare is same string;
		if (_M_pos == rhs._M_pos){
			return true;
		}

		if (_M_pos->_M_length != (rhs._M_pos)->_M_length){
			return false;
		}

		const _Char_t *first = this->_m_date();
		const _Char_t *second = rhs._m_date();

		size_type n = _M_pos->_M_length;
		while (n--){
			if (*first != *second){
				return false;
			}
			++first;
			++second;
		}

		return true;
	}


	template<class _Char_t, class A>
	basic_string<_Char_t, A>& basic_string<_Char_t, A>::assign(const _Char_t* ch, size_type n){
		//真实的分配给字符串的空间大小为_M_capcity + 1, 但是末尾的字符为终结字符，因而实际能使用的空间为_M_capcity;
		if (is_shared () || _M_pos->_M_capcity < n){
			this->~basic_string();
			_M_pos = creat_n(n);
		}
		
		uninitialized_copy(ch, ch + n, _m_date());
		//设置末尾;
		_m_date()[n] = 0;
		this->_M_pos->_M_length = n;
		return *this;
	}



	template<class _Char_t, class A>
	basic_string<_Char_t, A>& basic_string<_Char_t, A>::assign(const _Char_t* ch){
		return assign(ch, strlen(ch));
	}

	template<class _Char_t, class A>
	basic_string<_Char_t, A>& basic_string<_Char_t, A>::assign(self& others){
		if (_M_pos != others._M_pos){
			this->assign(others.c_str(), others.size());
		}
		return *this;
	}

	template<class _Char_t, class A>
	basic_string<_Char_t, A>& basic_string<_Char_t, A>::assign(const _Char_t& ch){
		return assign(ch, 1);
	}

	template<class _Char_t, class A>
	basic_string<_Char_t, A>& basic_string<_Char_t, A>::assign(const _Char_t& ch, size_type n){
		if (is_shared () || this->capacity() < n ){
			this->~basic_string();
			_M_pos = creat_n(n);
		}
		uninitialized_fill_n(_m_date(), n, ch);
		_m_date()[n] = 0;
		this->_M_pos->_M_reference_count = n;
		return *this;
	}

	template<class _Char_t, class A>
	template<class Iterator>
	basic_string<_Char_t, A>& basic_string<_Char_t, A>::assign(Iterator first, size_type n){
		if (is_shared () || this->capacity () < n){
			this->~~basic_string();
			_M_pos = creat_n(n);
		}

		_Char_t *start = this->_m_date();
		uninitialized_copy(first, first + n, start);
		_m_date()[n] = 0;
		return *this;
	}

	template<class _Char_t, class A>
	template<class Iterator>
	basic_string<_Char_t, A>& basic_string<_Char_t, A>::assign(Iterator first, Iterator last){
		size_type n = distance(first, last);
		return assign(first, n);
	}




	//append function
	template<class _Char_t, class A>
	basic_string<_Char_t, A>& basic_string<_Char_t, A>::append(const self& others){
		return append(others.c_str(), others.size());
	}

	template<class _Char_t, class A>
	basic_string<_Char_t, A>& basic_string<_Char_t, A>::append(const _Char_t* ch, size_type n){
		size_type new_sz = size() + n;
		size_type old_sz = size();
		if (is_shared () || new_sz > capacity ()){
			self tmp(new_sz);
			tmp.assign(this->c_str(), this->size());
			this->swap(tmp);
			//destructor will be auto used
		}

		_Char_t* out = _m_date() + old_sz;

		uninitialized_copy(ch, ch + n, out);
		//设置结尾
		_m_date()[new_sz] = 0;
		_M_pos->_M_length = new_sz;
		return *this;
	}

	template<class _Char_t, class A>
	basic_string<_Char_t, A>& basic_string<_Char_t, A>::append(const _Char_t* ch){
		return append(ch, strlen(ch));
	}

	template<class _Char_t, class A>
	basic_string<_Char_t, A>& basic_string<_Char_t, A>::append(_Char_t ch){
		return append(ch, 1);
	}

	template<class _Char_t, class A>
	basic_string<_Char_t, A>& basic_string<_Char_t, A>::append(_Char_t ch, size_type n){
		size_type new_size = size() + n;
		size_type old_size = size();
		if (is_shared () || new_size > capacity ()){
			self tmp(new_size);
			tmp.assign(this->c_str(), this->size());
			this->swap(tmp);
		}

		uninitialized_fill(_m_date() + old_size, _m_date() + new_size, ch);
		_m_date()[new_size] = 0;
		_M_pos->_M_length = new_size;
		return *this;
	}

	template<class _Char_t, class A>
	template<class Iterator>
	basic_string<_Char_t, A>& basic_string<_Char_t, A>::append(Iterator first, Iterator last){
		size_type n = distance(first, last);
		return append(first, n);
	}

	template<class _Char_t, class A>
	template<class Iterator>
	basic_string<_Char_t, A>& basic_string<_Char_t, A>::append(Iterator first, size_type n){
		size_type new_sz = size() + n;
		size_type old_sz = size();

		if (is_shared () || new_sz > capacity ()){
			self tmp(new_sz);
			tmp.assign(this->c_str(), old_sz);
			this->swap(tmp);
		}

		_Char_t *start = _m_date() + old_sz;

		while (n--) {
			*start = *first;
			start++;
			first++;
		}

		_m_date()[new_sz] = 0;
		this->_M_pos->_M_length = new_sz;
		return *this;
	}



	template<class _Char_t, class A>
	typename basic_string<_Char_t, A>::size_type basic_string<_Char_t, A>::find_first_of(_Char_t ch){
		size_type index = 0;
		_Char_t *ptr = _m_date();
		while (index < size()) {
			if (*ptr == ch){
				return index;
			}
			++index;
		}
		return basic_string<_Char_t, A>::npos;
	}

	template<class _Char_t, class A>
	typename basic_string<_Char_t, A>::size_type basic_string<_Char_t, A>::find_first_not_of(_Char_t ch){
		size_type index = 0;
		_Char_t *ptr = _m_date();
		while (index < size()) {
			if (*(ptr + index) != ch){
				return index;
			}
			++index;
		}
		return basic_string<_Char_t, A>::npos;
	}

	template<class _Char_t, class A>
	typename basic_string<_Char_t, A>::size_type basic_string<_Char_t, A>::find_last_of(_Char_t ch){
		if (size () == 0){
			return basic_string<_Char_t, A>::npos;
		}

		long index = size() - 1;
		_Char_t *ptr = _m_date() + index;

		while (index >= 0) {
			if (*(ptr + index) == ch){
				return index;
			}
			--index;
		}

		return basic_string<_Char_t, A>::npos;
	}


	template<class _Char_t, class A>
	typename basic_string<_Char_t, A>::size_type basic_string<_Char_t, A>::find_last_not_of(_Char_t ch){
		if (size() == 0){
			return basic_string<_Char_t, A>::npos;
		}

		long index = size() - 1;
		_Char_t *ptr = _m_date() + index;

		while (index >= 0) {
			if (*(ptr + index) != ch){
				return index;
			}
			--index;
		}

		return basic_string<_Char_t, A>::npos;
	}

	template<class _Char_t, class A>
	typename basic_string<_Char_t, A>& basic_string<_Char_t, A>::erase(iterator _where){
		return erase(_where, _where + 1);
	}

	template<class _Char_t, class A>
	basic_string<_Char_t, A>& basic_string<_Char_t, A>::erase(iterator first, iterator last){
		size_type new_sz = size() - (last - first);
		iterator last_pos = _m_date() + size();

		while (last <= last_pos) {
			*first++ = *last++;
		}
		_M_pos->_M_length = new_sz;

		return *this;
	}


	template<class _Char_t, class A>
	basic_string<_Char_t, A>& basic_string<_Char_t, A>::erase(size_type index){
		return erase(_m_date() + index);
	}

	template<class _Char_t, class A>
	basic_string<_Char_t, A>& basic_string<_Char_t, A>::erase(size_type from, size_type count){
		return erase(_m_date() + from, _m_date() + from + count);
	}








	template<class _Char_t, class A>
	std::ostream& operator<<(std::ostream& out, basic_string<_Char_t, A>& str){
		out << str.c_str();
		return out;
	}

	template<class _Char_t, class A>
	basic_string<_Char_t, A>& operator+(basic_string<_Char_t, A>& left, basic_string<_Char_t, A>& right){
		return left.operator+=(right);
	}

	/*template<class _Char_t, class A>
	bool operator<(basic_string<_Char_t, A>& left, basic_string<_Char_t, A>& right){
		const _Char_t* lhs = left.c_str();
		const _Char_t* rhs = rhs.c_str();

		while (*lhs && *lhs == '0'){
			++lhs;
		}

		while (*rhs && *rhs == '0') {
			++rhs;
		}

		while (*lhs && *rhs) {
			if (*lhs > *rhs){
				return false;
			}
			lhs++;
			rhs++;
		}

		return true;

	}
*/



	typedef basic_string<char> string;
}

#endif	//_ECSTL_STRING_H