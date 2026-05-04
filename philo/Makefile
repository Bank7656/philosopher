CC = cc
CFLAGS = -g -Wall -Wextra -Werror

MANDATORY_HEADER = philosopher.h
MANDATORY_HEADER_DIR = ./
MANDATORY_SRC = main.c \
				parse.c \
				ft_isdigit.c \
				ft_atoi.c

MANDATORY_SRC_OBJS = $(MANDATORY_SRC:.c=.o)
MANDATORY_OBJS_DIR = ./objects/
MANDATORY_OBJS = $(addprefix $(MANDATORY_OBJS_DIR), $(MANDATORY_SRC_OBJS))

NAME = philo

OBJS = $(MANDATORY_OBJS)
OBJ_DIR = $(MANDATORY_OBJS_DIR)
HEADER = $(MANDATORY_HEADER)
HEADER_DIR = $(MANDATORY_HEADER_DIR)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o:%.c 
	$(CC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

