NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -MD -MP
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

# Détection du système d'exploitation
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    CFLAGS += -D LINUX
    # Vérification de readline sur Linux
    READLINE_EXIST := $(shell ldconfig -p | grep readline)
    ifeq ($(READLINE_EXIST),)
        $(info Installing readline...)
        INSTALL_READLINE := $(shell sudo apt-get update && sudo apt-get install -y libreadline-dev)
    endif
    READLINE_FLAGS = -lreadline
endif
ifeq ($(UNAME_S),Darwin)
    CFLAGS += -D OSX
    # Vérification de readline sur MacOS (via Homebrew)
    READLINE_EXIST := $(shell brew list | grep readline)
    ifeq ($(READLINE_EXIST),)
        $(info Installing readline...)
        INSTALL_READLINE := $(shell brew install readline)
    endif
    # Chemins spécifiques pour MacOS
    READLINE_FLAGS = -L$(shell brew --prefix readline)/lib -lreadline -I$(shell brew --prefix readline)/include
endif

MINISH_SRCS = src/main.c \
src/builtins/cd.c \
src/builtins/echo.c \
src/builtins/pwd.c \
src/builtins/env.c \
src/builtins/execb.c \
src/builtins/exit.c \
src/builtins/unset.c \
src/builtins/export/is_valid_identifier.c \
src/builtins/export/export.c \
src/builtins/export/print_env.c \
src/cmd/cmd.c \
src/cmd/access.c \
src/cmd/cmd_utils.c \
src/environment/edit_var_env.c \
src/environment/get_env.c \
src/environment/is_new_var.c \
src/environment/set_var_env.c \
src/environment/add_var_env.c \
src/environment/get_path.c \
src/environment/init_envp.c \
src/error/free_env.c \
src/error/free_tokens.c \
src/error/print_error.c \
src/exec/exec.c \
src/exec/exec_multi_cmd.c \
src/exec/pipes.c \
src/expansion/get_var_name.c \
src/expansion/expansion.c \
src/expansion/get_value.c \
src/lexer/create_tokenisation.c \
src/lexer/manage_quote.c \
src/lexer/utils.c \
src/parsing/clean_quote.c \
src/parsing/is_operator.c \
src/parsing/is_pipe_syntax.c \
src/parsing/is_redir_syntax.c \
src/parsing/parsing.c \
src/parsing/print_parse_error.c \
src/parsing/handle_parsing.c \
src/redir/redir.c \
src/redir/redir_utils.c \
src/signals/handle_sigint_prompt.c \
src/signals/signals.c
MINISH_OBJS = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(MINISH_SRCS))
DEPS = $(MINISH_OBJS:.o=.d)


all: check_readline $(NAME)

check_readline:
	@echo "${CYAN}Checking readline installation...${NC}"
ifeq ($(UNAME_S),Linux)
	@if ! dpkg -l | grep -q libreadline-dev; then \
		echo "${YELLOW}Installing readline...${NC}"; \
		sudo apt-get update && sudo apt-get install -y libreadline-dev; \
	else \
		echo "${GREEN}Readline is already installed.${NC}"; \
	fi
endif
ifeq ($(UNAME_S),Darwin)
	@if ! brew list | grep -q readline; then \
		echo "${YELLOW}Installing readline...${NC}"; \
		brew install readline; \
	else \
		echo "${GREEN}Readline is already installed.${NC}"; \
	fi
endif

$(NAME): $(LIBFT) $(MINISH_OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(MINISH_OBJS) -L$(LIBFT_DIR) -lft $(READLINE_FLAGS) -o $@
	@echo "${YELLOW}Executable $(NAME) created.${NC}"

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	@echo "${CYAN}Compiling $<...${NC}"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEPS)

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "${GREEN}Object files cleaned.${NC}"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "${RED}All files removed.${NC}"

re: fclean all

.PHONY: all clean fclean re check_readline
