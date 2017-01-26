# Definitions for Makefile
NAME=			gkrellm

INC_DIR=		-I.	\
			-I./components


DEBUG=			no

MODE=

LOCAL_COMP_FLAGS=	-pipe

LOCAL_LINK_FLAGS=	-pthread -lncurses -lsfml-graphics -lsfml-window -lsfml-system

LOCAL_DEBUG_FLAGS=
