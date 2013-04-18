CXX = g++					        # compiler
CXXFLAGS = -g -Wall -MMD			# compiler flags
OBJECTS = hearts.o trick.o Player.o SmartPlayer.o RandomPlayer.o HumanPlayer.o Options.o CardPile.o Deck.o Card.o
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXEC = Hearts

PHONY : all clean

all : ${EXEC}

${EXEC} : ${OBJECTS}				# link step
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -rf ${DEPENDS} ${OBJECTS}
