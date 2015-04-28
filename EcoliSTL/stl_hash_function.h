#ifndef _ECSTL_HASH_FUNCTION_H
#define _ECSTL_HASH_FUNCTION_H

namespace EcSTL{

	template<class K>
	struct hash{};

	//hash function for string
	inline size_t _hash_string(const char* ch){
		unsigned long ret = 0;
		for (; *ch; ++ch) {
			ret = ret * 5 + *ch;
		}
		return size_t(ret);
	}

	template<>
	struct hash < char * > {
		size_t operator()(const char* s){ return _hash_string(s); }
	};

	//partial sepcilization version of const char*;
	template<>
	struct hash <const char *> {
		size_t operator()(const char* s){ return _hash_string(s); }
	};

	template<> struct hash < char > {
		size_t operator()(char __x) const { return __x; }
	};
	template<> struct hash < unsigned char > {
		size_t operator()(unsigned char __x) const { return __x; }
	};
	template<> struct hash < signed char > {
		size_t operator()(unsigned char __x) const { return __x; }
	};
	template<> struct hash < short > {
		size_t operator()(short __x) const { return __x; }
	};
	template<> struct hash < unsigned short > {
		size_t operator()(unsigned short __x) const { return __x; }
	};
	template<> struct hash < int > {
		size_t operator()(int __x) const { return __x; }
	};
	template<> struct hash < unsigned int > {
		size_t operator()(unsigned int __x) const { return __x; }
	};
	template<> struct hash < long > {
		size_t operator()(long __x) const { return __x; }
	};
	template<> struct hash < unsigned long > {
		size_t operator()(unsigned long __x) const { return __x; }
	};


	//hash function for double and float
	template<> struct hash < double > {
		size_t operator()( double __x) const { 
			union combination{
				long long v1;
				double v2;
			};
			combination cc;
			cc.v2 = __x;

			return (size_t)cc.v1; 
		}
	};

	template<> struct hash < float > {
		size_t operator()(float __x) const {
			union combination{
				unsigned v1;
				float v2;
			};
			combination cc;
			cc.v2 = __x;
			return (size_t)cc.v1;
		}
	};

}

#endif