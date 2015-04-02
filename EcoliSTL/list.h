#ifndef _ECSTL_LIST_H
#define _ECSTL_LIST_H
#include <iostream>
#include "allocator.h"
#include "iterator.h"
#include "functional.h"
using std::cout;
using std::endl;

//STL��list�ṹ��Ϊ˫������;


namespace EcSTL{

	//listʵ�ʵĽڵ�����

	template<class T>
	struct _list_node{
		typedef _list_node<T>* pointer;
		pointer next;
		pointer prev;
		T data;
	};

	//���list�ĵ�����
	//������˫���б���������iterator��bidirection�ģ���������random_access��

	template<class T, class Ref = T&, class Ptr = T*>
	class _list_iterator{
	public:
		typedef _list_iterator<T, Ref, Ptr> self;
		typedef _list_iterator<T, T&, T*> iterator;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef _list_node<T>* link_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef bidirectional_iterator_tag iterator_category;

		//consturctor and copy constuctor

		_list_iterator(link_type ptr) :ptr_to_node(ptr){}
		_list_iterator(){}
		_list_iterator(const _list_iterator& others) :ptr_to_node(others.ptr_to_node){}

		link_type ptr_to_node;

		self operator++(){
			this->ptr_to_node = this->ptr_to_node->next;
			return *this;
		}

		self operator++(int){
			self tmp = *this;
			this->ptr_to_node = this->ptr_to_node->next;
			return tmp;
		}

		self operator--(){
			this->ptr_to_node = this->ptr_to_node->prev;
			return *this;
		}

		self operator--(int) {
			self tmp = *this;
			this->ptr_to_node = this->ptr_to_node->prev;
			return tmp;
		}

		bool operator==(const self& rhs)const{

			return ptr_to_node == rhs.ptr_to_node;
		}

		bool operator!=(const self& rhs)const{
			return ptr_to_node != rhs.ptr_to_node;
		}

		reference operator*()const{
			return ptr_to_node->data;
		}


		//��ͷ���������뷵��һ��ָ�������������->����������

		pointer operator->()const{
			return &(operator*());
		}
	};

	template < class T, class Alloc = allocator<_list_node<T>> >
	class list{
	public:
		typedef _list_node<T> list_node;
		typedef T value_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef _list_iterator<T, T&, T*> iterator;
		typedef list_node* link_type;
		typedef T& reference;

	private:
		//SGI STL������һ��link_type��ʾ��������next��prev�ֱ�ָ��list��ͷ����β�����γ���һ����״����

		link_type node;

	public:

		//constructor function and copy function;
		list(){
			node = get_node();
			node->prev = node->next = node;
		}

		list(size_type n){
			list(n, T());
		}

		list(size_type n, const T& val);

		~list();


		iterator begin(){ return iterator(node->next); }
		iterator begin()const { return iterator(node->next); }
		iterator end() { return iterator(node); }
		iterator end() const { return iterator(node); }
		size_type size()const{ return distance(begin(), end()); }
		bool empty()const{ return begin() == end(); }
		reference front(){ return *begin(); }
		reference back(){ return *(--end()); }

		//����������޸�;
		void push_back(const value_type& _Val){
			insert(end(), _Val);
		}

		void push_front(const value_type& _Val){
			insert(begin(), _Val);
		}

		void pop_back(){
			erase(--end());
		}

		void pop_front(){
			erase(begin());
		}

		iterator erase(iterator position){
			link_type next_node = position.ptr_to_node->next;
			link_type prev_node = position.ptr_to_node->prev;
			prev_node->next = next_node;
			next_node->prev = prev_node;
			destroy_node(position.ptr_to_node);
			return iterator(next_node);
		}

		void clear();

		iterator insert(iterator position, const T& v){
			link_type tmp = make_node(v);
			tmp->next = position.ptr_to_node;
			tmp->prev = position.ptr_to_node->prev;
			position.ptr_to_node->prev->next = tmp;
			position.ptr_to_node->prev = tmp;
			return tmp;
		}

