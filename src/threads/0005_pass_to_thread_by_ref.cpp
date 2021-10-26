#include <iostream>
#include <thread>

void increment(int &i)
{
	++i;
}

int main()
{
	int a = 0;

	std::thread t(increment, std::ref(a));
	t.join();

	std::cout << a;
}
