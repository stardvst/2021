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

Writer<vector<string>> process(string s)
{
	auto p1 = toUpper(s);
	auto p2 = toWords(p1.first);
	return make_pair(p2.first, p1.second + p2.second);
}

int main()
{
	auto result = process("This is hello world");
	cout << result.first.size() << ": " << result.second;
}
