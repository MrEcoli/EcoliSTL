#ifndef _ECSTL_HASHMAP_H
#define _ECSTL_HASHMAP_H

#include "vector.h"

//EcSTL��hashtable���ÿ��������primer cluster
//hashtableͨ��һ��vector����bucket
//ÿһ��bucket�ﶼά����һ������
//ͨ�������ģ�����HashFcnȷ��Key���ڵ�bucket��λ�ã�Ȼ�������bucket�н��в���
//iterator ������Ҫ��������ָ���node�ڵ��ָ�룬ͬʱҲҪ��������hashtable��ָ�룬ForwardIterator�Ļ������ܣ���bucket��ĩβΪ�յ�����£�ָ����һ��bucket��

namespace EcSTL{

	//hashtable�нڵ�Ķ���

	template<class _Ty>
	struct _hash_node{
		_hash_node* next;
		data _Ty;
	};

	//hashtable�е������Ķ���

	template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
	struct _hash_iterator{
		//iterator �ͱ�����;
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

		//��ǰ��ָ��Ľڵ�
		node* current_node;

		//��ǰ���ڵ�hashtable��ַ
		hashtable* ht;

		//���캯��

		_hash_iterator(node* given_node, hashtable* given_ht) :current_node(given_node), ht(given_ht){}

		_hash_iterator() :current_node(nullptr), ht(nullptr) {}

		//���Զ���Ϊconst,��Ϊ�ò�������ı� current_node��ht������
		reference operator*()const{
			return current_node->data;
		}

		//���Զ���Ϊconst,��Ϊ�ò�������ı� current_node��ht������
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
		//���ﱣ�����iterator�������Ԫ��������ָ��
		//��������Value��ԭ���ǣ�����Value���Ϳ�����Ҫ���ô�������Դ��

		iterator origin = current_node;
		current_node = current_node->next;

		//���bucket�������ѿ�
		if (!current_node){
			size_type bucket_position = ht->bkt_num(origin->data);

			while (!current_node && ++bucket_position < ht->buckets.size()){
				current_node = ht->buckets[bucket_position];
			}
		}

		return *this;
	}

	//����Ϊ��������
	template<class V, class K, class Hf, class Exk, class Eqk, class A>
	inline _hash_iterator<V, K, Hf, Exk, Eqk, A>& _hash_iterator<V, K, Hf, Exk, Eqk, A>::operator++(int){

		iterator ret = *this;

		this->operator++();

		return ret;
	}


	//hashtable�Ķ���

	template<class Value, class Key, class HashFunc, class ExtractKey, class EqualKey, class Alloc = allocator<_hash_node<Value>>>
	class hashtable{
	public:
		typedef HashFunc hasher;
		typedef EqualKey key_equal;
		typedef size_t size_type;
		typedef _hash_iterator<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc> iterator;
		typedef Value value_type;

	private:
		//hashtable�����ݳ�Ա
		//hash����������ȷ��Value��λ��
		hasher hash;
		//���ڱȽ�keyֵ�Ƿ���ͬ�ķº���
		key_equal equals;
		//�Ƚ�ֵ��С�ķº���
		ExtractKey get_key;

		typedef _hash_node<Value> node;
		typedef Alloc node_allocator;

		//vector���ڴ洢����Ԫ�صĴ洢��vector�е�λ����hash����/�º�������
		vector<node*> buckets;
		//�洢��Ԫ�ص���Ŀ
		size_type num_elements;

	public:

		//hashtable��Ԫ�ص���Ŀ
		size_type size()const{ return num_elements; }

		//�������Ŀ
		size_type bucket_count()const { return buckets.size(); }


	protected:
		//���õ�������ڵ�ռ�ĺ���

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