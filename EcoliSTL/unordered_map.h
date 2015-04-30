#ifndef _ECSTL_UNORDERED_MAP_H
#define _ECSTL_UNORDERED_MAP_H
#include "hashtable.h"

namespace EcSTL{
	template<class Key, class T, class HashFunc = hash<Key>, class EqualKey = equal_to<Key>, class Alloc = allocator<_hash_node<pair<Key, T>>>>
	class unordered_map{
	public:
		typedef hashtable<pair<Key, T>, Key, HashFunc, select1st<pair<Key, T>>, EqualKey, Alloc> hashtable;
		typedef typename hashtable::iterator iterator;
		typedef typename hashtable::size_type size_type;
		typedef typename hashtable::value_type value_type;
		typedef typename hashtable::key_type key_type;
		typedef typename hashtable::hasher hasher;
		typedef typename hashtable::key_equal key_equal;
		typedef typename hashtable::node node;
		typedef T data_type;
		typedef T map_type;
		typedef unordered_map<Key, T, HashFunc, EqualKey, Alloc> self;

	private:
		hashtable ht;

	public:

		//constructor
		unordered_map() :ht(50, hasher(), key_equal()){}
		explicit unordered_map(size_type n) :ht(n, hasher(), key_equal()){}

		template<class Iterator>
		unordered_map(Iterator first, Iterator last) : ht(50, hasher(), key_equal()){
			ht.insert_unique(first, last);
		}

		template<class Iterator>
		unordered_map(Iterator first, Iterator last, size_type n) : ht(n, hasher(), key_equal()){
			ht.insert_unique(first, last);
		}


		iterator begin(){ return ht.begin(); }
		iterator end(){ return ht.end(); }

		size_type size()const{ return ht.size(); }
		bool empty()const{ return ht.empty(); }

		self& operator=(const self& others){
			ht = others.ht;
			return *this;
		}

		void swap(self& others){
			ht.swap(others);
		}


		pair<iterator, bool> insert(const value_type& val){
			return ht.insert_unique(val);
		}

		void erase(const key_type& key){
			ht.erase(key);
		}

		void erase(const iterator& it){
			ht.erase(it);
		}

		iterator find(const key_type& key){
			return ht.find(key);
		}

		T& operator[](const key_type& key){
			iterator it = find(key);

			if (it.current_node == nullptr){
				it = insert(value_type(key, T())).first;
				return it->second;
			}
			else{
				return it->second;
			}
		}



	};


}
#endif