########################################################################
# While - An abstract interpreter for the While language
# Marco Zanella <marco.zanella.9@studenti.unipd.it>
# Static Analysis and Verification of Software

########################################################################
# Configuration.
PROJ    = while
SRC     = src
BIN     = bin
MAKEOPT = --no-print-directory


########################################################################
# Dependencies.
all: ${SRC}/${PROJ}
.PHONY: clean doc


########################################################################
# Recipes.
${SRC}/${PROJ}:
	@make ${MAKEOPT} -C ${SRC}

install:
	@echo "Installing under ${BIN}..."
	@mv ${SRC}/${PROJ} ${BIN}

doc:
	@make doc ${MAKEOPT} -C ${SRC}

clean:
	@make clean ${MAKEOPT} -C ${SRC}

uninstall:
	@echo "Uninstalling..."
	@rm -f ${BIN}/${PROJ}
