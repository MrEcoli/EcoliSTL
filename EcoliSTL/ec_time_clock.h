
#ifndef _ECSTL_EC_TIME_CLOCK_H
#define _ECSTL_EC_TIME_CLOCK_H
#include <winnt.h>
#include <profileapi.h>
#include <iostream>


//windows system only;

namespace EcSTL{
	class timer{
	private:
		LARGE_INTEGER before_t, after_t;
		LONGLONG freq;
		bool stat;
		//CPU timer at nanoseconds;
		long long cost_ms;
	public:
		timer() :stat(false), cost_ms(0){
			LARGE_INTEGER tmp;
			QueryPerformanceFrequency(&tmp);
			freq = tmp.QuadPart;
		}

		void start(){
			QueryPerformanceCounter(&before_t);
			stat = true;
		}
		void end(){

			if (stat){
				QueryPerformanceCounter(&after_t);
				cost_ms = ((after_t.QuadPart - before_t.QuadPart) * 1000000000) / freq;
			}
			else
				std::cout << "error, no start time" << std::endl;

		}
		void reset(){
			stat = false;
			cost_ms = 0;
		}
		long long get_cost(){
			return cost_ms;
		}
	};


}


#endif // !_ECSTL_EC_TIME_CLOCK_H
