#ifndef CONSTANTS_H
# define CONSTANTS_H

# define	MAX_ENVP				100
# define	MAX_PATH				1024
# define	MAX_ARGNUM				100

# define	PP_READ					0
# define	PP_WRITE				1

# define	PNT_CMD					1
# define	PNT_PARAM				2

# define	ERR_ENV_INVALID			-1
# define	ERR_NOT_ENOUGH_PARAM	-2
# define	ERR_FAILED_TO_OPEN_FILE	-3
# define	ERR_PIPE				-4
# define	ERR_FAILED_TO_FORK		-5
# define	ERR_FAILED_TO_EXEC		-6
# define	ERR_FAILED_TO_MALLOC	-7
# define	ERR_CD_INVALIDPATH		-8

# define	TKN_DBLQUOTE			11
# define	TKN_SGLQUOTE			12
# define	TKN_COLON				13
# define	TKN_AMP					14
# define	TKN_SINGLE_OR			15
# define	TKN_REDIR_LEFT			16
# define	TKN_REDIR_RIGHT			17
# define	TKN_HEREDOC				18
# define	TKN_DBLANDOR			19
# define	TKN_CHAR				20

# define	CONN_PIPE				31
# define	CONN_REDIR_OUT			32

#endif
