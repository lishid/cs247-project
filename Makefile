# variables and initialization
CXX=g++
# builds dependency lists in .d ﬁles
CXXFLAGS = -g -Wall -MMD 
OBJECTS = Card.o Command.o Deck.o Game.o Player.o Table.o
# substitute ".o" with ".d"
DEPENDS = ${OBJECTS:.o=.d} 
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d ﬁles and reruns dependencies