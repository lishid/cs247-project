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

void Log::setAnnounce(Gtk::Label *c)
{
	announce = c;
}

void Log::clear()
{
	if(console != NULL) {
		Glib::RefPtr<Gtk::TextBuffer> buffer = console->get_buffer();
		buffer->erase(buffer->begin(), buffer->end());
	}
	announce->set_markup("<b> </b>");
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
		while(Gtk::Main::instance()->events_pending()) {
			Gtk::Main::instance()->iteration();
		}
		
		// need to trim newline character, otherwise it will mess with formatting
		if(lerr_str.length() > 0) {
			announce->set_markup("<span foreground=\"red\" weight=\"bold\">" + lerr_str.substr(0, lerr_str.length() - 1) + "</span>");
		} else {
			announce->set_markup("<b>" + lout_str.substr(0, lout_str.length() - 1) + "</b>");
		}
		
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
