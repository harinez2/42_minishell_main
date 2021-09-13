NAME		= minishell
INCLUDE		= -I./inc -I $(shell brew --prefix readline)/include
SRC_DIR		= srcs
SRCS		= \
				$(SRC_DIR)/arg_destroy.c \
				$(SRC_DIR)/arg_init.c \
				$(SRC_DIR)/builtin_cd.c \
				$(SRC_DIR)/builtin_cd_util.c \
				$(SRC_DIR)/builtin_echo.c \
				$(SRC_DIR)/builtin_env.c \
				$(SRC_DIR)/builtin_exit.c \
				$(SRC_DIR)/builtin_export.c \
				$(SRC_DIR)/builtin_export_print.c \
				$(SRC_DIR)/builtin_pwd.c \
				$(SRC_DIR)/builtin_unset.c \
				$(SRC_DIR)/env_environ.c \
				$(SRC_DIR)/env_envlst.c \
				$(SRC_DIR)/env_envlst_add.c \
				$(SRC_DIR)/env_envlst_util.c \
				$(SRC_DIR)/error.c \
				$(SRC_DIR)/error_custom.c \
				$(SRC_DIR)/executer.c \
				$(SRC_DIR)/executer_builtin_nofork.c \
				$(SRC_DIR)/executer_cmdexec.c \
				$(SRC_DIR)/executer_cmdexec_shellcmd.c \
				$(SRC_DIR)/executer_util.c \
				$(SRC_DIR)/expander.c \
				$(SRC_DIR)/expander_char_env.c \
				$(SRC_DIR)/expander_char_quote.c \
				$(SRC_DIR)/lexer.c \
				$(SRC_DIR)/lexer_util.c \
				$(SRC_DIR)/lib_ft.c \
				$(SRC_DIR)/lib_ft2.c \
				$(SRC_DIR)/lib_ft3.c \
				$(SRC_DIR)/lib_ft4.c \
				$(SRC_DIR)/lib_ft5.c \
				$(SRC_DIR)/lib_util.c \
				$(SRC_DIR)/lib_util_dbg.c \
				$(SRC_DIR)/main.c \
				$(SRC_DIR)/parser.c \
				$(SRC_DIR)/parser_bnf_compoundcmd.c \
				$(SRC_DIR)/parser_bnf_redirection.c \
				$(SRC_DIR)/parser_heredoc.c \
				$(SRC_DIR)/signal.c \
				$(SRC_DIR)/struct_add.c \
				$(SRC_DIR)/struct_init_destroy.c \
				$(SRC_DIR)/struct_lst.c \
				$(SRC_DIR)/struct_print.c
OBJS		= $(SRCS:.c=.o)
DEPS		= $(SRCS:%.c=%.d) $(NAME).d
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -MMD -MP
CFLAGS_RL	= -lreadline -lhistory -L$(shell brew --prefix readline)/lib
DBGFLG		= -g3 -fsanitize=address

all: $(NAME)

-include $(DEPS)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(CFLAGS_RL) $(INCLUDE) -o $(NAME)

.c.o: $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

debug: $(SRCS)
	clang $(SRCS) $(CFLAGS) $(CFLAGS_RL) $(INCLUDE) $(DBGFLG) -o $(NAME)

debugwsl: $(SRCS)
	clang $(SRCS) $(CFLAGS) -lreadline -lhistory -I./inc $(DBGFLG) -o $(NAME)

protogen:
	python3 util/prototype_generator.py

setup:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	export PATH=$PATH:~/.brew/bin
	brew install readline

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
