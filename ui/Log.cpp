#include "Log.h"

Log Logger = Log();
std::ostringstream lout;
std::ostringstream lerr;
Lend lend;

using namespace std;

void Log::setConsole(Gtk::TextView *c)
{
	console = c;

	if(console != NULL) {
		console->get_buffer()->create_tag("red")->property_foreground_gdk() = Gdk::Color("red");
	}
}

void Log::clear()
{
	if(console != NULL) {
		Glib::RefPtr<Gtk::TextBuffer> buffer = console->get_buffer();
		buffer->erase(buffer->begin(), buffer->end());
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
		Gtk::TextIter end = buffer->end();
		console->scroll_to(end);
	}
	
	lout.str("");
	lout.clear();
	lerr.str("");
	lerr.clear();
}

ostream &operator<<(ostream &out, Lend &l) {
	out << "\n";
	Logger.flush();
	return out;
}
