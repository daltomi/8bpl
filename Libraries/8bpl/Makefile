
SONAME			= lib8bpl.a
VER				= "0.4"
DIR_INCLUDE		:= include
DIR_SRC			:= src
CC				?= cc
CFLAGS			:= -Wall -std=c99 -I$(DIR_INCLUDE) 	\
					-I../Tilengine/include 			\
					-I/usr/include/SDL2 			\
					-I../stb/include				\
					-I../cute_headers/include		\
					-msse3 #cute_sound

CFLAGS_RELEASE	:= -O3 -DNDEBUG
CFLAGS_DEBUG	:= -O0 -g -DDEBUG -Wextra
SOURCES			:= $(wildcard $(DIR_SRC)/*.c)
OBJS			:= $(SOURCES:.c=.o)

config:
	-@sed -e 's/@8BPL_SONAME@/\"$(SONAME)\"/g' -e 's/@8BPL_VER@/$(VER)/g' include/config.h.in > include/config.h

release: SONAME:=$(SONAME).release
release: CFLAGS+=$(CFLAGS_RELEASE)
release: config $(SONAME)
release: clean

debug: SONAME:=$(SONAME).debug
debug: CFLAGS+=$(CFLAGS_DEBUG)
debug: config $(SONAME)
debug: clean

$(SONAME): $(OBJS)
	ar rcs $(SONAME) $(OBJS)

clean:
	-@echo CLEAN
	-@rm $(DIR_SRC)/*.o $(DIR_INCLUDE)/config.h

cleanlib:
	-@echo CLEAN LIB
	-@rm $(SONAME).*
