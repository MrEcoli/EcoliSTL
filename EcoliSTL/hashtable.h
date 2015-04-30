#ifndef _ECSTL_HASHMAP_H
#define _ECSTL_HASHMAP_H

#include "vector.h"
#include "iterator.h"
#include "pair.h"
#include "construct.h"
//EcSTL的hashtable采用开链法解决primer cluster
//hashtable通过一个vector保存bucket
//每一个bucket里都维护着一个链表
//通过给予的模板参数HashFcn确定Key所在的bucket的位置，然后在这个bucket中进行插入
//iterator 不单单要保存它所指向的node节点的指针，同时也要保存整个hashtable的指针，ForwardIterator的基本功能，在bucket的末尾为空的情况下，指向下一个bucket。

namespace EcSTL{


	template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
	class hashtable;
	template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
	struct _hash_iterator;
	template<class Value>
	struct _hash_node;




	enum _primer_num { __stl_num_primes = 28 };

	static const unsigned long __stl_prime_list[__stl_num_primes] =
	{
		53ul, 97ul, 193ul, 389ul, 769ul,
		1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
		49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
		1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
		50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
		1610612741ul, 3221225473ul, 4294967291ul
	};

	inline unsigned long __stl_next_prime(unsigned long __n)
	{
		const unsigned long* __first = __stl_prime_list;
		const unsigned long* __last = __stl_prime_list + (int)__stl_num_primes;
		const unsigned long* pos = lower_bound(__first, __last, __n);
		return pos == __last ? *(__last - 1) : *pos;
	}




	//hashtable中节点的定义

	template<class T>
	struct _hash_node{
		_hash_node* next;
		T data;
	};

	//hashtable中迭代器的定义

	template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
	struct _hash_iterator{
		//iterator 型别声明;
		typedef _hash_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> iterator;
		typedef hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> hashtable;
		typedef _hash_node<Value> node;

		typedef forward_iterator_tag iterator_category;
		typedef Value value_type;
		typedef Value& reference;
		typedef Value* pointer;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		//当前所指向的节点
		node* current_node;

		//当前所在的hashtable地址
		hashtable* ht;

		//构造函数

		_hash_iterator(node* given_node, hashtable* given_ht) :current_node(given_node), ht(given_ht){}

		_hash_iterator() :current_node(nullptr), ht(nullptr) {}

		//可以定义为const,因为该操作不会改变 current_node和ht的数据
		reference operator*()const{
			return current_node->data;
		}

		//可以定义为const,因为该操作不会改变 current_node和ht的数据
		pointer operator->()const{
			return &(operator*());
		}

		iterator& operator++();

		iterator operator++(int);

		bool operator==(const iterator& others)const{ return current_node == others.current_node; }
		bool operator!=(const iterator& others)const{ return current_node != others.current_node; }

	};

	template<class V, class K, class Hf, class Exk, class Eqk, class A>
	typename _hash_iterator<V, K, Hf, Exk, Eqk, A>::iterator& _hash_iterator<V, K, Hf, Exk, Eqk, A>::operator++(){
		//这里保存的是iterator，里面的元素是两个指针
		//并不保存Value的原因是，构造Value类型可能需要调用大量的资源。
		
		node* origin = current_node;
		current_node = current_node->next;

		//如果bucket的链表已空
		if (!current_node){
			size_type bucket_position = ht->bkt_num_val(origin->data);
			while (!current_node && ++bucket_position < ht->buckets.size()){
				current_node = ht->buckets[bucket_position];
			}
		}

		return *this;
	}

	//设置为内联函数
	template<class V, class K, class Hf, class Exk, class Eqk, class A>
	inline typename _hash_iterator<V, K, Hf, Exk, Eqk, A>::iterator _hash_iterator<V, K, Hf, Exk, Eqk, A>::operator++(int){

		iterator ret = *this;

		this->operator++();

		return ret;
	}












	//hashtable的定义

	template<class Value, class Key, class HashFunc, class ExtractKey, class EqualKey, class Alloc = allocator<_hash_node<Value>>>
	class hashtable{
	public:
		typedef HashFunc hasher;
		typedef EqualKey key_equal;
		typedef size_t size_type;
		typedef _hash_iterator<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc> iterator;
		typedef Value value_type;
		typedef _hash_node<Value> node;
		typedef Alloc node_allocator;
		typedef Key key_type;
		typedef value_type& reference;

