
SONAME			= libflecs.a
CC				?= cc
CFLAGS			:= -Wall -std=c99

FLECS_INC:=include
CFLAGS += -I$(FLECS_INC) -I$(FLECS_INC)/flecs/ -I$(FLECS_INC)/flecs/modules -I$(FLECS_INC)/flecs/addons

CFLAGS_RELEASE	:= -O3 -DNDEBUG
CFLAGS_DEBUG	:= -O0 -g -DDEBUG -Wextra
SOURCES			:= $(wildcard src/*.c src/modules/*.c src/modules/pipeline/*.c src/modules/system/*.c src/addons/*.c)
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
	-@rm src/*.o src/modules/pipeline/*.o src/modules/system/*.o src/addons/*.o

cleanlib:
	-@echo CLEAN LIB
	-@rm $(SONAME).*
