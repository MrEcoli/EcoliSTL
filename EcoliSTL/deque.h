#ifndef _ECSTL_DEQUE_H
#define _ECSTL_DEQUE_H
#include "construct.h"
#include "algorithm.h"

//deque��һ�֣�ͨ��һ����map����������ڴ�黺����ģ���һ���������������ݽṹ
//�����ŵ����ʺ���ͷβ����ɾ�����ӣ�ʱ�临�Ӷ�ΪO(1)��ͬʱ����vector���ƣ����ʺ����м���в������ݣ�ʱ�临�Ӷ�ΪO(n)
//����iterator��tag��ȻΪrandom_accesss��������Ҫά���ĳɱ��ǽϸߵġ�


namespace EcSTL{


	template<class T, class Ref = T&, class Ptr = T*, size_t BufSize>
	class _deque_iterator{
	public:
		//�ͱ�����
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

		//��ǰiteratorָ���λ�õ�ָ��
		pointer cur

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
			last = first + difference_type(buffer_sz);
		}
		
		//random_access_iterator��֮���ܹ�ֱ�Ӽ������
		//����iterator֮��ľ����������ڸ��Ե��ڴ������е�λ�ã��Լ����������ڴ����map�б��еľ��빲ͬ����
		difference_type operator-(const iterator& rhs)const{
			return ((difference_type)buffer_sz())(this->node - rhs->node - 1) + (first - cur) + (rhs->last - rhs->cur);
		}
		
		//������ǰ��/�˺�һλ����Ҫ���ǵ��ǣ����curָ���ڴ���������first֮ǰ����Ҫset_node
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

		
	protected:
		typedef pointer* map_pointer;
		//ָ���ڴ������ָ���ָ��
		map_pointer map;
		//ָ���ڴ������ָ�����Ŀ
		size_type map_size;


	};





}



#endif