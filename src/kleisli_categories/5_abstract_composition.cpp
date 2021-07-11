#include <functional>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

template <typename A>
using Writer = pair<A, string>;

Writer<string> toUpper(string s)
{
	string result;
	int (*pToUpper)(int) = &toupper;
	transform(begin(s), end(s), back_inserter(result), pToUpper);
	return make_pair(result, "toUpper ");
}

vector<string> words(string s)
{
	vector<string> result;
	for (auto c : s)
	{
		if (isspace(c))
			result.push_back("");
		else
		{
			if (result.empty())
				result.emplace_back();
			result.back() += c;
		}
	}
	return result;
}

Writer<vector<string>> toWords(string s)
{
	return make_pair(words(s), "toWords ");
}

template <typename A, typename B, typename C>
function<Writer<C>(A)> compose(function<Writer<B>(A)> m1, function<Writer<C>(B)> m2)
{
	return [m1, m2](A x)
	{
		auto p1 = m1(x);
		auto p2 = m2(p1.first);
		return make_pair(p2.first, p1.second + p2.second);
	};
}

Writer<vector<string>> process(string s)
{
	return compose<string, string, vector<string>>(toUpper, toWords)(s);
}

//////////////////////////////////////////////////////////////////////////

const auto compose_cpp14 = [](auto m1, auto m2)
{
	return [m1, m2](auto x)
	{
		auto p1 = m1(x);
		auto p2 = m2(p1.first);
		return make_pair(p2.first, p1.second + p2.second);
	};
};

Writer<vector<string>> process_cpp14(string s)
{
	return compose_cpp14(toUpper, toWords)(s);
}

int main()
{
	auto result = process("This is hello world");
	cout << result.first.size() << ": " << result.second << '\n';

	result = process_cpp14("This is hello world");
	cout << result.first.size() << ": " << result.second;
}
