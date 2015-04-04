#ifndef _ECSTL_DEQUE_H
#define _ECSTL_DEQUE_H
#include "construct.h"
#include "algorithm.h"
#include <stdlib.h>
#include "iterator.h"
#include "_type_trait.h"

//deque��һ�֣�ͨ��һ����map����������ڴ�黺����ģ���һ���������������ݽṹ
//�����ŵ����ʺ���ͷβ����ɾ�����ӣ�ʱ�临�Ӷ�ΪO(1)��ͬʱ����vector���ƣ����ʺ����м���в������ݣ�ʱ�临�Ӷ�ΪO(n)
//����iterator��tag��ȻΪrandom_accesss��������Ҫά���ĳɱ��ǽϸߵġ�


namespace EcSTL{


	template<class T, class Ref = T&, class Ptr = T*, size_t BufSize = 0>
	class _deque_iterator{
	public:
		//�ͱ�����
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

		//��ǰiteratorָ���λ�õ�ָ��
		pointer cur;

		//��ǰ����������ڴ�ͷβָ��
		pointer first;
		pointer last;

		//���ڵ�deque��map_pointer

		map_pointer node;

		//��������iterator��ָ����ڴ��
		//��operator++�� operator--��������ڿ��ڴ��������Ϊʱʹ��
		void set_node(map_pointer new_node){
			node = new_node;
			first = *new_node;
			last = first + difference_type(buffer_sz());
		}


		
		
		//random_access_iterator��֮���ܹ�ֱ�Ӽ������
		//����iterator֮��ľ����������ڸ��Ե��ڴ������е�λ�ã��Լ����������ڴ����map�б��еľ��빲ͬ����
		difference_type operator-(const iterator& rhs)const{
			return ((difference_type)buffer_sz())(this->node - rhs->node - 1) + (first - cur) + (rhs->last - rhs->cur);
		}
		
		//������ǰ��/�˺�һλ����Ҫ���ǵ��ǣ����curָ���ڴ���������first֮ǰ����Ҫset_node
		iterator& operator++(){
			++cur;
			if (cur == last){
				set_node(node+1);
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
		
		//������������, �����ظ���ֵ
		iterator& operator+=(difference_type dif){
			if (dif + cur < last && dif + cur >= first){
				cur += dif;
				return *this;
			}
			else{
				difference_type offset = dif + (cur - first);
				difference_type node_offset = offset >= 0 ? offset / buffer_sz() : ((offset + 1) / buffer_sz() - 1);
				set_node(node + node_offset);
				cur = first + (dif - node_offset* buffer_sz());
				return *this;
			}
		}

		iterator& operator-=(difference_type dif){
			return this->operator+=(-n);
		}

		//��Ϊδ�ı�ԭʼ�������Կ�������Ϊconst
		//����������һ����ֵ�����Բ����������͵�
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

		reference operator*(){ return *cur;}
		pointer operator->(){ return cur; }

		void swap(iterator& rhs){
			EcSTL::swap(cur, rhs.cur);
			EcSTL::swap(first, rhs.first);
			EcSTL::swap(last, rhs.last);
			EcSTL::swap(node, rhs.node);

		}

	};

	//һ��ȫ�ֺ�����ͨ��������ģ����ͱ����BufSizeȷ��deque���ڴ��Ĵ�С��BufSizeĬ��Ϊ0���ڴ��Ĭ�ϴ�СΪ512bytes�������ڴ���п��Է��ö��ٸ��洢�Ķ���
	//��������С����512,�����һ������
	inline size_t _deque_buf_size(size_t n, size_t sz){
		return n != 0 ? n : (sz >= 512 ? 1 : (512 / sz));
	}


	//���������ͱ������ʾ�������Ĵ�С
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

		//���ݳ�Ա���Ա�������

		typedef pointer* map_pointer;
		//ָ���ڴ������ָ���ָ��
		map_pointer map;
		//ָ���ڴ������ָ�����Ŀ
		size_type map_size;

		//ά���������������ֱ�ָ��deque�ĵ�һ���������ĵ�һ��Ԫ�أ��Լ����һ�������������һ��Ԫ�ص���һ��λ�ã�ǰ�պ�
		iterator start;
		iterator finish;

		//deque����Ҫ���ж���ķ��䣬��Ҫ����mapָ������ķ���
		//������˸����Ĭ�ϵ�Alloc�⣬deque��Ҫ����һ������map_pointer��allocatorallocator

		typedef allocator<pointer> map_pointer_allocator;
		typedef Alloc data_allocator;

	public:	

		//constructor
		deque(size_type n, const T& v):start(), finish(), map(0), map_size(0){
			fill_initialize(n, v);
		}

		//constructor

		deque(){}


		//destructor

		~deque(){

			//����destroy���������е�������Ա
			destroy(begin(), end());
			//�ͷ����з�����ڴ��
			map_pointer cur;
			for (cur = start.node; cur != finish.node; ++cur) {
				data_allocator::deallocate(*cur, buf_sz());
			}
			
			//�ͷŴ洢map_pointer�Ķ�̬����
			map_pointer_allocator::deallocate(map_pointer, map_size);

		}



		//���ýӿ�
		iterator begin(){ return start; }
		iterator end(){ return finish; }
		reference front(){ return *start; }
		reference back(){ return *(--end()); }
		void size()const{ return end() - begin(); }
		void empty()const{ return end() == begin(); }
		reference operator[](size_type n){
			return start[n];
		}

		//push_back����ڵ�ǰ�ڴ������Ѿ����˵�����£���Ҫ����push_back_aux;
		void push_back(const value_type& val){
			if (finish.last - 1 != finish.cur){
				construct(finish.cur, val);
				++finish.cur;
			}
			else{
				push_back_aux(val);
			}
		};

		

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

		}
		void pop_back();

