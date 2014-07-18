# variables and initialization
CXX=g++
# builds dependency lists in .d ﬁles
CXXFLAGS = -g -Wall -MMD `pkg-config gtkmm-2.4 --cflags --libs`
CPPFILES = $(wildcard abstract/*.h) $(wildcard game/*.h) $(wildcard ui/*.h) $(wildcard *.h)
OBJECTS = ${CPPFILES:.h=.o}
# substitute ".o" with ".d"
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} ${CXXFLAGS}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d and reruns dependencies