		friend iterator;

	private:
		//hashtable的数据成员
		//hash函数，用于确定Value的位置
		hasher hash;
		//用于比较key值是否相同的仿函数
		key_equal equals;
		//比较值大小的仿函数
		ExtractKey get_key;

		//vector用于存储链表，元素的存储在vector中的位置由hash函数/仿函数决定
		vector<node*> buckets;
		//存储的元素的数目
		size_type num_elements;

	public:

		//hashtable中元素的数目
		size_type size()const{ return num_elements; }

		bool empty()const{ return num_elements == 0; }

		//链表的数目
		size_type max_bucket_count()const { return buckets.size(); }
		size_type bucket_count()const;
		//constructor
		hashtable(size_type n, const HashFunc& hf, const EqualKey& eq) :hash(hf), equals(eq), get_key(ExtractKey()), num_elements(0){
			initialize_buckets(n);
		}

		hashtable(const hashtable& others){
			copy_from(others);
		}

		hashtable& operator=(const hashtable& others){
			return hashtable(others);
		}


		void swap(hashtable& others){
			buckets.swap(others.buckets);
			swap(num_elements, others.num_elements);
		}

		//member function
		void initialize_buckets(size_type n){
			size_type new_size = next_size(n);
			buckets.reserve(new_size);
			buckets.insert(buckets.end(), new_size, nullptr);
			num_elements = 0;
		}
		size_type next_size(size_type n) const{
			return __stl_next_prime(n);
		}
		pair<iterator, bool> insert_unique(const value_type& val){
			resize(num_elements + 1);
			return insert_unique_noresize(val);
		}
		pair<iterator, bool> insert_equal(const value_type& val){
			resize(num_elements + 1);
			return insert_equal_noresize(val);
		}

		iterator begin();
		iterator begin()const;
		value_type front(){
			return *begin();
		}

		value_type back();

		iterator end(){
			return iterator();
		}

		void resize(size_type new_size);
		pair<iterator, bool> insert_unique_noresize(const value_type& val);
		pair<iterator, bool> insert_equal_noresize(const value_type& val);
		void clear();
		void copy_from(hashtable& others);
		void print();
		iterator find(const key_type& val);
		size_type count(const value_type& val);

		template<class Iterator>
		void insert_unique(Iterator first, Iterator last);

		template<class Iterator>
		void insert_equal(Iterator first, Iterator last);

		pair<iterator, iterator> equal_range(const key_type& key);

		void erase(const iterator& pos);

		size_type erase(const key_type& val);

		void erase(const iterator& first, const iterator& last);


		size_t bkt_num_val(const value_type& val){ return bkt_num_val(val, buckets.size()); }
		size_t bkt_num_val(const value_type& val, size_t n){ return bkt_num(get_key(val), n); }
		size_t bkt_num(const key_type& k){ return bkt_num(k, buckets.size()); }
		size_t bkt_num(const key_type& k, size_t n){ return hash(k) % n; }


	protected:
		//配置单个链表节点空间的函数

		node* new_node(const value_type& _val){
			node *ptr = (node*)Alloc::allocate(1);
			ptr->next = nullptr;
			construct(&(ptr->data), _val);
			return ptr;
		}

		void delete_node(node* ptr){
			destroy(&(ptr->data));
			Alloc::deallocate(ptr);
		}

		
		void _bucket_erase(size_type index, node* first, node* last);
		void _bucket_erase(size_type index, node* first){
			_bucket_erase(index, first, nullptr);
		}
		void _bucket_erase(size_type index){
			_bucket_erase(index, buckets[index], nullptr);
		}

	};









	template<class V, class K, class Hs, class Ex, class Eq, class A>
	typename hashtable<V, K, Hs, Ex, Eq, A>::size_type hashtable<V, K, Hs, Ex, Eq, A>::bucket_count()const{
		size_type n = buckets.size();
		size_type no_empty_bucket_num = 0;

		for (size_t idx = 0; idx < n; idx++)
		{
			if (buckets[idx]){
				no_empty_bucket_num++;
			}

		}
		return no_empty_bucket_num;
	}