		void insert(iterator postion, const T& _val){

		};

		void swap(deque<T, Alloc, BufSize>& rhs){
			start.swap(rhs.swap);
			finish.swap(rhs.swap);
			EcSTL::swap(map, rhs.map);
			EcSTL::swap(map_size, rhs.map_size);
		}

	protected:
		//���ٹ�����ٿ��ڴ��
		enum {_MIN_NODE_SIZE = 8};
		enum {_DEFAULT_NODE_NUM = 512};
		enum {_DEFAULT_INCR_SIZE = 2};

		//

		static size_type buf_sz(){
			return BufSize != 0 ? BufSize : ((sizeof(T) > _DEFAULT_NODE_NUM ? 1 : (_DEFAULT_NODE_NUM / sizeof(T))));
		}

		//����deque�Ĵ洢�ռ䣬����������ĳ�ʼ����deque�����Ա��Ŀ�趨
		void creat_map_and_node(size_type n);

		//����ͳ�ʼ��һ��deque
		void fill_initialize(size_type n, const T& val);

		//�����Ҫ���µ��ڴ���н���push_back����������º���
		void push_back_aux(const value_type& val);

		void push_front_aux(const value_type& val);
		
		void deallocate_map_pointer(map_pointer ptr, size_type n){
			map_pointer_allocator::deallocate(ptr, n);
		}


		//��push_back����push_front����insert����������Ҫ����map_sizeʱ,���ú�������map_pointer����
		void reserve_map_at_back(size_type num_to_add = 1){

			if (num_to_add > (map + map_size - 1 -finish.node)){

				reallocate_map(map_size + num_to_add, false);

			}

		}

		void reserve_map_at_front(size_type num_to_add = 1){

			if (num_to_add > (map - start.node)){

				reallocate_map(map_size + num_to_add, true);
			}


		}

		void reallocate_map(size_type n, bool isFront);
	};

	//�����洢n�������deque�ռ�
	//��ʼ��deque�����ݳ�Ա