		//�Ƴ����������е�data����T�Ľڵ�
		void remove(const T& val);

		void unique();


		bool operator==(const list<T, Alloc>& rhs)const{
			return size() == rhs.size() && equal(begin(), end(), rhs.begin());
		}

		bool operator!=(const list<T, Alloc>& rhs)const{
			return size() != rhs.size() || !equal(begin(), end(), rhs.begin());
		}

		list<T, Alloc>& operator=(const list<T, Alloc>& rhs){
			list<T, Alloc> ret = list<T, Alloc>();
			
			iterator first = rhs.begin();
			iterator last = rhs.end();
			while (first != last) {
				ret.push_back(*first);
				++first;
			}

			this->swap(ret);
			return *this;
		}


		void splice(iterator position, list<T, Alloc>& others){
			if (!others.empty ()){
				transfer(position, others.begin(), others.end());
			}
		}

		void splice(iterator position, iterator iter){
			iterator nxt_iter = next(iter);
			if (position == iter && position == nxt_iter)
				return;

			transfer(position, iter, nxt_iter);
		}

		void splice(iterator position, iterator first, iterator last){
			if (first != last){
				transfer(position, first, last);
			}
		}
		void merge(list<T, Alloc> &others);

		void sort();

		void reverse();

		void swap(list<T, Alloc>& others){
			iterator first = begin();
			iterator last = end();
			transfer(begin(), others.begin(), others.end());
			transfer(others.begin(), first, last);
		}

		void print(){
			if (empty ()){
				cout << "No member in the list" << endl;
				return;
			}
			iterator first = begin();
			iterator last = end();

			while (first != last) {
				cout << (*first) << " ";
				++first;
			}
			cout << endl;
			
		}


	protected:

		//ʵ�ַ�����list_node�ķ����У�ͨ������һ������ڴ棬Ȼ��ͨ���ƶ�ָ�룬ʵ�ֽ��ڴ���������
		//���ص�result��һ���ֲ��ڶ��еĶ�����Ҫ�����ڴ��ͷţ�������������������
		//����release_node�������н����ͷ�.

		//����ע�ͣ����·����ǲ����еģ���Ϊ�ڴ��������һ�����ģ����������õ������ǲ��ܽ��е����ڵ���ڴ�Ļ���

		/*link_type get_n_node(size_type n){
			link_type result = get_node();
			result->next = result->prev = result;

			if (n > 0){
			link_type first_node = (link_type)(Alloc::allocate(n));
			result->next = first_node;
			first_node->prev = result;
			link_type cur_node = first_node;
			link_type next_node = first_node;

			//������������ӣ�һ����n����㣬������(n-1)�ε�����

			for (size_type i = 1; i < n; ++i) {
			next_node = link_type((char*)cur_node + sizeof(list_node));
			next_node->prev = cur_node;
			cur_node->next = next_node;
			cur_node = next_node;
			}

			cur_node->next = result;
			result->prev = cur_node;
			}

			return result;

			}*/


		link_type get_node(){
			return (link_type)Alloc::allocate(1);
		}

		void release_node(link_type ptr){
			Alloc::deallocate(ptr);
		}

		link_type make_node(const T& val){
			link_type tmp = get_node();
			if (tmp){
				construct(&(tmp->data), val);
			}
			return tmp;
		}

		void destroy_node(link_type ptr){
			if (ptr) {
				destroy(&(ptr->data));
				release_node(ptr);
			}
		}

		void transfer(iterator position, iterator first, iterator last){
			link_type first_node = first.ptr_to_node;
			//�����last_nodeָ��transfer�����һ���ڵ㣬����ǰ�պ���
			link_type last_node = last.ptr_to_node;
			link_type insert_pos = position.ptr_to_node;
			link_type prev_insert = insert_pos->prev;

			//���postion == last����ô����Ĺ����ǲ���Ҫ���е�;
			//ʵ���ϸ�������6�����ӣ�ͬʱ��Ҫһ����������position֮ǰ��λ��,tmp
			if (position != last && first != last){
				last_node->prev->next = insert_pos;
				first_node->prev->next = last_node;
				prev_insert->next = first_node;
				insert_pos->prev = last_node->prev;
				last_node->prev = first_node->prev;
				first_node->prev = prev_insert;
			}
		}


	};




