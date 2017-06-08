CC = g++

RM = rm -f

INCDIR = include

EXTLIB = extlib

SRCDIR = src

BINDIR = bin

CXXFLAGS = -W -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Os -O0 -g -I$(INCDIR) -I$(EXTLIB)

LIBS = -L$(EXTLIB)

ifeq ($(OS),Windows_NT)
	CXXFLAGS += -IW:/Software/mingw32/include -IC:/mingw64/include
	LIBS += -lsfml-system -lsfml-window -lsfml-graphics
	NAME = $(BINDIR)/sengine-win32.exe
else
	UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
	LIBS += -lsfml-graphics -lsfml-window -lsfml-system
	NAME = $(BINDIR)/sengine-linux
  endif
  ifeq ($(UNAME_S),Darwin)
	CXXFLAGS = -I/usr/local/include
	LIBS += -F/Library/Frameworks -framework freetype -framework sfml-window -framework sfml-graphics -framework sfml-system
	NAME = $(BINDIR)/sengine-macos
  endif
endif

SRCS =				$(EXTLIB)/pugixml/src/pugixml.cpp	\
				$(SRCDIR)/main.cpp			\
				$(SRCDIR)/Engine.cpp			\
				$(SRCDIR)/Console.cpp			\
				$(SRCDIR)/Commands.cpp			\
				$(SRCDIR)/Keybinds.cpp			\
				$(SRCDIR)/Control.cpp			\
				$(SRCDIR)/Menu.cpp

OBJS = $(SRCS:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
