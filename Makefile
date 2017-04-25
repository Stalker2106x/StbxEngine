CC = g++

RM = rm -f

INCDIR = include

SRCDIR = src

BINDIR = bin

ifeq ($(OS),Windows_NT)
	CXXFLAGS = -W -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Os -O2 -g3 -I$(INCDIR)
	LIBS = -lsfml-system -lsfml-window -lsfml-graphics
	NAME = $(BINDIR)/sengine-win32.exe
else
	UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
	CXXFLAGS = -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Os -O2 -g3 -I$(INCDIR) -I/usr/include
	LIBS = -lsfml-system -lsfml-window -lsfml-graphics
	NAME = $(BINDIR)/sengine-linux
  endif
  ifeq ($(UNAME_S),Darwin)
	CXXFLAGS = -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Os -O2 -g3 -I$(INCDIR) -I/usr/local/include
	LIBS = -F/Library/Frameworks -framework freetype -framework sfml-window -framework sfml-graphics -framework sfml-system
	NAME = $(BINDIR)/sengine-macos
  endif
endif

SRCS =				$(SRCDIR)/main.cpp		\
				$(SRCDIR)/Engine.cpp		\
				$(SRCDIR)/Console.cpp		\
				$(SRCDIR)/Commands.cpp

OBJS = $(SRCS:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CXXFLAGS) $(LIBS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
