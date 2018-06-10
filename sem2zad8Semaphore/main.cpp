#include <iostream>
#include <thread>
#include <chrono>  
#include "semaphore.h"

void f(Semaphore &s)
{
	s.enter();
	std::cout << "Do smth" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Done" << std::endl;
	s.leave();

}

int main()
{
	Semaphore s(1);
	std::thread thread1(f, std::ref(s));
	std::thread thread2(f, std::ref(s));
	thread1.join();
	thread2.join();
	return 0;
}