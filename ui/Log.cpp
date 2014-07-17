#include "Log.h"

Log Logger = Log();

using namespace std;

void Log::setConsole(Gtk::TextView *c)
{
	console = c;
}

void Log::log(const string &msg) const
{
	cout << msg << endl;
	if(console != NULL) {
		Glib::RefPtr<Gtk::TextBuffer> buffer = console->get_buffer();
		buffer->insert(buffer->end(), msg + string("\n"));
	}
}

void Log::log(const char* msg) const
{
	log(string(msg));
}