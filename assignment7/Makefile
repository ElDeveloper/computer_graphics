#
# author: Yoshiki Vazquez Baeza
# e-mail: yoshiki89@gmail.com
# credits: git's Makefile and a Makefile from 'CSCI5229 Fall 2013'
#

EX=hw7

# get the system name
uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')

CC=gcc

#  OSX
ifeq ($(uname_S),Darwin)
	CFLAGS +=  -Wunused-function -Wno-deprecated-declarations 
	LIBS=-framework GLUT -framework OpenGL -lm
	CC = clang # error/warnings are more verbose
endif
#  MinGW
ifeq ($(uname_S),Windows)
	LIBS=-lglut32cu -lglu32 -lopengl32
endif
#  Unix/Linux
ifeq ($(uname_S),Linux)
	LIBS=-lglut -lGLU -lGL -lm
endif

#  Main target
all: $(EX)

#  Generic compile rules
.c.o:
	$(CC) -c -O -Wall $(CFLAGS) $<

#  Generic compile and link
%: %.c CSCIx229.a
	$(CC) -Wall -O3 -o $@ $^ $(LIBS) $(CFLAGS)

#  Delete unwanted files
clean:
	rm -f $(EX) *.o *.gch *.zip *.a

#  Create archive
CSCIx229.a:fatal.o loadtexbmp.o print.o project.o errcheck.o object.o yvbutils.o
	ar -rcs CSCIx229.a $^

submit: clean
	zip hw7.zip hw7.c *.c *.h Makefile README.md

#  Obligatory UNIX inside joke
love:
	@echo "not war?"

