NAME    = matrix_circus
CC      = gcc
CFLAGS  = -Wall -Wextra -g
LDLIBS  = -lm

SRCS    = matrix_circus.c

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(LDLIBS)

clean:
	rm -f $(NAME)

re: clean all