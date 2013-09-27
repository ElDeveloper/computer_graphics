# author: Yoshiki Vazquez Baeza
# e-mail: yoshiki89@gmail.com
# credits: git's Makefile and a Makefile from 'CSCI5229 Fall 2013'

EX=main
all: $(EX)

# get the system name
uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')

CC=gcc

#  OSX
ifeq ($(uname_S),Darwin)
	CFLAGS += -framework GLUT -framework OpenGL
	CC = clang # error/warnings are more verbose
endif
#  MinGW
ifeq ($(uname_S),Windows)
	CFLAGS += -lglut32cu -lglu32 -lopengl32
endif
#  Unix/Linux
ifeq ($(uname_S),Linux)
	CFLAGS += -lglut -lGLU
endif

csci5229.o:
	$(CC) -Wall -O3 -c csci5229.c

# change the name of the output to hwXXX
$(EX):csci5229.o
	$(CC) -Wall -O3 -lm -o hw3 main.c $< $(CFLAGS)

clean:
	rm -f $(EX) *.o *.gch *.zip

submit: clean
	zip hw3.zip main.c csci5229.c csci5229.h Makefile README.md