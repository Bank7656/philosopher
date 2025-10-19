CC = cc
# CFLAGS = -Wall -Wextra -Werror

MANDATORY_HEADER = philosopher.h
MANDATORY_HEADER_DIR = ./
MANDATORY_SRC = main.c \
			table.c \
			routine.c
MANDATORY_SRC_OBJS = $(MANDATORY_SRC:.c=.o)
MANDATORY_OBJS_DIR = ./objects/
MANDATORY_OBJS = $(addprefix $(MANDATORY_OBJS_DIR), $(MANDATORY_SRC_OBJS))

NAME = philo

OBJS = $(MANDATORY_OBJS)
OBJ_DIR = $(MANDATORY_OBJS_DIR)
HEADER = $(MANDATORY_HEADER)
HEADER_DIR = $(MANDATORY_HEADER_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o:%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

