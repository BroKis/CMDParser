#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <filesystem>


namespace thread_pool
{
	/*
	* @brief Класс пула потоков 
	*/
	class ThreadPool 
	{
	public:
		/*
		* @brief Конструктор с параметрами
		* @param[in] numThreads количество входящих потоков
		*/
		ThreadPool(int numThreads);
		/*
		* @brief Десткрутор выключающий потоки
		*/
		~ThreadPool();
		/*
		* Добавление задачи в очередь задач
		* @param[in] task функция выполняющаяся в потоке
		*/
		void enqueue(std::function<void()> task);
		/*
		* @brief Метод сеттер для _msSleep
		* @param[in] msSleep входной параметр
		*/
		void setDebugSleep(std::chrono::microseconds msSleep);
		/*
		* @brief Метод геттер для _msSleep
		*/
		std::chrono::microseconds getDebugSleep();
		/*
		* @brief Метод который останавливает основной поток, пока существуют заявки в пуле
		*/
		void waitFinishTasks();
	private:
		/// Поле для хранения списка потоков
		std::vector<std::thread> threads;
		/// Поле для хранения очереди заявок
		std::queue<std::function<void()>> tasks;
		/// Поле для хранения мьютекса для очереди
		std::mutex queue_mutex;
		/// Поле для хранения состояние
		std::condition_variable condition;
		/// Поле для хранения флага остановки работы пула
		bool stop;
		/// Атомарная переменная для хранения количества задач
		std::atomic<int> taskCount = 0;
		/// Поле для хранения мьютекса для количества задач
		std::mutex taskCountMutex;
		/// Поле для хранения состояния подстчета количества задач
		std::condition_variable taskCountCondition;
		/// Поле для хранения значения debug_sleep
		std::chrono::microseconds _msSleep{};
		/// Метод внутри которого создается поток
		void worker();
	};
}/*namespace thread_pool*/