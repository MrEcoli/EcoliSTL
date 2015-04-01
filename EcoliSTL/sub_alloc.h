#ifndef _ECOLISTL_SUB_ALLOC_H
#define _ECOLISTL_SUB_ALLOC_H

#include <cstdlib>

namespace EcSTL{
	enum {_ALIGN = 8}; //分配内存的最小单位；
	enum { _MAX_BYTES = 128 };	//内存池可分配的最大单位；
	enum { _NUM_FREELIST = _MAX_BYTES / _ALIGN }; //sub_alloc维护的内存池的链表数组大小；
	enum {_OBJ_NUM = 20};

	class sub_alloc{
	private:

		//windows上整数的表示为小端法，client_data[1]表示的是指针的末尾8位
		//内存池链表结构
		//next指向下一个空余位的位置
		//client_data空闲内存的第一个byte的位置

		union obj{
			union obj* next;
			char client_data[1];
		};

		//通过加上(_ALIGN-1),然后通过位运算向上取整
		//_ALGIN必须为2的指数
		static size_t ROUND_UP(size_t n){
			return (n + _ALIGN - 1) & (~(_ALIGN - 1));
		}

		//以static链表维护内存池，一个程序中sub_alloc只维护一个内存池

		static union obj* free_list[_NUM_FREELIST];

		//根据需要配置的内存大小，确定在free_list的哪个位置进行内存分配；
		static size_t free_list_index(size_t n){
			return (n + _ALIGN - 1) / _ALIGN - 1;
		}
		
		static void* refill(size_t n);
		//从堆中获取内存，num_objs表示需要获取的内存数目，以引用传递
		static char *chunk_alloc(size_t size, int &num_objs);

		static char *pool_start;	//内存池起始位置
		static char *pool_end;		//内存池结束位置
		static size_t heap_size;	//??

	public:
		//sub_alloc 开放的接口
		
		//在内存池中分配空间，如果内存池为空，则从堆中重新分配空间给内存池
		static void* allocate(size_t n){
			obj* tmp = 0;

			if (n > _MAX_BYTES){
				tmp = (obj*)malloc(n);
			}
			else{

				//free_list指向成员为指向obj的指针的一个指针；
				//所以select_position需要定义为obj的指针的指针；
				obj** select_position = free_list + free_list_index(n);

				if (*select_position == nullptr){
					void *r = refill(ROUND_UP(n));
					return r;
				}
				else{
					tmp = *select_position;
					*select_position = tmp->next;
				}
			}

			return (void*)tmp;
		}
		
		//回收内存
		static void deallocate(void *p, size_t n){

			if (n > _MAX_BYTES) {
				free(p);
				return;
			}

			//将回收的内存加入相应的链表头部
			obj** recyle_position = free_list + free_list_index(n);

			((obj*)p)->next = *recyle_position;

			*recyle_position = (obj*)p;
		}

		static void reallocate(void *p, size_t old_size, size_t new_size){
			deallocate(p, old_size);
			p = allocate(new_size);
		}
	};




	//初始化内存池

	char* sub_alloc::pool_start = nullptr;
	char* sub_alloc::pool_end = nullptr;

	size_t sub_alloc::heap_size = 0;

	sub_alloc::obj* sub_alloc::free_list[_NUM_FREELIST] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


	//
	void* sub_alloc::refill(size_t n){
		//默认重新分配20个结点；

		int num_objs = _OBJ_NUM;

		//以引用形式传递形参num_objs给函数chunk_alloc
		//如果堆内存不够，可能导致num_objs被改变；
		char *chunk = chunk_alloc(n, num_objs);

		if (num_objs == 1){
			return (void*)chunk;
		}

		obj** refill_positon = free_list + free_list_index(n);

		void *ret = (void *)chunk;
		obj *cur_obj, *nxt_obj;

		*refill_positon = nxt_obj = (obj *)(chunk + n);


		while (--num_objs) {
			cur_obj = nxt_obj;
			nxt_obj = (obj *)((char *)nxt_obj + n);
			if (num_objs == 1){
				cur_obj->next = nullptr;
				break;
			}
			else {
				cur_obj->next = nxt_obj;
			}
		}

		return ret;

	}

	//free_list无可用内存时调用
	char* sub_alloc::chunk_alloc(size_t n, int &num_objs) {
		
		size_t left_bytes = pool_end - pool_start;
		size_t require_bytes = n*num_objs;
		char *ret;

		//内存池满足需求
		if (left_bytes >= require_bytes){
			ret = pool_start;
			pool_start += require_bytes;
			return ret;
		}
		//还有至少能满足一个对象的空间
		else if (left_bytes >= n){
			num_objs = left_bytes / n;
			ret = pool_start;
			pool_start += (num_objs * n);
			return ret;
		}
		//如果剩余空间连一个对象都不能配置
		else {

			
			//将内存池中剩余的空间分配给free_list
			if (left_bytes > 0){
				obj** select_position = free_list + free_list_index(left_bytes);

				((obj*)pool_start)->next = *select_position;

				*select_position = (obj *)pool_start;
			}

			//从堆中配置内除
		
			size_t byte_to_get = 2 * require_bytes + ROUND_UP(heap_size >> 4);

			pool_start = (char*)malloc(byte_to_get);


			//如果heap空间不足，则尝试从尚未使用的内存池区块中配置空间
			if (pool_start == nullptr){

				obj** cur_free_list, *ptr;

				for (size_t i = n; i <= _MAX_BYTES; i += _ALIGN) {
					cur_free_list = free_list + free_list_index(i);
					ptr = *cur_free_list;
					if (ptr != nullptr){
						*cur_free_list = ptr->next;
						pool_start = (char*)ptr;
						pool_end = pool_start + i;

						return chunk_alloc(n, num_objs);
					}
				}

				//分配失败, 退出程序
				exit(1);
			}

			heap_size += byte_to_get;

			pool_end = pool_start + byte_to_get;


			return (chunk_alloc(n, num_objs));
		}
		
	}



}

#endif