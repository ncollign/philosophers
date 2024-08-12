CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS_DIR = main-core
SRCS = $(shell find $(SRCS_DIR) -name "*.c")
OBJS = $(SRCS:.c=.o)
INCLUDES = -I$(SRCS_DIR)
EXEC = philo

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c $(SRCS_DIR)/philo.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re