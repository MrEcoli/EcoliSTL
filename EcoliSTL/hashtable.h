#ifndef _ECSTL_HASHMAP_H
#define _ECSTL_HASHMAP_H

#include "vector.h"

//EcSTL的hashtable采用开链法解决primer cluster
//hashtable通过一个vector保存bucket
//每一个bucket里都维护着一个链表
//通过给予的模板参数HashFcn确定Key所在的bucket的位置，然后在这个bucket中进行插入
//iterator 不单单要保存它所指向的node节点的指针，同时也要保存整个hashtable的指针，ForwardIterator的基本功能，在bucket的末尾为空的情况下，指向下一个bucket。

namespace EcSTL{

	//hashtable中节点的定义

	template<class _Ty>
	struct _hash_node{
		_hash_node* next;
		data _Ty;
	};

	//hashtable中迭代器的定义

	template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
	struct _hash_iterator{
		//iterator 型别声明;
		typedef _hash_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> iterator;
		typedef hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> hashtable;
		typedef _hash_const_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> iterator;
		typedef _hash_node<Value> node;

		typedef iterator_category forward_iterator_tag;
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

		iterator operator++();

		iterator operator++(int);

		bool operator==(const iterator& others){ return current_node == others.current_node; }
		bool operator!=(const iterator& others){ return current_node != others.current_node; }

	};

	template<class V, class K, class Hf, class Exk, class Eqk, class A>
	_hash_iterator<V, K, Hf, Exk, Eqk, A>& _hash_iterator<V, K, Hf, Exk, Eqk, A>::operator++(){
		//这里保存的是iterator，里面的元素是两个指针
		//并不保存Value的原因是，构造Value类型可能需要调用大量的资源。

		iterator origin = current_node;
		current_node = current_node->next;

		//如果bucket的链表已空
		if (!current_node){
			size_type bucket_position = ht->bkt_num(origin->data);

			while (!current_node && ++bucket_position < ht->buckets.size()){
				current_node = ht->buckets[bucket_position];
			}
		}

		return *this;
	}

	//设置为内联函数
	template<class V, class K, class Hf, class Exk, class Eqk, class A>
	inline _hash_iterator<V, K, Hf, Exk, Eqk, A>& _hash_iterator<V, K, Hf, Exk, Eqk, A>::operator++(int){

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

	private:
		//hashtable的数据成员
		//hash函数，用于确定Value的位置
		hasher hash;
		//用于比较key值是否相同的仿函数
		key_equal equals;
		//比较值大小的仿函数
		ExtractKey get_key;

		typedef _hash_node<Value> node;
		typedef Alloc node_allocator;

		//vector用于存储链表，元素的存储在vector中的位置由hash函数/仿函数决定
		vector<node*> buckets;
		//存储的元素的数目
		size_type num_elements;

	public:

		//hashtable中元素的数目
		size_type size()const{ return num_elements; }

		//链表的数目
		size_type bucket_count()const { return buckets.size(); }


	protected:
		//配置单个链表节点空间的函数

		node* new_node(const value_type& _val){
			node *ptr = Alloc::allocate(1);
			node->next = nullptr;
			construct(&(ptr->data), _val);
			return ptr;
		}

		void delete_node(node* ptr){
			destory(&(ptr->data));
			Alloc::deallocate(ptr);
		}











	};





}




#endif