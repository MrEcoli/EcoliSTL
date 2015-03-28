#ifndef _ECOLISTL_ALLCATOR_H
#define _ECOLISTL_ALLCATOR_H

#include "sub_alloc.h"
#include "construct.h"
#include <cstdlib>
#include <type_traits>
//通过是否定义_USE_PRIMARY_ALLOC确定是否使用次级分配器







namespace EcoliSTL{
	//标准的 STL 接口
	
	//C++11中添加的支持多个参数构造函数的construct

	


	template<typename T>
	class allocator{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef T const* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		static void* allocate(size_type n, const void* ptr = 0){
			return sub_alloc::allocate(n * sizeof(T));
		}
		static void deallocate(pointer ptr){
			sub_alloc::deallocate(ptr, sizeof(T));
		}

		static void deallocate(pointer, size_type){
			sub_alloc::deallocate(ptr, size_type * sizeof(T));
		}

		//construct until C++11 
		template<class... Args>
		static void construct(T* p, Args&&... args){
			::new (static_cast<void*>(p)) T(std::forward<Args>(args)...);
		}

		static void destroy(pointer ptr){
			EcoliSTL::_destroy(ptr);
		}
	};


}


#endif