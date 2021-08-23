#include "main.h"

int	get_token(char *read, int *i)
{
	int		ret;

	if (read[*i] == '"')
	{
		while (read[++(*i)] != '"')
			;
		ret = TKN_DBLQUOTE;
	}
	else if (read[*i] == '\'')
	{
		while (read[++(*i)] != '\'')
			;
		ret = TKN_SGLQUOTE;
	}
	else if (read[*i] == ';')
		ret = TKN_COLON;
	else if (read[*i] == '&' && read[*i + 1] != '&')
		ret = TKN_AMP;
	else if (read[*i] == '|' && read[*i + 1] != '|')
		ret = TKN_SINGLE_OR;
	else if (read[*i] == '<')
		ret = TKN_REDIR_LEFT;
	else if (read[*i] == '>' && read[*i + 1] != '>')
		ret = TKN_REDIR_RIGHT;
	else if (read[*i] == '>' && read[*i + 1] == '>')
	{
		(*i)++;
		ret = TKN_HEREDOC;
	}
	else if (ft_strncmp(&read[*i], "||", 2) == 0
		|| ft_strncmp(&read[*i], "&&", 2) == 0)
	{
		(*i)++;
		ret = TKN_DBLANDOR;
	}
	else
	{
		while (!is_whitespace(read[*i]) && read[*i] != '\0' && !is_delim_or_redir(read[*i]))
			(*i)++;
		return (TKN_CHAR);
	}
	(*i)++;
	return (ret);
}
