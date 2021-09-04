#ifndef CONSTANTS_H
# define CONSTANTS_H

# define	MAX_ENVP				100
# define	MAX_PATH				1024
# define	MAX_ARGNUM				100
# define	MAX_TOKENNUM			1000
# define	MAX_RETRY_HEREDOC		10

# define	PP_READ					0
# define	PP_WRITE				1

# define	PNT_CMD					1
# define	PNT_PARAM				2

# define	CONN_PIPE				31
# define	CONN_REDIR_OUT			32
# define	CONN_AMP				33

# define	HEREDOC_FILENAME_LEN	14

# define COL_BK_CYAN	"\x1b[46m"
# define COL_BK_RESET	"\x1b[49m"

# define COL_TX_CYAN	"\x1b[36m"
# define COL_TX_RESET	"\x1b[39m"

# define BACK_CURSOR			"\033[2D"
# define CLEAR_FROM_CURSOR		"\033[0K"
# define SHELL_PROMPT			COL_BK_CYAN"minishell>"COL_BK_RESET" "

#endif