	template<class V, class K, class Hs, class Ex, class Eq, class A>
	void hashtable<V, K, Hs, Ex, Eq, A>::resize(size_type new_size){
		size_type old_size = buckets.size();

		if (new_size > old_size){
			size_type n = next_size(old_size);
			if (n > old_size){
				vector<node*> tmp(n, nullptr);

				//re-connect the hash_node in the new bucket
				for (size_t idx = 0; idx != old_size; ++idx) {
					node* cur = buckets[idx];

					while (cur) {
						size_t new_idx = bkt_num(get_key(cur->data), n);
						buckets[idx] = cur->next;
						cur->next = tmp[new_idx];
						tmp[new_idx] = cur;

						cur = buckets[idx];
					}
				}
				tmp.swap(buckets);
			}
		}
	}


	template<class V, class K, class Hs, class Ex, class Eq, class A>
	pair<typename hashtable < V, K, Hs, Ex, Eq, A >::iterator, bool> hashtable < V, K, Hs, Ex, Eq, A >::insert_unique_noresize(const value_type& val){
		size_t insert_position = bkt_num_val(val);

		//if exist same value in the bucket, return without any operation
		for (node* cur = buckets[insert_position]; cur; cur = cur->next) {
			if (equals(get_key(cur->data), get_key(val))){
				return make_pair(iterator(cur, this), false);
			}
		}

		node* tmp = new_node(val);
		tmp->next = buckets[insert_position];
		buckets[insert_position] = tmp;
		++num_elements;
		return make_pair(iterator(tmp, this), true);
	}

	template<class V, class K, class Hs, class Ex, class Eq, class A>
	pair<typename hashtable < V, K, Hs, Ex, Eq, A >::iterator, bool> hashtable < V, K, Hs, Ex, Eq, A >::insert_equal_noresize(const value_type& val){
		size_t insert_position = bkt_num_val(val);

		//if exist same value in the bucket, return without any operation
		for (node* cur = buckets[insert_position]; cur; cur = cur->next) {
			if (equals(get_key(cur->data), get_key(val))){
				node* tmp = new_node(val);
				tmp->next = cur->next;
				cur->next = tmp;
				++num_elements;
				return make_pair(iterator(tmp, this), true);
			}
		}

		node* tmp = new_node(val);
		tmp->next = buckets[insert_position];
		buckets[insert_position] = tmp;
		++num_elements;
		return make_pair(iterator(tmp, this), true);
	}

	template<class V, class K, class Hs, class Ex, class Eq, class A>
	void hashtable < V, K, Hs, Ex, Eq, A >::clear(){
		size_t n = buckets.size();

		for (size_t idx = 0; idx < n; idx++)
		{
			node* cur = buckets[idx];

			while (cur){
				node* nxt = cur->next;
				delete_node(cur);
				nxt = cur;
			}
		}
		num_elements = 0;
	}

	//base copy function for hash table
	template<class V, class K, class Hs, class Ex, class Eq, class A>
	void hashtable < V, K, Hs, Ex, Eq, A >::copy_from(hashtable& others){
		clear();
		size_t n = others.buckets.size();
		buckets.resize(n);

		for (size_t idx = 0; idx < n; idx++)
		{
			const node* cur = others.buckets[idx];
			if (cur){
				node* copy = new_node(cur->data);
				buckets[idx] = copy;
				cur = cur->next;
				while (cur) {
					copy->next = new_node(cur->data);
					copy = copy->next;
					cur = cur->next;
				}
			}
		}
		num_elements = others.num_elements;
	}

	template<class V, class K, class Hs, class Ex, class Eq, class A>
	void hashtable < V, K, Hs, Ex, Eq, A >::print(){
		size_t n = buckets.size();

		for (size_t idx = 0; idx < n; idx++)
		{
			node *cur = buckets[idx];
			while (cur) {
				cout << (this->get_key(cur->data)) << " ";
				cur = cur->next;
			}
		}
		cout << endl;
	}
	template<class V, class K, class Hs, class Ex, class Eq, class A>
	typename hashtable < V, K, Hs, Ex, Eq, A >::iterator hashtable < V, K, Hs, Ex, Eq, A >::find(const key_type& val){
		size_t n = buckets.size();

		for (size_t idx = 0; idx < n; idx++)
		{
			node* cur = buckets[idx];

			while (cur) {
				if (this->equals(val, this->get_key(cur->data))){
					return iterator(cur, this);
				}
				cur = cur->next;
			}

		}

		return iterator();
	}

