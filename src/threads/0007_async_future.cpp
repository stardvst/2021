#include <future>
#include <iostream>

int double_it(int n)
{
	return n << 1;
}

void do_other_stuff()
{
	std::cout << "doing other stuff\n";
}

int main()
{
	std::future<int> answer = std::async(double_it, 3);
	do_other_stuff();
	std::cout << "The answer is " << answer.get() << '\n';
	return 0;
}
