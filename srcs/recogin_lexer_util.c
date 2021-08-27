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
	if (c == ';' || c == '|' || c == '&' || c == '>'
		|| c == '<' || c == '"' || c == '\'')
		return (1);
	else
		return (0);
}

void	skip_whitespace(char *read, int *i)
{
	while (is_whitespace(read[*i]))
		(*i)++;
}

void	print_token_type(t_token_type type)
{
	static char	token_type_text[TKN_TYPE_LENGTH][16] = {
		"TKN_EOF        ",
		"TKN_DBLQUOTE   ",
		"TKN_SGLQUOTE   ",
		"TKN_SEMICOLON  ",
		"TKN_AMP        ",
		"TKN_SINGLE_OR  ",
		"TKN_REDIR_LEFT ",
		"TKN_REDIR_RIGHT",
		"TKN_HEREDOC    ",
		"TKN_DBLANDOR   ",
		"TKN_CHAR       "
	};

	if (0 <= type && type < TKN_TYPE_LENGTH)
		printf("%s", token_type_text[type]);
	else
		printf("<out of range>");
}

void	print_token_info(int token_info[][2], char *read)
{
	int		i;

	printf("<< lexer results >>\n");
	printf(" i  token-type         starti  content\n");
	i = 0;
	while (token_info[i][0] != TKN_EOF)
	{
		printf("%2d  ", i);
		print_token_type(token_info[i][0]);
		printf("    %3d     ", token_info[i][1]);
		ft_putstr(read + token_info[i][1],
			token_info[i + 1][1] - token_info[i][1]);
		printf("\n");
		i++;
	}
	printf("\n");
}
