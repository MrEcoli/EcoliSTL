#ifndef _ECOLI_TYPE_TRAIT_H
#define _ECOLI_TYPE_TRAIT_H
//利用偏特化 Partial specialization 进行类型信息萃取


namespace EcSTL{

	struct _true_type{};
	struct _false_type{};


	template<class T>
	struct _type_trait{
		typedef _false_type	has_trivial_default_constructor;
		typedef _false_type	has_trivial_default_copy_constructor;
		typedef _false_type	has_trivial_default_assignment_operator;
		typedef _false_type	has_trivial_default_destructor;

		//is_POD_type指Plain Old Data, 标量类型或传统的C struct型别，它们的构造函数，析构函数，拷贝函数，拷贝赋值函数等都是不重要，trivial的
		typedef _false_type	is_POD_type;

	};

	template<>
	struct _type_trait<char>{
		typedef _true_type	has_trivial_default_constructor;
		typedef _true_type	has_trivial_default_copy_constructor;
		typedef _true_type	has_trivial_default_assignment_operator;
		typedef _true_type	has_trivial_default_destructor;
		typedef _true_type	is_POD_type;
	};

	template<>
	struct _type_trait<signed char>{
		typedef _true_type	has_trivial_default_constructor;
		typedef _true_type	has_trivial_default_copy_constructor;
		typedef _true_type	has_trivial_default_assignment_operator;
		typedef _true_type	has_trivial_default_destructor;
		typedef _true_type	is_POD_type;
	};


	template<>
	struct _type_trait<unsigned char>{
		typedef _true_type	has_trivial_default_constructor;
		typedef _true_type	has_trivial_default_copy_constructor;
		typedef _true_type	has_trivial_default_assignment_operator;
		typedef _true_type	has_trivial_default_destructor;
		typedef _true_type	is_POD_type;
	};


	template<>
	struct _type_trait<short>{
		typedef _true_type	has_trivial_default_constructor;
		typedef _true_type	has_trivial_default_copy_constructor;
		typedef _true_type	has_trivial_default_assignment_operator;
		typedef _true_type	has_trivial_default_destructor;
		typedef _true_type	is_POD_type;
	};


	template<>
	struct _type_trait<unsigned short>{
		typedef _true_type	has_trivial_default_constructor;
		typedef _true_type	has_trivial_default_copy_constructor;
		typedef _true_type	has_trivial_default_assignment_operator;
		typedef _true_type	has_trivial_default_destructor;
		typedef _true_type	is_POD_type;
	};


	template<>
	struct _type_trait<int>{
		typedef _true_type	has_trivial_default_constructor;
		typedef _true_type	has_trivial_default_copy_constructor;
		typedef _true_type	has_trivial_default_assignment_operator;
		typedef _true_type	has_trivial_default_destructor;
		typedef _true_type	is_POD_type;
	};


	template<>
	struct _type_trait<unsigned int>{
		typedef _true_type	has_trivial_default_constructor;
		typedef _true_type	has_trivial_default_copy_constructor;
		typedef _true_type	has_trivial_default_assignment_operator;
		typedef _true_type	has_trivial_default_destructor;
		typedef _true_type	is_POD_type;
	};


	template<>
	struct _type_trait<long>{
		typedef _true_type	has_trivial_default_constructor;
		typedef _true_type	has_trivial_default_copy_constructor;
		typedef _true_type	has_trivial_default_assignment_operator;
		typedef _true_type	has_trivial_default_destructor;
		typedef _true_type	is_POD_type;
	};


	template<>
	struct _type_trait<unsigned long>{
		typedef _true_type	has_trivial_default_constructor;
		typedef _true_type	has_trivial_default_copy_constructor;
		typedef _true_type	has_trivial_default_assignment_operator;
		typedef _true_type	has_trivial_default_destructor;
		typedef _true_type	is_POD_type;
	};


	template<>
	struct _type_trait<float>{
		typedef _true_type	has_trivial_default_constructor;
		typedef _true_type	has_trivial_default_copy_constructor;
		typedef _true_type	has_trivial_default_assignment_operator;
		typedef _true_type	has_trivial_default_destructor;
		typedef _true_type	is_POD_type;
	};



	template<>
	struct _type_trait<double>{
		typedef _true_type	has_trivial_default_constructor;
		typedef _true_type	has_trivial_default_copy_constructor;
		typedef _true_type	has_trivial_default_assignment_operator;
		typedef _true_type	has_trivial_default_destructor;
		typedef _true_type	is_POD_type;
	};


	template<>
	struct _type_trait<long double>{
		typedef _true_type	has_trivial_default_constructor;
		typedef _true_type	has_trivial_default_copy_constructor;
		typedef _true_type	has_trivial_default_assignment_operator;
		typedef _true_type	has_trivial_default_destructor;
		typedef _true_type	is_POD_type;
	};


	template<typename T>
	struct _type_trait<T*>{
		typedef _true_type	has_trivial_default_constructor;
		typedef _true_type	has_trivial_default_copy_constructor;
		typedef _true_type	has_trivial_default_assignment_operator;
		typedef _true_type	has_trivial_default_destructor;
		typedef _true_type	is_POD_type;
	};


}


#endif // !_ECOLI_TYPE_TRAIT_H
