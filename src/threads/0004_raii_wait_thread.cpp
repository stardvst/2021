#include <iostream>
#include <thread>

class thread_guard
{
public:
	explicit thread_guard(std::thread &thread) : m_thread(thread) {}

	thread_guard(const std::thread &) = delete;
	thread_guard &operator=(const std::thread &) = delete;

	~thread_guard()
	{
		if (m_thread.joinable())
			m_thread.join();
	}

private:
	std::thread &m_thread;
};

struct func
{
	int &m_i;
	func(int &i) : m_i(i) {}

	void operator()()
	{
		for (unsigned j = 0; j < 10; ++j)
			std::cout << j << '\n';
	}
};

void throwing()
{
	throw 42;
}

void my_function()
{
	int local_state = 0;
	func my_func{ local_state };

	std::thread my_thread(my_func);
	thread_guard guard(my_thread);

	try
	{
		throwing();
	}
	catch (int i)
	{
		std::cout << i << '\n';
	}
}

int main()
{
	my_function();
}
