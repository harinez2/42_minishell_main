#include "main.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

int	is_delim_or_redir(char c)
{
	if (c == ';' || c == '|' || c == '&' || c == '>' || c == '<' || c == '"' || c == '\'')
		return (1);
	else
		return (0);
}

void	skip_whitespace(char *read, int *i)
{
	while (is_whitespace(read[*i]))
		(*i)++;
}

void	print_token_type(int type)
{
	if (type == TKN_DBLQUOTE)
		printf("<dbl quote>");
	else if (type == TKN_SGLQUOTE)
		printf("<sgl quote>");
	else if (type == TKN_COLON)
		printf("<colon    >");
	else if (type == TKN_AMP)
		printf("<amp      >");
	else if (type == TKN_SINGLE_OR)
		printf("<single or>");
	else if (type == TKN_REDIR_LEFT)
		printf("<rdr left >");
	else if (type == TKN_REDIR_RIGHT)
		printf("<rdr right>");
	else if (type == TKN_HEREDOC)
		printf("<heredoc  >");
	else if (type == TKN_DBLANDOR)
		printf("<dbl andor>");
	else if (type == TKN_CHAR)
		printf("<char     >");
}
