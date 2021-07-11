#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

static string toUpper(string s)
{
	string result;
	int (*pToUpper)(int) = &toupper;
	transform(begin(s), end(s), back_inserter(result), pToUpper);
	return result;
}

static vector<string> words(string s)
{
	vector<string> result;
	for (auto c : s)
	{
		if (isspace(c))
			result.push_back("");
		else
			result.back() += c;
	}
	return result;
}

static vector<string> toWords(string s)
{
	return words(s);
}
