
#include "thread_pool.hpp"
#include <iostream>

namespace thread_pool
{
	ThreadPool::ThreadPool(int numThreads) : stop(false)
	{
		for (auto i{ 0 }; i < numThreads; i++) {
			threads.emplace_back(&ThreadPool::worker, this);
		}
	}

	void ThreadPool::worker()
	{
		try
		{
			while (true) {
				std::function<void()> task;
				{
					std::unique_lock<std::mutex> lock(queue_mutex);
					condition.wait(lock, [this] { return stop || !tasks.empty(); });
					if (stop && tasks.empty()) {
						return;
					}
					task = std::move(tasks.front());
					tasks.pop();
				}
				task();
				--taskCount;
				 taskCountCondition.notify_one();
			}
		}
		catch (std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			for (std::thread& thread : threads)
			{
				if (thread.joinable()) { thread.join(); }
			}
		}

	}
	ThreadPool::~ThreadPool()
	{
		{
			std::unique_lock<std::mutex> lock(queue_mutex);
			stop = true;
		}
		condition.notify_all();
		for (std::thread& thread : threads)
		{
			if (thread.joinable()) { thread.join(); }
		}
	}
	void ThreadPool::enqueue(std::function<void()> task)
	{
		{
			std::unique_lock<std::mutex> lock(queue_mutex);
			if (stop) {
				throw std::runtime_error("enqueue on stopped ThreadPool");
			}
			++taskCount;
			tasks.emplace(task);
		}
		condition.notify_one();

	}

	void ThreadPool::waitFinishTasks()
	{
		std::unique_lock<std::mutex> lock(taskCountMutex);
		taskCountCondition.wait(lock, [this] {return taskCount == 0; });
	}

	std::chrono::microseconds ThreadPool::getDebugSleep()
	{
		return _msSleep;
	}

	void ThreadPool::setDebugSleep(std::chrono::microseconds msSleep)
	{
		_msSleep = msSleep;
	}


}