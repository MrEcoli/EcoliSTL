#ifndef _ECOLISTL_ALLCATOR_H
#define _ECOLISTL_ALLCATOR_H

#include "minor_alloc.h"
#include "primary_alloc.h"

//通过是否定义_USE_PRIMARY_ALLOC确定是否使用次级分配器



#endif */// !_USE_MINOR_ALLOC



namespace EcoliSTL{
	#ifdef _USE_PRIMARY_ALLOC
		typedef primary_alloc alloc;
	#else
	#define  _NODE_ALLOCATOR_THREADS 0 //_NODE_ALLOCATOR_THREADS 多线程在ECOLISTL中暂不考虑
		typedef minor_alloc<_NODE_ALLOCATOR_THREADS, 0> alloc;
	#endif



	//simple_alloc是最后各类容器所使用的allocator

	template<typename T, typename Alloc>
	simple_alloc{
	static T *allocate(size_t n){
		return 0 == n ? (T*)Alloc::allocate(n * sizeof(T));
	} //可以通过设定默认形参 n = 1 来替代形参为空的allocate函数吗？

	static T *allocate(void) {
		return (T*)Alloc::allocate(sizeof (T));
	}

	static void deallocate(T* ptr, size_t n){
		if (n != 0){
			Alloc::deallocate(p, n * sizeof(T));
		}
	}

	static void deallocate(T* ptr){
		Alloc::deallocate(p);
	}
};


}


#endif