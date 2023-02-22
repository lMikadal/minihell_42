NAME = minishell

CFLAGS = -Wall -Wextra -Werror

MAIN = main.c

CC = gcc

SRCS = g_n_l.c g_n_l_utils.c \
		executor.c executor2.c executor_fork.c executor_fork2.c\
		utils.c utils2.c utils3.c utils4.c free.c

all: $(NAME)

$(NAME): $(OBJ)
	$(CC)  $(CFLAGS) -o $(NAME) $(MAIN)  $(SRCS)

clean:
	rm -rf $(NAME)

re: clean all