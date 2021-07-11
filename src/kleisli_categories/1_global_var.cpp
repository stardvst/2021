#include <string>

using namespace std;

string logger;
static bool negateGlobal(bool b)
{
	logger += "Not so! ";
	return !b;
}

// produce a log
static pair<bool, string> negate(bool b, string logger)
{
	return make_pair(!b, logger + "Not so! ");
}

// produce a string
static pair<bool, string> negate(bool b)
{
	return make_pair(!b, "Not so! ");
}
