
SONAME			= libflecs.a
DIR_INCLUDE		:= include
DIR_SRC			:= src
CC				?= cc
CFLAGS			:= -Wall -std=c99 -I$(DIR_INCLUDE)

CFLAGS_RELEASE	:= -O3 -DNDEBUG
CFLAGS_DEBUG	:= -O0 -g -DDEBUG -Wextra
SOURCES			:= $(wildcard $(DIR_SRC)/*.c)
OBJS			:= $(SOURCES:.c=.o)

config:


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
	-@rm $(DIR_SRC)/*.o

cleanlib:
	-@echo CLEAN LIB
	-@rm $(SONAME).*