	template<class T, class A, size_t BufSize>
	void deque<T, A, BufSize>::creat_map_and_node(size_type n){
		//ÿ���ڴ�����ܷ��µĶ�����Ŀ
		size_type bufsize = buf_sz();

		//������Ҫ���ٸ��ڴ��
		size_type num_nodes = n / bufsize + 1;
		//�����ڴ������Ϊ_MIN_NODE_SIZE������Ҫ�ڴ����Ŀ+2;
		map_size = (num_nodes + 2) > _MIN_NODE_SIZE ? (num_nodes + 2) : _MIN_NODE_SIZE;

		//����map_pointer�Ķ�̬����
		map = (map_pointer)map_pointer_allocator::allocate(map_size);
		
		//��dequeʹ�õ����γ�ʼ��Ϊmap���м�����
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

	//����deque���ݽṹ
	//��ʼ�������ڵĶ���
	template<class T, class A, size_t BufSize>
	void deque<T, A, BufSize>::fill_initialize(size_type n, const T& val){
		
		creat_map_and_node(n);
		uninitialized_fill(start, finish, val);

	}

	template<class T, class A, size_t BufSize>
	void deque<T, A, BufSize>::reallocate_map(size_type num_add, bool isFront){

		size_type old_sz = start.node - finish.node + 1;

		size_type new_sz = old_sz + num_add;

		map_pointer new_start;

		//���ԭʼ��map�����С��ȫ�����������map������е�������
		if (map_size > new_sz * 2){
			new_start = map + (map_size - new_sz) / 2 + (isFront ? num_add : 0);


			//����newstart��λ��ȷ����ǰ���ǴӺ���
			if (new_start > start.node){
				copy(start.node, finish.node, new_start);
			}
			else{
				copy_reverse(start.node, finish.node, new_start);
			}

		}
		//���·���map����
		else{
			size_type new_map_size = map_size + max(map_size, num_add) + 2;

			map_pointer new_map = (map_pointer)map_pointer_allocator::allocate(new_map_size);

			new_start = new_map + (new_map_size - num_add) / 2 + (isFront ? num_add : 0);

			copy(start.node, finish.node, new_start);

			map_pointer_allocator::deallocate(map, map_size);
			map = new_map;
			map_size = new_map_size;
		}

		start.set_node(new_start);
		finish.set_node(new_start + old_sz - 1);
	}

	

	






	template<class T, class A, size_t BufSize>
	void deque<T, A, BufSize>::push_back_aux(const value_type& val){
		//���deque��ĩβ�Ѿ�ʹ���������е��ڴ��
		if (map + map_size -1 == finish.node){
			//���deque��ǰ�ε��ڴ�δʹ���꣬���ڴ��ָ��ǰ�ƣ�
			//ǰ��ʹ��copy function, ���򿽱�
			if (map != start.node){
				size_type offset = (map_size - (start.node - finish.node + 1)) / 2;
				copy(start.node, finish.node, map + offset);
				push_back_aux(val);
			}
			//���ǰ��û�пռ��ˣ������¹���һ��map_pointer������
			else{

				size_type new_size = map_size + (_DEFAULT_INCR_SIZE < 1 ? 2 : _DEFAULT_INCR_SIZE);
				map_pointer new_map = (map_pointer)map_pointer_allocator::allocate(new_size);

				//star.node�����new_map��ƫ�ƣ�����2����ʹͷ��ƫ�ƽ�С����ʹֻ����1λ����һλ��ƫ��Ҳ������ͷ��

				size_type offset = (new_size - map_size) / 2;

				//����ԭ����mapָ��
				copy(start.node, finish.node, new_map + offset);

				
				//����ԭ������ĸ�map_pointer�Ķ�̬����
				map_pointer_allocator::deallocate(map, map_size);

				//�������ݳ�Ա

				start.set_node(new_map + offset);
				finish.set_node(start.node + map_size - 1);
				map = new_map;
				map_size = new_size;
				push_back_aux(val);
			}
		}
		//���β��map_pointer�������ٷ���һ���ڴ�������ָ��
		else{

			construct(finish.cur, val);
			*(map + map_size) = data_allocator::allocate(buf_sz());
			
			finish.set_node(*(map + map_size));



		}

	}





}



#endif