	template<class V, class K, class Hs, class Ex, class Eq, class A>
	typename hashtable < V, K, Hs, Ex, Eq, A >::size_type hashtable < V, K, Hs, Ex, Eq, A >::count(const value_type& val){
		size_t n = buckets.size();

		size_type num_equals = 0;
		for (size_t idx = 0; idx < n; idx++)
		{
			node* cur = buckets[idx];
			while (cur) {
				if (this->equals(this->get_key(val), this->get_key(cur->data))){
					num_equals++;
				}
				cur = cur->next;
			}

		}
		return num_equals;
	}

	template<class V, class K, class Hs, class Ex, class Eq, class A>
	typename hashtable < V, K, Hs, Ex, Eq, A >::iterator hashtable < V, K, Hs, Ex, Eq, A >::begin(){
		size_t n = buckets.size();

		for (size_t idx = 0; idx < n; idx++)
		{
			if (node* cur = buckets[idx]){
				return iterator(cur, this);
			}
		}

		return iterator();
	}

	template<class V, class K, class Hs, class Ex, class Eq, class A>
	typename hashtable < V, K, Hs, Ex, Eq, A >::iterator hashtable < V, K, Hs, Ex, Eq, A >::begin() const {
		size_t n = buckets.size();

		if (this->num_elements == 0){
			return iterator();
		}
		else{
			for (size_t idx = 0; idx < n; idx++)
			{
				if (const node* cur = buckets[idx]){
					return iterator(cur, this);
				}
			}
		}
		return iterator();
	}

	template<class V, class K, class Hs, class Ex, class Eq, class A>
	typename hashtable < V, K, Hs, Ex, Eq, A >::value_type hashtable < V, K, Hs, Ex, Eq, A >::back(){
		size_t n = buckets.size();

		for (size_t idx = 0; idx < n; idx++)
		{
			size_t cur_idx = n - 1 - idx;
			node* cur = buckets[cur_idx];
			if (cur){
				while (cur->next) {
					cur = cur->next;
				}

				return cur->data;
			}

		}

		return V();
	}

	template<class V, class K, class Hs, class Ex, class Eq, class A>
	template<class Iterator>
	void hashtable < V, K, Hs, Ex, Eq, A >::insert_unique(Iterator first, Iterator last){
		size_t new_add = size_t(distance(first, last));
		resize(this->num_elements + new_add);

		while (first != last) {
			insert_unique_noresize(*first);
			++first;
		}
	}


	template<class V, class K, class Hs, class Ex, class Eq, class A>
	template<class Iterator>
	void hashtable < V, K, Hs, Ex, Eq, A >::insert_equal(Iterator first, Iterator last){
		size_t new_add = size_t(distance(first, last));
		resize(this->num_elements + new_add);

		while (first != last) {
			insert_equal_noresize(*first);
			++first;
		}
	}


	template<class V, class K, class Hs, class Ex, class Eq, class A>
	pair<typename hashtable < V, K, Hs, Ex, Eq, A >::iterator, typename hashtable < V, K, Hs, Ex, Eq, A >::iterator> hashtable < V, K, Hs, Ex, Eq, A >::equal_range(const key_type& key){

		if (this->num_elements == 0){
			return pair<iterator, iterator>(iterator(), iterator());
		}

		size_type n = buckets.size();
		size_type pos = bkt_num(key);
		node* cur = this->buckets[pos];

		while (cur) {

			if (this->equals(key, get_key(cur->data))){
				iterator first(cur, this);
				cur = cur->next;

				while (cur && this->equals(key, get_key(cur->data))) {
					cur = cur->next;
				}

				if (cur){
					iterator last(cur, this);
					return pair<iterator, iterator>(first, last);
				}
				else{
					while (!cur && ++pos < buckets.size()){
						cur = buckets[pos];
					}
					iterator last(cur, this);
					return pair<iterator, iterator>(first, last);
				}
			}
			cur = cur->next;
		}
		return pair<iterator, iterator>(iterator(), iterator());
	}

