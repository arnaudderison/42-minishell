LIBFT = libft.a
LIBFT_I = ./include/
CC = gcc
OBJ_DIR = obj
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -I$(LIBFT_I)

# Colors
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
CYAN=\033[0;36m
NC=\033[0m

# Libft sources
LIBFT_SRCS = $(wildcard src/*/*.c)
LIBFT_OBJS = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(LIBFT_SRCS))

# Compilation rules
all: $(LIBFT)

$(LIBFT): $(LIBFT_OBJS)
	@ar rcs $@ $^
	@echo "\n${YELLOW}Library $@ created.${NC}"

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	@printf "${CYAN}\rCompiling $<...${NC}"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "${GREEN}Object files cleaned.${NC}"

fclean: clean
	@rm -f $(LIBFT)
	@echo "${RED}All files removed.${NC}"

re: fclean all

.PHONY: all clean fclean re