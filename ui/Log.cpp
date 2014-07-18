#include "Log.h"

Log Logger = Log();
std::ostringstream lout;
std::ostringstream lerr;

using namespace std;

void Log::setConsole(Gtk::TextView *c)
{
	console = c;

	if(c != NULL) {
		c->get_buffer()->create_tag("red")->property_foreground_gdk() = Gdk::Color("red");
	}
}

void Log::flush()
{
	std::string lout_str = lout.str();
	std::string lerr_str = lerr.str();
	cout << lout_str << lerr_str;

	if(console != NULL) {
		Glib::RefPtr<Gtk::TextBuffer> buffer = console->get_buffer();
		buffer->insert(buffer->end(), lout_str);
		buffer->insert_with_tag(buffer->end(), lerr_str, "red");
	}

	lout.clear();
	lerr.clear();
}
