assembler : assembler.o utils.o
	g++ \
	assembler.o \
	utils.o \
	-o assembler

	find . -name "*.gch" -type f -delete
	find . -name "*.o" -type f -delete

	./assembler

assembler.o : assembler.cpp
	g++ -c assembler.cpp

utils.o : utils.cpp
	g++ -c utils.cpp
