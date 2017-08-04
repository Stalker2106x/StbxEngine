CC = g++

RM = rm -f

TEST = $(BINDIR)/test

INCDIR = ./include

EXTLIB = ./extlib

TESTDIR = ./test

SRCDIR = ./src

BINDIR = ./bin

CXXFLAGS = -fPIC -W -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Os -O0 -g -I$(INCDIR) -I$(EXTLIB) -I$(EXTLIB)/sfml/include/ -I$(EXTLIB)/stblib/include/
LDFLAGS = -L$(EXTLIB) -L$(EXTLIB)/libsfml-bin/mingw_win64/ -L$(EXTLIB)/stblib/bin/ -shared -lstblib
test: CXXFLAGS = -W -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Os -O0 -g -I$(INCDIR) -I$(EXTLIB) -I$(EXTLIB)/sfml/include/ -I$(EXTLIB)/stblib/include/
test: LDFLAGS = -L$(EXTLIB)/libsfml-bin/mingw_win32/ -L$(BINDIR) -lsengine -lsfml-system-d -lsfml-window-d -lsfml-graphics-d

ifeq ($(OS),Windows_NT)
	LDFLAGS += -lsfml-system-d -lsfml-window-d -lsfml-graphics-d
	NAME = $(BINDIR)/libsengine.dll
else
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
	LDFLAGS += -lsfml-system-d -lsfml-window-d -lsfml-graphics-d
	NAME = $(BINDIR)/libsengine.so
  endif
  ifeq ($(UNAME_S),Darwin)
	LDFLAGS += -F/Library/Frameworks -framework freetype -framework sfml-window -framework sfml-graphics -framework sfml-system
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
				$(SRCDIR)/MenuItem.cpp			\
				$(SRCDIR)/GUI.cpp			\
				$(SRCDIR)/GUIElement.cpp		\
				$(SRCDIR)/GUIPanel.cpp			\
				$(SRCDIR)/GUIEntity.cpp			\
				$(SRCDIR)/GUIButton.cpp			\
				$(SRCDIR)/Resolver.cpp

OBJS = $(SRCS:.cpp=.o)

## RULES ##

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBS) $(LDFLAGS)

test: $(TESTOBJS)
	$(CC) -o $(TEST) $(TESTOBJS) -L$(BINDIR) $(LIBS) $(LDFLAGS) -lsengine

clean:
	$(RM) $(OBJS) $(TESTOBJS)

fclean: clean
	$(RM) $(NAME) $(TEST)

re: fclean all

.PHONY: all clean fclean re
