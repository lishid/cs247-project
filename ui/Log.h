#ifndef UI_LOG_H
#define UI_LOG_H

#include <string>
#include <iostream>

class Log {
public:
	void log(const std::string &msg) const;
	void log(const char* msg) const;
private:

};

static Log Logger;

#endif