#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../game/Game.h"

class Controller {
public:
   Controller(Game*);
   void nextButtonClicked();
   void resetButtonClicked();
private:
   Game *game;
};

#endif
