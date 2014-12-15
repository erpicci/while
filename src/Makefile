########################################################################
# While - An abstract interpreter for the While language
# Marco Zanella <marco.zanella.9@studenti.unipd.it>
# Static Analysis and Verification of Software

########################################################################
# Configuration.
CPPC  = g++
COPT  = -Wall -Wextra -pedantic -c
LD    = g++
LDOPT = -Wall -Wextra -pedantic
LEX   = flex
YACC  = bison
DOC   = ../doc


########################################################################
# Dependencies.
all: while
while: domains/BlackHole.o domains/Sign.o domains/Interval.o \
       parser/parser.o scanner/scanner.o AST.o main.o
parser/parser.cpp: parser/grammar.y
scanner/scanner.cpp: scanner/scanner.l
.PHONY: clean doc


########################################################################
# Recipes.
scanner/scanner.cpp:
	@echo "Generating source code for the lexer..."
	@${LEX} -o $@ $<

parser/parser.cpp:
	@echo "Generating source code for the parser..."
	@${YACC} -d -o $@ $<

%.o: %.cpp
	@echo "Compiling $@ module..."
	@${CPPC} ${COPT} -o $@ $<

while:
	@echo "Linkning object modules together..."
	@${LD} ${LDOPT} -o $@ $^
	@echo "Done."

clean:
	@echo "Cleaning up..."
	@rm -f *.o
	@rm -f domains/*.o
	@rm -f scanner/*.o
	@rm -f parser/*.o

doc:
	@echo "Generating documentation" 
	@doxygen ${DOC}/Doxyfile
