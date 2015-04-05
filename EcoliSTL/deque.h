#ifndef _ECSTL_DEQUE_H
#define _ECSTL_DEQUE_H
#include "construct.h"
#include "algorithm.h"
#include <stdlib.h>
#include "iterator.h"
#include "_type_trait.h"

//deque是一种，通过一个“map”，将多个内存块缓冲区模拟成一个整体的数组的数据结构
//它的优点是适合在头尾进行删除增加，时间复杂度为O(1)，同时又与vector类似，不适合在中间进行插入数据，时间复杂度为O(n)
//它的iterator的tag虽然为random_accesss，但是需要维护的成本是较高的。


namespace EcSTL{


	template<class T, class Ref = T&, class Ptr = T*, size_t BufSize = 0>
	class _deque_iterator{
	public:
		//型别声明
		typedef _deque_iterator<T, T&, T*, BufSize> iterator;
		typedef random_access_iterator_tag iterator_category;
		typedef size_t size_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef T** map_pointer;
		typedef ptrdiff_t difference_type;
		typedef _deque_iterator<T, Ref, Ptr, BufSize> self;

		static size_t buffer_sz(){ return _deque_buf_size(BufSize, sizeof(T)); }

		//当前iterator指向的位置的指针
		pointer cur;

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
			last = first + difference_type(buffer_sz());
		}



		//operator =
		_deque_iterator& operator=(const _deque_iterator& rhs){
			node = rhs.node;
			first = rhs.first;
			last = rhs.last;
			cur = rhs.cur;
			return *this;
		}


		//random_access_iterator的之间能够直接计算距离
		//两个iterator之间的距离由他们在各自的内存区域中的位置，以及他们所处内存块在map列表中的距离共同决定
		difference_type operator-(const iterator& rhs)const{

			return ((difference_type)buffer_sz())*(node - rhs.node - 1) + (cur - first) + (rhs.last - rhs.cur);


		}

		//迭代器前进/退后一位，需要考虑的是，如果cur指向内存块结束或是first之前，需要set_node
		iterator& operator++(){
			++cur;
			if (cur == last){
				set_node(node + 1);
				cur = first;
			}
			return *this;
		}

		iterator operator++(int){
			iterator tmp = *this;
			this->operator++();
			return tmp;
		}