	template<class T, class Alloc>
	list<T, Alloc>::list(size_type n, const T& val){
		node = get_node();
		node->next = node->prev = node;
		for (size_type i = 0; i < n; i++){
			push_back(val);
		}
	}



	template<class T, class Alloc>
	list<T, Alloc>::~list(){
		iterator first = begin(), last = end();
		iterator cur;

		//����������
		while (first != last) {
			//cur���ڱ�ʾĿǰ��Ҫ���������Ľ���iterator,ͬʱfirstǰ��һλ��
			cur = first++;
			destroy_node(cur.ptr_to_node);
		}
		//�ͷŶ�̬�����class�е����ݶ���node;
		release_node(node);
	}


	template<class T, class Alloc>
	void list<T, Alloc>::clear(){
		iterator first = begin();
		iterator last = end();

		while (first != last) {
			iterator tmp = first++;
			erase(tmp);
		}

	}


	template<class T, class Alloc>
	void list<T, Alloc>::unique(){

		iterator first = begin();
		iterator last = end();

		if (first == last || next(first) == last){
			return;
		}
		iterator cur_node = first;
		iterator next_node = cur_node;
		while (next(cur_node) != last) {
			next_node = next(cur_node);
			if (*next_node == *cur_node){
				erase(cur_node);
			}
			cur_node = next_node;
		}
	}
	template<class T, class Alloc>
	void list<T, Alloc>::remove(const T& val){
		iterator first = begin();
		iterator last = end();
		while (first != last){
			iterator tmp = first++;
			if (*tmp == val){
				erase(tmp);
			}
		}
	}


	template<class T, class Alloc>
	void list<T,Alloc>::reverse (){
		iterator first = begin();
		iterator last = end();
		if (first == last || next(first) == last){
			return;
		}

		++first;
		while (first != last) {
			iterator tmp = first++;
			//��һ�ƶ��ڵ�
			transfer(begin(), tmp, first);
		}
	}



	//merge Ĭ�������Ѿ���������Ĭ�ϵ���less<T>�º���������������

	template<class T, class Alloc>

	void list<T, Alloc>::merge(list<T, Alloc> &rhs){
		iterator first = begin();
		iterator last = end();

		
		iterator rhs_first = rhs.begin();
		iterator rhs_last = rhs.end();

		if (rhs_first == rhs_last)
			return;

		while (first != last && rhs_first != rhs_last) {
			if (*first < *rhs_first){
				first++;
			}
			else{
				iterator tmp = rhs_first++;
				transfer(first, tmp, rhs_first);
			}
		}

		if (first == last){
			transfer(first, rhs_first, rhs_last);
		}
	}



	template<class T, class Alloc>
	void list<T, Alloc>::sort(){
		iterator first = begin();
		iterator last = end();
		//���ֻ��һ���ڵ���ǿ��б�ֱ�ӷ���
		if (first == last || next (first) == last){
			return;
		}

		list<T, Alloc> tmp_list;
		list<T, Alloc> list_arr[64];
		int fill = 0;

		while (!empty()){
			tmp_list.splice(tmp_list.begin(), begin());

			int i = 0;

			while (i < fill && !list_arr[i].empty ()) {
				list_arr[i].merge(tmp_list);
				tmp_list.swap(list_arr[i++]);
			}

			tmp_list.swap(list_arr[i]);
			if (i == fill){
				++fill;
			}
		}

		for (int i = 1; i < fill; ++i) {
			list_arr[i].merge(list_arr[i-1]);
		}

		swap(list_arr[fill - 1]);
	}


}



#endif