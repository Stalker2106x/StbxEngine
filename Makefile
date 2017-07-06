CC = g++

RM = rm -f

TEST = $(BINDIR)/test

INCDIR = ./include

EXTLIB = ./extlib

TESTDIR = ./test

SRCDIR = ./src

BINDIR = ./bin

CXXFLAGS = -fPIC -W -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Os -O0 -g -I$(INCDIR) -I$(EXTLIB) -I$(EXTLIB)/sfml/include/

LIBS = -L$(EXTLIB) -L$(EXTLIB)/sfml/lib/

LIBFLAGS = -shared

ifeq ($(OS),Windows_NT)
	CXXFLAGS += -IW:/Software/mingw32/include -IC:/mingw64/include
	LIBFLAGS += -lsfml-system -lsfml-window -lsfml-graphics
	NAME = $(BINDIR)/libsengine.dll
else
	UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
	LIBFLAGS += -lsfml-system -lsfml-window -lsfml-graphics
	NAME = $(BINDIR)/libsengine.so
  endif
  ifeq ($(UNAME_S),Darwin)
	CXXFLAGS += -I/usr/local/include
	LIBFLAGS += -F/Library/Frameworks -framework freetype -framework sfml-window -framework sfml-graphics -framework sfml-system
	NAME = $(BINDIR)/libsengine.Framework
  endif
endif

TESTSRCS =			$(TESTDIR)/test.cpp			\
				$(TESTDIR)/cengine.cpp

TESTOBJS = $(TESTSRCS:.cpp=.o)

SRCS =				$(EXTLIB)/pugixml/src/pugixml.cpp	\
				$(SRCDIR)/Engine.cpp			\
				$(SRCDIR)/Console.cpp			\
				$(SRCDIR)/Commands.cpp			\
				$(SRCDIR)/Keybinds.cpp			\
				$(SRCDIR)/Control.cpp			\
				$(SRCDIR)/Menu.cpp			\
				$(SRCDIR)/MenuItem.cpp

OBJS = $(SRCS:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBS) $(LIBFLAGS)

test: $(TESTOBJS)
	$(CC) -o $(TEST) $(TESTOBJS) -L$(BINDIR) -lsengine

clean:
	$(RM) $(OBJS) $(TESTOBJS)

fclean: clean
	$(RM) $(NAME) $(TEST)

re: fclean all

.PHONY: all clean fclean re
