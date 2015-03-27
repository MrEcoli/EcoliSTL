#ifndef _ECOLISTL_PRIMARY_ALLOC_H
#define _ECOLISTL_PRIMARY_ALLOC_H

#include <new>
#include <iostream>
#include <cstdlib>
namespace EcoliSTL{
	//SGI STL里，第一级配置器是一个带有非型别参数int的模板类，但这个形参在过程中并未使用
	//与SGI_STL不同，EcoliSTL的第一级配置器，使用operator new 配置空间，而非SGI STL中的malloc
	void no_memory(){
		std::cout << "No enough memory!\n" << std::endl;
		std::exit(1);
	}


	class primary_alloc{
	public:
		static void *allocate(size_t n){
			//设置 new 失败的操作 no_memory
			std::set_new_handler(no_memory);
			void* ptr = (::operator new(n));
			//当new失败后，将调用no_memory函数
			return ptr;
		}

	};
}

#endif