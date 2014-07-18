#ifndef UI_LOG_H
#define UI_LOG_H

#include <string>
#include <iostream>
#include <gtkmm.h>

class Log {
public:
	void flush();
	void clear();
	void setConsole(Gtk::TextView *c);
private:
	Gtk::TextView *console;
};

struct Lend {};

extern std::ostringstream lout;
extern std::ostringstream lerr;
extern Lend lend;
extern Log Logger;

std::ostream &operator<<(std::ostream &out, Lend &l);

#endif