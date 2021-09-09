#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

// Tasks
// Threads
// 	can accesss different memory locations concurrently with no issues
// Thread-local data
// Condition Variables
// Atomics

// C++11
// 	standard memory model
// 	standard threading interface
// 	Threads
// 		thread.join(), thread.detach()
// 	Mutex Locks
// 		std::lock_guard, std::unique_lock, std:: shared_lock
// 	Tasks
// 		std::async, std::promise, std::future
// C++14
// 	reader-writer locsk added to threading interface
/****************************************************
 * FWD DECLARES
 * **************************************************/
void Test1();
void Test2();
void Test3();
/***************************************************/

int main()
{
	Test3();
	return 0;
}

void Test3()
{
	using namespace std::chrono_literals;
	std::atomic<int> progress{0};

	auto load = [&]() {
		while (progress < 1000)
		{
			progress += 10;
			std::this_thread::sleep_for(3ms);
		}
	};

	std::thread t1{load};
	for (;;)
	{
		if (progress % 50 == 0)
		{
			std::cout << "progress: " << progress << std::endl;
		}
		std::this_thread::sleep_for(50us);
		if (progress == 1000)
		{
			t1.join();
			break;
		}
	}
}

void Test1()
{
	int cnt = 0;
	auto f = [&] { cnt++; };
	std::thread t1{f}, t2{f}, t3{f};
	t1.join();
	t2.join();
	t3.join();
	std::cout << "cnt: " << cnt << std::endl;
}

void Test2()
{
	std::atomic<int> cnt{0};
	auto f = [&] { cnt++; };
	std::thread t1{f}, t2{f}, t3{f};
	t1.join();
	t2.join();
	t3.join();
	std::cout << "cnt: " << cnt << std::endl;
}

//
//			using namespace std::chrono_literals;
//			std::this_thread::sleep_for(20ms);
