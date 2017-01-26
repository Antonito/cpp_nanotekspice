# Makefile dependencies directory
MK_DIR=		./mk/

include $(MK_DIR)colors.mk $(MK_DIR)local_defs.mk $(MK_DIR)defs.mk

# Project's files
VPATH=		.:./components

SRC_FILES=	main.cpp	\
		Parser.cpp

COMPONENT_FILES=	AQuadSimple.cpp		\
			QuadXOR.cpp		\
			QuadAND.cpp		\
			QuadNAND.cpp		\
			QuadNOR.cpp		\
			QuadOR.cpp	

SRC=		$(SRC_FILES) $(COMPONENT_FILES)

# Rules
include $(MK_DIR)rules.mk
