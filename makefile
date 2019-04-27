assembler : assembler.o utils.o Instruction.o InstructionSet.o
	g++ \
	assembler.o \
	utils.o \
	Instruction.o \
	InstructionSet.o \
	-o assembler

	find . -name "*.gch" -type f -delete
	find . -name "*.o" -type f -delete

	./assembler

assembler.o : assembler.cpp
	g++ -c assembler.cpp

utils.o : utils.cpp
	g++ -c utils.cpp

Instruction.o : Instruction.cpp
	g++ -c Instruction.cpp

InstructionSet.o : InstructionSet.cpp
	g++ -c InstructionSet.cpp
