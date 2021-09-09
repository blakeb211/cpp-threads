#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <string>
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

struct GameState {
	std::vector<int> vertices{};
};

void Test3()
{
	using namespace std::chrono_literals;
	std::atomic<int> progress{0};
	GameState level{};

	auto load = [&progress, &level]() {
		level.vertices.resize(40'000);
		level.vertices.resize(0);
		while (progress < 1000)
		{
			level.vertices.push_back(progress);
			progress += 1;
			std::this_thread::sleep_for(1ms);
		}
	};

	const std::string prog_txt{"."};
	std::cout << "Loading level\n";
	std::thread t1{load};
	t1.detach();

	for (;;)
	{
		// GetUserInput();
		std::this_thread::sleep_for(16ms);
		if (progress % 2 == 0)
			std::cout << prog_txt;
		if (progress == 1000)
		{
			break;
		}
	}
	std::cout << std::endl;
	std::cout << "Level loaded with " << level.vertices.size() << " vertices." << std::endl;
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
