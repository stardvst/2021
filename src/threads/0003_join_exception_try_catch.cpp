#include <iostream>
#include <thread>

void do_something(int j)
{
	std::cout << j << '\n';
}

struct func
{
	int &m_i;
	func(int &i) : m_i(i) {}

	void operator()()
	{
		for (unsigned j = 0; j < 10; ++j)
			do_something(m_i);
	}
};

void oops()
{
	int local_state = 0;
	func my_func{ local_state };

	std::thread my_thread(my_func);
	try
	{
		std::cout << "Trying...\n";
	}
	catch (...)
	{
		my_thread.join();
		throw;
	}
	my_thread.join();
}

int main()
{
	oops();
}
