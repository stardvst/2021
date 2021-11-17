#include <queue>
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>

template <typename T>
class thread_safe_queue
{
public:
	thread_safe_queue() = default;

	thread_safe_queue(const thread_safe_queue &other)
	{
		std::lock_guard<std::mutex> lk(other.m_mutex);
		m_queue = other.m_queue;
	}

	void push(T new_value)
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		m_queue.push(new_value);
		m_condition_var.notify_one();
	}

	void wait_and_pop(T &value)
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		m_condition_var.wait(lk, [this] {return !m_queue.empty(); });
		value = m_queue.front();
		m_queue.pop();
	}

	std::shared_ptr<T> wait_and_pop()
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		m_condition_var.wait(lk, [this] {return !m_queue.empty(); });
		std::shared_ptr<T> res(std::make_shared<T>(m_queue.front()));
		m_queue.pop();
		return res;
	}

	bool try_pop(T &value)
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		if (m_queue.empty())
			return false;

		value = m_queue.front();
		m_queue.pop();
		return true;
	}

	std::shared_ptr<T> try_pop()
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		if (m_queue.empty())
			return std::shared_ptr<T>();

		std::shared_ptr<T> res(std::make_shared<T>(m_queue.front()));
		m_queue.pop();
		return res;
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		return m_queue.empty();
	}

private:
	mutable std::mutex m_mutex;
	std::queue<T> m_queue;
	std::condition_variable m_condition_var;
};

thread_safe_queue<int> queue;

void write()
{
	for (auto idx = 0; idx < 10; ++idx)
		queue.push(idx);
}

void read()
{
	int value{};
	//while (!queue.empty())
	while (queue.try_pop(value))
	{
		//queue.wait_and_pop(value);
		std::cout << value << '\n';
	}
}

int main()
{
	std::thread thread_push(write);
	std::thread thread_pop(read);

	thread_push.join();
	thread_pop.join();
}
