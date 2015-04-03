#ifndef _ECSTL_DEQUE_H
#define _ECSTL_DEQUE_H
#include "construct.h"
#include "algorithm.h"

//deque是一种，通过一个“map”，将多个内存块缓冲区模拟成一个整体的数组的数据结构
//它的优点是适合在头尾进行删除增加，时间复杂度为O(1)，同时又与vector类似，不适合在中间进行插入数据，时间复杂度为O(n)
//它的iterator的tag虽然为random_accesss，但是需要维护的成本是较高的。


namespace EcSTL{


	template<class T, class Ref = T&, class Ptr = T*, size_t BufSize>
	class _deque_iterator{
	public:
		//型别声明
		typedef _deque_iterator<T, T&, T*, BufSize> iterator;
		typedef iterator_category random_access_iterator_tag;
		typedef size_t size_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef T** map_pointer;
		typedef ptrdiff_t difference_type;
		typedef _deque_iterator<T, Ref, PTR> self;

		static size_t buffer_sz(){ return _deque_buf_size(BufSize, sizeof(T)); }

		//当前iterator指向的位置的指针
		pointer cur

		//当前所在区块的内存头尾指针
		pointer first;
		pointer last;

		//所在的deque的map_pointer

		map_pointer node;

		//重新设置iterator所指向的内存块
		//在operator++， operator--中如果存在跨内存区块的行为时使用
		void set_node(map_pointer new_node){
			node = new_node;
			first = *new_node;
			last = first + difference_type(buffer_sz);
		}
		
		//random_access_iterator的之间能够直接计算距离
		//两个iterator之间的距离由他们在各自的内存区域中的位置，以及他们所处内存块在map列表中的距离共同决定
		difference_type operator-(const iterator& rhs)const{
			return ((difference_type)buffer_sz())(this->node - rhs->node - 1) + (first - cur) + (rhs->last - rhs->cur);
		}
		
		//迭代器前进/退后一位，需要考虑的是，如果cur指向内存块结束或是first之前，需要set_node
		iterator operator++(){
			++cur;
			if (cur == last){
				set_node(node+1);
			}
			cur = first;
			return *this;
		}
		
		iterator operator++(int){
			iterator tmp = *this;
			this->operator++();
			return tmp;
		}


		iterator operator--(){
			if (cur == first){
				set_node(node-1);
				cur = last - 1;
				return *this;
			}

			--cur;
			return *this;
		}
		iterator operator--(int){
			iterator tmp = *this;
			this->operator--();
			return tmp;
		}
		
		iterator operator+=(difference_type dif){
			if (dif + cur < last && dif + cur >= first){
				cur += dif;
				return *this;
			}
			else{
				difference_type offset = n + (cur - first);
				difference_type node_offset = offset >= 0 ? offset / buffer_sz() : ((offset + 1) / buffer_sz() - 1);
				set_node(node + node_offset);
				cur = first + (dif - node_offset* buffer_sz());
			}
		}


		iterator operator-(size_type);

		reference operator*(){ return *cur;}
		pointer operator->(){ return cur; }


		

	};

	//一个全局函数，通过给定的模板非型别参数BufSize确定deque的内存块的大小，BufSize默认为0，内存块默认大小为512bytes，返回内存块中可以放置多少个存储的对象
	//如果对象大小超过512,则放置一个对象
	inline size_t _deque_buf_size(size_t n, size_t sz){
		return n != 0 ? n : (sz >= 512 ? 1 : (512 / sz));
	}


	//第三个非型别参数表示缓冲区的大小
	template<class T, class Alloc = allocator<T>, size_t BufSize = 0>
	class deque{
	public:
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		
	protected:
		typedef pointer* map_pointer;
		//指向内存区块的指针的指针
		map_pointer map;
		//指向内存区块的指针的数目
		size_type map_size;


	};





}



#endif