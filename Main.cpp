#include "Main.h"

int main( int argc, char * argv[] )
{
	Gtk::Main kit( argc, argv );
	Game game;
	Controller controller(&game);
	Window window(&controller, &game);
	Gtk::Main::run(window);
	return 0;
}

