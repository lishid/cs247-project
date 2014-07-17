#include "Log.h"

using namespace std;

void Log::log(const string &msg) const
{
	cout << msg << endl;
}

void Log::log(const char* msg) const
{
	cout << msg << endl;
}