
SONAME			= libTilengine.a
DIR_INCLUDE		:= include
DIR_SRC			:= src
CC				?= cc
CFLAGS			:= -Wall -std=c99 -I$(DIR_INCLUDE) -I/usr/include/SDL2
CFLAGS_RELEASE	:= -O3 -DNDEBUG
CFLAGS_DEBUG	:= 	-O0 -g -DDEBUG -Wextra -Wno-unused-parameter -Wno-typedef-redefinition -Wno-unused-function
SOURCES			:= $(wildcard $(DIR_SRC)/*.c)
OBJS			:= $(SOURCES:.c=.o)


release: SONAME:=$(SONAME).release
release: CFLAGS+=$(CFLAGS_RELEASE)
release: $(SONAME)
release: clean

debug: SONAME:=$(SONAME).debug
debug: CFLAGS+=$(CFLAGS_DEBUG)
debug: $(SONAME)
debug: clean

$(SONAME): $(OBJS)
	ar rcs $(SONAME) $(OBJS)

clean:
	-@echo CLEAN
	-@rm $(DIR_SRC)/*.o

cleanlib:
	-@echo CLEAN LIB
	-@rm $(SONAME).*
