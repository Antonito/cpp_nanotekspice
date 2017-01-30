# Makefile dependencies directory
MK_DIR=		./mk/

# Project's folders
FOLDERS=	src			\
		src/components		\
		src/components/gates	\
		src/exceptions

# Lots of definitions
include $(MK_DIR)colors.mk $(MK_DIR)local_defs.mk $(MK_DIR)defs.mk

# Project's files
SRC_FILES=	main.cpp		\
		Parser.cpp		\
		Simulator.cpp

COMPONENT_FILES= Pin.cpp		\
		ComponentFactory.cpp	\
		Input.cpp		\
		Output.cpp		\
		Adder.cpp		\
		FullAdder.cpp		\
		FlipFlop.cpp		\
		DualFlipFlop.cpp

GATES_FILES=	AGate.cpp		\
		ANDGate.cpp		\
		ORGate.cpp		\
		NANDGate.cpp		\
		NORGate.cpp		\
		XORGate.cpp		\
		NOTGate.cpp		\
		NodeGate.cpp

EXCEPTION_FILES= LexicalOrSyntacticError.cpp	\
		InvalidPin.cpp			\
		BadParameter.cpp		\
		UnknownComponent.cpp		\
		InvalidInput.cpp

SRC=		$(SRC_FILES) $(COMPONENT_FILES) $(GATES_FILES)	\
		$(EXCEPTION_FILES)

# Rules
include $(MK_DIR)rules.mk
