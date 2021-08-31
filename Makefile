NAME		= minishell
INCLUDE		= -I./inc
SRC_DIR		= srcs
SRCS		= \
				$(SRC_DIR)/arg_init_destroy.c \
				$(SRC_DIR)/builtin_cd.c \
				$(SRC_DIR)/builtin_echo.c \
				$(SRC_DIR)/builtin_env.c \
				$(SRC_DIR)/builtin_export.c \
				$(SRC_DIR)/builtin_pwd.c \
				$(SRC_DIR)/error.c \
				$(SRC_DIR)/executer.c \
				$(SRC_DIR)/executer_cmdexec.c \
				$(SRC_DIR)/executer_util.c \
				$(SRC_DIR)/lexer.c \
				$(SRC_DIR)/lexer_util.c \
				$(SRC_DIR)/lib_ft.c \
				$(SRC_DIR)/lib_ft2.c \
				$(SRC_DIR)/lib_util_dbg.c \
				$(SRC_DIR)/lib_util.c \
				$(SRC_DIR)/main.c \
				$(SRC_DIR)/parser_bnf_compoundcmd.c \
				$(SRC_DIR)/parser_bnf_redirection.c \
				$(SRC_DIR)/parser_heredoc.c \
				$(SRC_DIR)/parser.c \
				$(SRC_DIR)/recogin_expander.c \
				$(SRC_DIR)/struct_add.c \
				$(SRC_DIR)/struct_init_destroy.c \
				$(SRC_DIR)/struct_lst.c \
				$(SRC_DIR)/struct_print.c
OBJS		= $(SRCS:.c=.o)
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
CFLAGS_RL	= -lreadline
DBGFLG		= -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(CFLAGS_RL) $(INCLUDE) -o $(NAME)

.c.o: $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

debug: $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) $(CFLAGS_RL) $(INCLUDE) $(DBGFLG) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
