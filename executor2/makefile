NAME = minishell

CFLAGS = -Wall -Wextra -Werror

MAIN = main.c

CC = gcc

SRCS = g_n_l.c g_n_l_utils.c \
		utils.c free.c

all: $(NAME)

$(NAME): $(OBJ)
	$(CC)  $(CFLAGS) -o $(NAME) $(MAIN)  $(SRCS)

clean:
	rm -rf $(NAME)

re: clean all