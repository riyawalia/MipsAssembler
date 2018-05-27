CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -Werror -MMD
EXEC = asm
OBJECTS = assembler.o scanner.o symbolTable.o syntaxChecker.o translator.o asm.o

DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS}  -o ${EXEC}

-include ${DEPENDS} #read the content and insert it in the variable (-include)

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
