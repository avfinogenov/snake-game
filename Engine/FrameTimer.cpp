#include "FrameTimer.h"


using namespace std::chrono;
FrameTimer::FrameTimer()
{
	last = steady_clock::now();

}

double FrameTimer::Mark()
{
	auto old=last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	
	
	return frameTime.count();
}