		iterator& operator--(){
			if (cur == first){
				set_node(node - 1);
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

		//返回引用类型, 可以重复赋值
		iterator& operator+=(difference_type n){

			difference_type offset = n + (cur - first);
			difference_type node_offset = 0;

			if (offset >= 0 && offset <(difference_type)(buffer_sz())){
				cur += n;
				return *this;
			}
			else if (offset < 0){
				node_offset = (offset + 1) / (difference_type(buffer_sz())) - 1;
			}
			else{
				node_offset = offset / (difference_type(buffer_sz()));
			}

			set_node(node + node_offset);
			
			cur = first + (offset - node_offset *(difference_type(buffer_sz())));
			return *this;
		}

		iterator& operator-=(difference_type n){
			return this->operator+=(-n);
		}

		//因为未改变原始对象，所以可以重载为const
		//返回类型是一个右值，所以不是引用类型的
		iterator operator-(difference_type n)const{
			iterator tmp = *this;
			return tmp -= n;
		}

		iterator operator+(difference_type n)const{
			iterator tmp = *this;
			return tmp += n;
		}

		reference operator[](difference_type n){
			return *(*this + n);
		}

		bool operator==(const iterator& rhs)const{
			return cur == rhs.cur;
		}

		bool operator!=(const iterator& rhs)const{
			return cur != rhs.cur;
		}

		bool operator<(const iterator& rhs)const{
			return node < rhs.node || (node == rhs.node && cur < rhs.cur);
		}

		bool operator<=(const iterator& rhs)const{
			return node < rhs.node || (node == rhs.node && cur <= rhs.cur);
		}


		bool operator>=(const iterator& rhs)const{
			return node > rhs.node || (node == rhs.node && cur >= rhs.cur);
		}

		reference operator*(){ return *cur; }
		pointer operator->(){ return cur; }

		void swap(iterator& rhs){
			EcSTL::swap(cur, rhs.cur);
			EcSTL::swap(first, rhs.first);
			EcSTL::swap(last, rhs.last);
			EcSTL::swap(node, rhs.node);

		}

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
		typedef _deque_iterator<T, T&, T*, BufSize> iterator;
		typedef deque<T, Alloc, BufSize> self;

	protected:

		//数据成员与性别声明；

		typedef pointer* map_pointer;
		//指向内存区块的指针的指针
		map_pointer map;
		//指向内存区块的指针的数目
		size_type map_size;

		//维护两个迭代器，分别指向deque的第一个缓冲区的第一个元素，以及最后一个缓冲区的最后一个元素的下一个位置，前闭后开
		iterator start;
		iterator finish;

		//deque除了要进行对象的分配，还要进行map指针数组的分配
		//因而除了给予的默认的Alloc外，deque需要定义一个分配map_pointer的allocatorallocator

		typedef allocator<pointer> map_pointer_allocator;
		typedef Alloc data_allocator;

	public:

		//constructor
		deque(size_type n, const T& v) :start(), finish(), map(0), map_size(0){
			fill_initialize(n, v);
		}

		//constructor

		deque(){
			creat_map_and_node(0);
		}

		//assignment operator

		self& operator=(const self& rhs){
			size_type n = rhs.size();
			self tmp;
			tmp.creat_map_and_node(n);
			copy(rhs.begin(), rhs.end(), tmp.begin());
			this->swap(tmp);
			return *this;
		}

		deque(const self& others){
			size_type n = others.size();
			creat_map_and_node(n);
			copy(others.begin(), others.end(), begin());
		}


		//destructor

		~deque(){

			//调用destroy，析构所有的容器成员
			destroy(begin(), end());
			//释放所有分配的内存块
			map_pointer cur;
			for (cur = start.node; cur != finish.node; ++cur) {
				data_allocator::deallocate(*cur, buf_sz());
			}

			//释放存储map_pointer的动态数组
			map_pointer_allocator::deallocate(map, map_size);

		}



		//常用接口
		iterator begin(){ return start; }
		iterator begin()const{ return start; }
		iterator end(){ return finish; }
		iterator end()const{ return finish; }
		reference front(){ return *start; }
		reference back(){ return *(--end()); }
		size_type size()const{ return size_type(end() - begin()); }
		bool empty()const{ return end() == begin(); }
		reference operator[](size_type n){
			return start[n];
		}

		//push_back如果在当前内存区块已经满了的情况下，需要调用push_back_aux;
		void push_back(const value_type& val){
			if (finish.last - 1 != finish.cur){
				construct(finish.cur, val);
				++finish.cur;
			}
			else{
				push_back_aux(val);
			}
		};


		//pop_back function, pop the last member of deque;
		void pop_back(){
			//pop_back need reconstruct the map array
			if (finish.cur == finish.first){
				data_allocator::deallocate(*(finish.node), buf_sz());
				finish.set_node(finish.node - 1);
				finish.cur = finish.last - 1;
				data_allocator::destroy(finish.cur);
			}
			else{

				finish.cur--;
				data_allocator::destroy(finish.cur);

			}

		}


		//push object at front of the deque;
		void push_front(const value_type& val){
			if (start.cur != start.first){
				start.cur--;
				construct(start.cur, val);
			}
			else{
				push_front_aux(val);
			}
		}

		void pop_front(){
			if (start.cur == start.last - 1){
				destory(start.cur, start.cur + 1);
				data_allocator::deallocate(*(start.node), buf_sz());
				start.set_node(start.node + 1);
				start.cur = start.first;
			}
			else{
				destory(start.cur, start.cur + 1);
				start.cur++;
			}

		}



		void swap(deque<T, Alloc, BufSize>& rhs){
			start.swap(rhs.start);
			finish.swap(rhs.finish);
			EcSTL::swap(map, rhs.map);
			EcSTL::swap(map_size, rhs.map_size);
		}

		void print()const;

		void clear();


		//erase the object at the target
		iterator erase(iterator position){
			iterator next = position;
			next++;
			difference_type dis = position - start;

			//destroy the target at the position
			//no need, in the copy function, assignment operator will be used, the object will destruct at that time
			//data_allocator::destroy(&*postion);

			//choose whether move the front part or back part of the deque
			//if distance of postion to start is father than half the size of deque, we choose to move the back part of the deque use copy forward
			if (dis > (size() >> 1)){
				copy(next, finish, position);
				pop_back();
			}
			else{
				//here, we need move the element backward;
				copy_reverse(start, position, next);
				pop_front();
			}
			return start + dis;
		}


		//erase a area;
		iterator erase(iterator pos_start, iterator pos_end);


		iterator insert(iterator pos, const value_type& val){

			if (pos == start){
				push_front(val);
				return start;
			}
			else if (pos == finish){
				push_back(val);
				iterator tmp = finish;
				return --tmp;
			}
			else{
				return insert_aux(pos, val);
			}

		}


		iterator insert_aux(iterator pos, const value_type& val);


		



	protected:
		//最少管理多少块内存块
		enum { _MIN_NODE_SIZE = 8 };
		enum { _DEFAULT_NODE_NUM = 512 };
		enum { _DEFAULT_INCR_SIZE = 2 };

		//

		static size_type buf_sz(){
			return BufSize != 0 ? BufSize : ((sizeof(T) > _DEFAULT_NODE_NUM ? 1 : (_DEFAULT_NODE_NUM / sizeof(T))));
		}

		//构造deque的存储空间，根据所给予的初始化的deque对象成员数目设定
		void creat_map_and_node(size_type n);

		//构造和初始化一个deque
		void fill_initialize(size_type n, const T& val);

		//如果需要在新的内存块中进行push_back，则调用以下函数
		void push_back_aux(const value_type& val);

		void push_front_aux(const value_type& val);

		void deallocate_map_pointer(map_pointer ptr, size_type n){
			map_pointer_allocator::deallocate(ptr, n);
		}


		//在push_back或是push_front或是insert情况中如果需要扩充map_size时,调用函数调整map_pointer数组
		void reserve_map_at_back(size_type num_to_add = 1){

			if (num_to_add > (size_type)(map + map_size - 1 - finish.node)){

				reallocate_map(num_to_add, false);

			}

		}

		void reserve_map_at_front(size_type num_to_add = 1){

			if (num_to_add > (size_type)(map - start.node)){

				reallocate_map(num_to_add, true);
			}

		}

		void reallocate_map(size_type n, bool isFront);



	};


	//allocate the heap memory for map_pointer array and n objects;

	template<class T, class A, size_t BufSize>
	void deque<T, A, BufSize>::creat_map_and_node(size_type n){
		//每个内存块所能放下的对象数目
		size_type bufsize = buf_sz();

		//最少需要多少个内存块
		size_type num_nodes = n / bufsize + 1;
		//分配内存块至少为_MIN_NODE_SIZE或是需要内存块数目+2;
		map_size = (num_nodes + 2) > _MIN_NODE_SIZE ? (num_nodes + 2) : _MIN_NODE_SIZE;

		//分配map_pointer的动态数组
		map = (map_pointer)map_pointer_allocator::allocate(map_size);

		//将deque使用的区段初始化为map的中间区域
		map_pointer node_start = map + (map_size - num_nodes) / 2;
		map_pointer node_end = node_start + num_nodes - 1;

		map_pointer cur;
		for (cur = node_start; cur <= node_end; ++cur) {
			*cur = (pointer)data_allocator::allocate(bufsize);
		}

		start.set_node(node_start);
		finish.set_node(node_end);

		start.cur = start.first;
		finish.cur = finish.first + (n % bufsize);
	}



	//构造deque数据结构
	//初始化容器内的对象
	template<class T, class A, size_t BufSize>
	void deque<T, A, BufSize>::fill_initialize(size_type n, const T& val){

		creat_map_and_node(n);
		uninitialized_fill(start, finish, val);

	}



	template<class T, class A, size_t BufSize>
	void deque<T, A, BufSize>::reallocate_map(size_type num_add, bool isFront){

		size_type old_sz = finish.node - start.node + 1;

		size_type new_sz = old_sz + num_add;

		map_pointer new_start;

		//如果原始的map数组大小完全满足需求，则对map数组进行调整即可
		if (map_size > new_sz * 2){

			new_start = map + (map_size - new_sz) / 2 + (isFront ? num_add : 0);

			//根据newstart的位置确定从前还是从后复制
			if (new_start > start.node){
				copy(start.node, finish.node + 1, new_start);
			}
			else{
				copy_reverse(start.node, finish.node + 1, new_start);
			}

		}
		//重新分配map数组
		else{
			size_type new_map_size = map_size + (map_size > num_add ? map_size : num_add) + 2;

			map_pointer new_map = (map_pointer)map_pointer_allocator::allocate(new_map_size);

			new_start = new_map + (new_map_size - new_sz) / 2 + (isFront ? num_add : 0);

			copy(start.node, finish.node + 1, new_start);

			map_pointer_allocator::deallocate(map, map_size);
			map = new_map;
			map_size = new_map_size;
		}

		start.set_node(new_start);
		finish.set_node(new_start + old_sz - 1);
	}



	template<class T, class A, size_t BufSize>
	void deque<T, A, BufSize>::push_back_aux(const value_type& val){
		//no postion at the end of map, adjust the map array or reconstruct the map array

		reserve_map_at_back();

		//分配新的内存块
		*(finish.node + 1) = (pointer)data_allocator::allocate(buf_sz());

		//在原来的位置上构造对象，因为是前闭后开，finish.cur指向的位置时未构造元素的
		construct(finish.cur, val);
		//重新设定finish
		finish.set_node(finish.node + 1);
		finish.cur = finish.first;

	}

	template<class T, class A, size_t BufSize>
	void deque<T, A, BufSize>::push_front_aux(const value_type& val){
		//reconstruction of map array
		//more space at front
		reserve_map_at_front();

		//allocate memory
		*(start.node - 1) = (pointer)data_allocator::allocate(buf_sz());
		//initialize the iterator start
		start.set_node(start.node - 1);
		start.cur = start.last - 1;

		//construct the object at the start.cur;
		construct(start.cur, val);
	}


	//print the deque, not the standard port of STL deque
	template<class T, class A, size_t BufSize>
	void deque<T, A, BufSize>::print() const {

		for (iterator it = begin(); it != end(); ++it) {
			cout << (*it) << " ";
		}

		cout << endl;
	}

	//clear the deque, destroy all the objects and deallocate the resource
	template<class T, class A, size_t BufSize>
	void deque<T, A, BufSize>::clear(){

		for (map_pointer cur_node = start.node + 1; cur_node < finish.node; ++cur_node){
			destroy(*cur_node, *cur_node + buf_sz());
			data_allocator::deallocate(*cur_node, buf_sz());
		}

		if (start.node != finish.node){
			destroy(start.cur, start.last);
			destroy(finish.first, finish.cur);
			//keep the memory chunk of start.node;
			data_allocator::deallocate(finish.first, buf_sz());
		}
		else{
			destroy(start.cur, finish.cur);
		}
		//set the iterator
		finish = start;
	}


	//erase a area indiacte by two iterator
	template<class T, class A, size_t BufSize>
	typename deque<T, A, BufSize>::iterator deque<T, A, BufSize>::erase(iterator pos_start, iterator pos_end){
		//size of erase area;
		size_type n = pos_end - pos_start;

		size_type front_sz = pos_start - start;
		size_type back_sz = finish - pos_end;


		//Global function

		//choose which direction we move the deque;
		if (front_sz > back_sz){
			//move the element use copy function
			copy(pos_end, finish, pos_start);
			iterator new_finish = finish - n;

			//destroy the no use area;
			destroy(new_finish, finish);

			//deallocate the unuse memory;
			for (map_pointer cur_node = new_finish.node + 1; cur_node <= finish.node; ++cur_node) {
				data_allocator::deallocate(*cur_node, buf_sz());
			}
			new_finish = finish;
		}
		else{
			copy_reverse(start, pos_start, pos_end);
			iterator new_start = start + n;
			destroy(start, new_start);

			for (map_pointer cur_node = start.node; cur_node < new_start.node; ++cur_node) {
				data_allocator::deallocate(*cur_node, buf_sz());
			}
		}

		return start + front_sz;
	}


	//if insert position is located "in the deque"
	template<class T, class A, size_t BufSize>
	typename deque<T, A, BufSize>::iterator deque<T, A, BufSize>::insert_aux(iterator pos, const value_type& val){
		size_type start_dis = pos - start;
		size_type finish_dis = finish - pos;

		//remember the index of insert position in the deque, because the push operator may result the change of data member node of the iterator;
		difference_type index = pos - start;

		//make choose which part to copy

		if (start_dis > finish_dis){
			push_back(back());
			iterator old_finish = prev(finish);
			copy_reverse(start + index, old_finish, finish);
			pos = start + index;
		}
		else{
			push_front(front());
			print();
			iterator old_start = start;
			old_start++;

			copy(old_start, old_start + index, start);
			pos = start + index;
		}

		*pos = val;
		return pos;
	}

}



#endif