#include "semaphore.h"

Semaphore::Semaphore(int count) 
{
	if (count < 0)
	{
		throw "Less than 0";
	}
	counter = count;
}


void Semaphore::enter()
{
	std::unique_lock<std::mutex> lock(mutex);
	cv.wait(lock, [this]() {return counter > 0; });
	counter--;
	cv.notify_one();
}

void  Semaphore::leave()
{
	std::unique_lock<std::mutex> lock(mutex);
	counter++;
	cv.notify_one();
}