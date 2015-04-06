
#ifndef _ECSTL_EC_TIME_CLOCK_H
#define _ECSTL_EC_TIME_CLOCK_H
#include <windows.h>



//windows system only;

namespace EcSTL{
	class timer{

	protected:
		
		__int64 start;
		__int64 end;

	public:
		static double PCFreq;
		static bool isPCFreq_detected;
		timer(){
			if (!isPCFreq_detected){
				LARGE_INTEGER li;
				QueryPerformanceFrequency(&li);
				PCFreq = double(li.QuadPart) / 1000.0;
				isPCFreq_detected = true;
			}

			start = 0;
			end = 0;
		}

		void startCounter(){
			LARGE_INTEGER li;
			QueryPerformanceCounter(&li);
			start = li.QuadPart;
		}

		void endCounter(){
			LARGE_INTEGER li;
			QueryPerformanceCounter(&li);
			end = li.QuadPart;
		}

		double getCounter(){
			return (double)(end -start) / PCFreq;
		}

	};

	bool timer::isPCFreq_detected = false;
	double timer::PCFreq = 0.0;


}


#endif // !_ECSTL_EC_TIME_CLOCK_H
