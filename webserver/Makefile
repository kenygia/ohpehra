NAME=lightbearer
CC=gcc
CFLAGS= -Wall -W -Werror -g -O
LDFLAGS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
GCH=$(SRC:.h=.h.gch)
RM=rm -f



all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	@$(CC) -c $< $(CFLAGS) -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

.PHONY: all clean fclean
