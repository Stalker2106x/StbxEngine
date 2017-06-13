CC = g++

RM = rm -f

TEST = $(BINDIR)/test

INCDIR = include

EXTLIB = extlib

TESTDIR = test

SRCDIR = src

BINDIR = bin

CXXFLAGS = -fPIC -W -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Os -O0 -g -I$(INCDIR) -I$(EXTLIB)

LIBS = -L$(EXTLIB)

LIBFLAGS = -shared

ifeq ($(OS),Windows_NT)
	CXXFLAGS += -IW:/Software/mingw32/include -IC:/mingw64/include
	LIBFLAGS += -lsfml-system -lsfml-window -lsfml-graphics
	NAME = $(BINDIR)/sengine.dll
else
	UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
	LIBFLAGS += -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system
	NAME = $(BINDIR)/sengine.so
  endif
  ifeq ($(UNAME_S),Darwin)
	CXXFLAGS += -I/usr/local/include
	LIBFLAGS += -F/Library/Frameworks -framework freetype -framework sfml-window -framework sfml-graphics -framework sfml-system
	NAME = $(BINDIR)/sengine.Framework
  endif
endif

TESTSRCS =			$(TESTDIR)/test.cpp

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
	$(CC) -o $(NAME) $(OBJS) $(LIBFLAGS)

test: $(TESTOBJS)
	$(CC) -o $(BINDIR)/test $(TESTOBJS) -L$(BINDIR) -lsengine

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(BINDIR)/test

re: fclean all

.PHONY: all clean fclean re
