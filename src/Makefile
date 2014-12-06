########################################################################
## While Language Abstract Interpretation - Makefile
########################################################################

########################################################################
## Configuration section.
CC   = gcc
CPPC = g++
LD   = g++
LEX  = flex
YACC = bison
OPT  = -O3
OPTSTRICT = $(OPT) -Wall -Wextra -pedantic


########################################################################
## Dependecnies.
all: while

while: scanner.o parser.o wrapper.o main.o

main.o:    main.cpp
scanner.o: scanner.l parser.o
parser.o:  parser.y
wrapper.o: wrapper.cpp


.PHONY: clean document backup



########################################################################
## Receipes.
while:
	@echo "Generating while interpreter..."
	@$(LD) $(OPTSTRICT) -o while scanner.o parser.o wrapper.o main.o
	@echo "Done."
	
scanner.o:
	@echo "Generating lexical analyzer from (f)lex file..."
	@$(LEX) -o scanner.c scanner.l
	@$(CPPC) $(OPTSTRICT) -c -o scanner.o scanner.c
	@rm -f scanner.c

parser.o:
	@echo "Generating syntactic analyzer from grammar file..."
	@$(YACC) -d -o parser.cc parser.y
	@$(CPPC) $(OPTSTRICT) -c -o parser.o parser.cc
	@rm -f parser.cc

wrapper.o:
	@$(CPPC) $(OPTSTRICT) -c -o wrapper.o wrapper.cpp

main.o:
	@echo "Generating main core..."
	@$(CPPC) $(OPTSTRICT) -c -o main.o main.cpp



clean:
	@echo "Cleanup..."
	@rm -f *.o *.dot *.png parser.hh


document:
	@echo "Generating documentation..."
	@doxygen ../doc/Doxyfile


backup:
	@echo "Creating a backup file."
	@rm -f ../source_backup.zip
	@zip -r ../source_backup.zip ./*

