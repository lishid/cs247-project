# variables and initialization
CXX=g++
# builds dependency lists in .d ﬁles
CXXFLAGS = -g -Wall -MMD `pkg-config gtkmm-2.4 --cflags --libs` 
OBJECTS = ./Main.o game/Card.o game/Command.o game/Deck.o game/Game.o game/Player.o game/Table.o
# substitute ".o" with ".d"
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} ${CXXFLAGS}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d and reruns dependencies
