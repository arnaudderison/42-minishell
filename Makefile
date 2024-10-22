NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
I_LIBFT = ./include/lib/libft/include/
I_MINISH = ./include/
INCLUDES = -I$(I_LIBFT) -I$(I_MINISH)
OBJ_DIR = obj
LIBFT_DIR = ./include/lib/libft/
LIBFT = $(LIBFT_DIR)libft.a

RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
CYAN=\033[0;36m
NC=\033[0m

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    CFLAGS += -D LINUX
endif
ifeq ($(UNAME_S),Darwin)
    CFLAGS += -D OSX
endif

MINISH_SRCS = src/main.c $(wildcard src/*/*.c)
MINISH_OBJS = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(MINISH_SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(MINISH_OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(MINISH_OBJS) -L$(LIBFT_DIR) -lft -o $@
	@echo "${YELLOW}Executable $(NAME) created.${NC}"

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	@echo "${CYAN}Compiling $<...${NC}"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "${GREEN}Object files cleaned.${NC}"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "${RED}All files removed.${NC}"

re: fclean all

.PHONY: all clean fclean re