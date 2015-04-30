#ifndef _ECSTL_UNORDERED_SET_H
#define _ECSTL_UNORDERED_SET_H
#include "hashtable.h"
#include "functional.h"

namespace EcSTL{


	template<class Value, class HashFunc = hash<Value>, class EqualKey = equal_to<Value>, class Alloc = allocator<_hash_node<Value>>>
	class unordered_set{
	public:
		typedef hashtable<Value, Value, HashFunc, identity<Value>, EqualKey, Alloc> Hashtable;
		typedef unordered_set<Value, HashFunc, EqualKey, Alloc> self;
		typedef typename Hashtable::key_type key_type;
		typedef typename Hashtable::value_type value_type;
		typedef typename Hashtable::iterator iterator;
		typedef typename Hashtable::size_type size_type;
		typedef typename Hashtable::hasher hasher;
		typedef typename Hashtable::key_equal key_equal;

	private:
		Hashtable ht;

	public:
		//constructors
		unordered_set() :ht(100, hasher(), key_equal()){}
		explicit unordered_set(size_type n) :ht(n, hasher(), key_equal()){}
		unordered_set(size_type n, const hasher& hs):ht(n, hs, key_equal()){}
		unordered_set(size_type n, const hasher& hs, const key_equal& ke) :ht(n, hs, ke){}

		template<class Iterator>
		unordered_set(Iterator first, Iterator last):ht(100, hasher(), key_equal()){
			ht.insert_unique(first, last);
		}

		template<class Iterator>
		unordered_set(Iterator first, Iterator last, size_type n):ht(n, hasher(), key_equal()){
			ht.insert_unique(first, last);
		}

		iterator begin(){ return ht.begin(); }
		iterator end(){ return ht.end(); }
		size_type size(){ return ht.size(); }
		void swap(self& others){
			ht.swap(other.ht);
		}
		bool empty()const{
			return ht.empty();
		}

		pair<iterator, bool> insert(const value_type& val){
			pair<iterator, bool> ret = ht.insert_unique(val);
			return pair<iterator, bool>(ret.first, ret.second);
		}
		
		template<class Iterator>
		void insert(Iterator first, Iterator last){
			ht.insert_unique(first, last);
		}

		pair<iterator, bool> insert_noresize(const value_type& val){
			pair<typename ht::iterator, bool> ret = ht.insert_unique_noresize(val);
			return pair<iterator, bool>(ret.first, ret.second);
		}

		iterator find(const value_type& val){
			return ht.find(val);
		}

		size_type count(const value_type& key)const{
			return ht.count(key);
		}

		pair<iterator, iterator> equal_range(const key_type& key)const{
			return ht.equal_range(key);
		}

		size_type erase(const key_type& key){
			return ht.erase(key);
		}

		void erase(iterator it){
			ht.erase(it);
		}
		
		void erase(iterator it1, iterator it2){
			ht.erase(it1, it2);
		}

		void clear(){
			ht.clear();
		}

	};


}
#endif