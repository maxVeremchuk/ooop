#pragma once

#include <mutex>
#include <condition_variable>
#include <vector>

class Semaphore
{
private:
	int counter;
	std::mutex mutex;
	std::condition_variable cv;
public:
	Semaphore(int);
	void enter();
	void leave();

};