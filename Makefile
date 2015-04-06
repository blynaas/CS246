CXX=g++ -g
XXFLAGS=-Wall -MMD
EXEC=cc3k
OBJECTS=cc3k.o item.o floor.o viewcontroller.o character.o cell.o enemy.o player.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${XXFLAGS} ${OBJECTS} -o ${EXEC}
-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC}
