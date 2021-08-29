#ifndef ENUMS_H
# define ENUMS_H

typedef enum e_token_type {
	TKN_EOF,
	TKN_SEMICOLON,
	TKN_AMP,
	TKN_SINGLE_OR,
	TKN_REDIR_LEFT,
	TKN_REDIR_RIGHT,
	TKN_HEREDOC,
	TKN_DBLANDOR,
	TKN_STRING,
	TKN_TYPE_LENGTH
}	t_token_type;

#endif
