#ifndef UI_LOG_H
#define UI_LOG_H

#include <string>
#include <iostream>
#include <gtkmm.h>

class Log {
public:
	void flush();
	void setConsole(Gtk::TextView *c);
private:
	Gtk::TextView *console;
};

extern std::ostringstream lout;
extern std::ostringstream lerr;
extern Log Logger;

#endif