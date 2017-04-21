CC = g++

RM = rm -f

INCDIR = include

SRCDIR = src

BINDIR = bin

LDFLAGS = -lsfml-audio -lsfml-system -lsfml-window -lsfml-graphics

ifeq ($(OS),Windows_NT)
	CXXFLAGS = -W -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Os -O2 -g3 -I$(INCDIR)
	NAME = $(BINDIR)/racedriver-win32.exe
else
	UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
	CXXFLAGS = -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Os -O2 -g3 -I$(INCDIR) -I/usr/include
	NAME = $(BINDIR)/racedriver-linux
  endif
  ifeq ($(UNAME_S),Darwin)
	CXXFLAGS = -Wall -Wextra -pedantic -Wshadow -Woverloaded-virtual -std=c++0x -Os -O2 -g3 -I$(INCDIR) -I/usr/local/include
	LDFLAGS += -L/usr/local/lib
	NAME = $(BINDIR)/racedriver-macos
  endif
endif

SRCS =				$(SRCDIR)/main.cpp		\
				$(SRCDIR)/Engine.cpp		\
				$(SRCDIR)/Graphics.cpp		\
				$(SRCDIR)/Console.cpp

OBJS = $(SRCS:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CXXFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