	template<class V, class K, class Hs, class Ex, class Eq, class A>
	void hashtable < V, K, Hs, Ex, Eq, A >::_bucket_erase(size_type index, node* first, node* last)
	{

		if (first == last){ return; }

		node* cur = buckets[index];
		if (cur){
			node* nxt = cur->next;
			if (first == cur){
				while (cur && cur != last){
					nxt = cur->next;
					delete_node(cur);
					cur = nxt;
				}
				buckets[index] = last;
			}
			else
			{
				while (cur && cur->next != first) {
					cur = cur->next;
				}

				if (!cur){
					node* prev = cur;
					while (cur && cur != last) {
						nxt = cur->next;
						delete_node(cur);
						cur = nxt;
					}
					prev->next = last;
				}

			}
		}
	}

	template<class V, class K, class Hs, class Ex, class Eq, class A>
	void hashtable < V, K, Hs, Ex, Eq, A >::erase(const iterator& pos){
		node* ptr = pos.current_node;
		if (ptr == nullptr){
			return;
		}

		size_type b_index = bkt_num(get_key(ptr->data));

		node* cur = buckets[b_index];
		if (cur == nullptr){
			return;
		}

		if (ptr == cur){
			buckets[b_index] = cur->next;
			delete_node(cur);
			--this->num_elements;
		}
		else{
			node* nxt = cur->next;
			while (nxt) {
				if (ptr == nxt){
					cur->next = nxt->next;
					delete_node(nxt);
					--num_elements;
					return;
				}
				else{
					cur = nxt;
					nxt = cur->next;
				}
			}
		}
	}

	template<class V, class K, class Hs, class Ex, class Eq, class A>
	typename hashtable < V, K, Hs, Ex, Eq, A >::size_type hashtable < V, K, Hs, Ex, Eq, A >::erase(const key_type& key){
/*
		if (this->num_elements == 0){
			return 0;
		}

		size_type num_find = 0;
		size_type b_index = bkt_num(key);
		node* cur = buckets[b_index];

		if (!cur){
			node *nxt = cur->next;
			if (equals(get_key(cur->data), key)){ //since the structure is a slist, change of first node result change of element in buckets vector
				delete_node(cur);
				++num_find;

				while (nxt && equals(get_key(nxt->data), key)) { //find the same key in the bucket
					cur = nxt;
					nxt = nxt->next;
					delete_node(cur);
					++num_find;
				}
				buckets[b_index] = nxt;
			}
			else{

				while (nxt && !equals(get_key(nxt->data), key)) { //find in the bucket;
					cur = nxt;
					nxt = nxt->next;
				}

				if (nxt == nullptr){ //if not find the same key;
					break;
				}
				else{

					node* prev = cur;
					while (nxt && equals (get_key(nxt->data), key)) {
						cur = nxt;
						nxt = nxt->next;
						delete_node(cur);
						++num_find;
					}
					
					prev->next = nxt;
				}
			}
		}
		num_elements -= num_find;
		return num_find;*/
		size_type num_find = 0;
		if (num_elements == 0){
			return num_find;
		}
		size_type b_index = bkt_num(key);
		node* first = buckets[b_index];
		if (first){//if bucket slot is not empty;
			node* cur = first;
			node* nxt = first->next;
			while (nxt) {//search in the bucket
				if (equals(get_key(nxt->data), key)){
					cur->next = nxt->next;
					delete_node(nxt);
					++num_find;
					nxt = cur->next;
				}
				else{
					cur = nxt;
					nxt = cur->next;
				}

			}
			if (equals(get_key(first->data), key)){ //if first node of the bucket is same with the key
				buckets[b_index] = first->next;
				delete_node(first);
				++num_find;
			}
		}

		num_elements -= num_find;
		return num_find;
	}


	template<class V, class K, class Hs, class Ex, class Eq, class A>
	void hashtable < V, K, Hs, Ex, Eq, A >::erase(const iterator& first, const iterator& last){
		if (first == last){
			return;
		}

		node* first_node = first.current_node;
		node* last_node = last.current_node;
		//buckets slot of two iterator;
		size_type first_index = !first_node ? buckets.size() : bkt_num_val(first_node->data); 
		size_type last_index = !last_node ? buckets.size() : bkt_num_val(last_node->data);

		if (first_index == last_index){
			this->_bucket_erase(first_index, first_node, last_node);
		}
		else if (first_index < last_index){
			_bucket_erase(first_index, first_node);

			for (size_type cur_index = first_index + 1; cur_index < last_index; ++cur_index) {
				_bucket_erase(cur_index);
			}

			if (last_index != buckets.size()){
				_bucket_erase(last_index, buckets[last_index], last_node);
			}
		}
	}

}




#endif