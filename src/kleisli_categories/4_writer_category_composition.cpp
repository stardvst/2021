#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

pair<bool, string> negate(bool b)
{
	return make_pair(!b, "Not so! ");
}

pair<bool, string> isEven(int n)
{
	return make_pair(n % 2 == 0, "isEven ");
}

// composition
pair<bool, string> isOdd(int n)
{
	pair<bool, string> p1 = isEven(n);
	pair<bool, string> p2 = negate(p1.first);
	return make_pair(p2.first, p1.second + p2.second);
}
