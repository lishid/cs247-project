#ifndef UI_LOG_H
#define UI_LOG_H

#include <string>
#include <iostream>
#include <gtkmm.h>

class Log {
public:
	void log(const std::string &msg) const;
	void log(const char* msg) const;
	void setConsole(Gtk::TextView *c);
private:
	Gtk::TextView *console;
};

extern Log Logger;

#endif