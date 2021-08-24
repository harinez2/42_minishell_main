NAME		= minishell
INCLUDE		= -I./inc
SRC_DIR		= srcs
SRCS		= \
				$(SRC_DIR)/builtin_cd.c \
				$(SRC_DIR)/builtin_echo.c \
				$(SRC_DIR)/builtin_env.c \
				$(SRC_DIR)/builtin_export.c \
				$(SRC_DIR)/builtin_pwd.c \
				$(SRC_DIR)/cmd_exec.c \
				$(SRC_DIR)/cmd_pipe.c \
				$(SRC_DIR)/error.c \
				$(SRC_DIR)/lib_ft.c \
				$(SRC_DIR)/lib_ft2.c \
				$(SRC_DIR)/lib_lst.c \
				$(SRC_DIR)/lib_util.c \
				$(SRC_DIR)/main.c \
				$(SRC_DIR)/recogin_executer.c \
				$(SRC_DIR)/recogin_lexer.c \
				$(SRC_DIR)/recogin_lexer_util.c \
				$(SRC_DIR)/recogin_parser.c \
				$(SRC_DIR)/recogin_runbuiltincmd.c
OBJS		= $(SRCS:.c=.o)
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
CFLAGS_RL	= -lreadline
DBGFLG		= -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(CFLAGS_RL) $(INCLUDE) -o $(NAME)

main.o: main.c
	$(CC) $(CFLAGS) $(CFLAGS_RL) $(INCLUDE) -c $< -o $(<:.c=.o)

.c.o: $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

debug: $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) $(INCLUDE) $(DBGFLG) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
