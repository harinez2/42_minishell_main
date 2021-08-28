#include "main.h"

static int	identify_quotes(char *read, int *i)
{
	int		ret;

	ret = 0;
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
	return (ret);
}

static int	identify_doublectrls(char *read, int *i)
{
	int		ret;

	if (ft_strncmp(&read[*i], ">>", 2) == 0)
		ret = TKN_HEREDOC;
	else
		ret = TKN_DBLANDOR;
	(*i)++;
	return (ret);
}

static int	identify_chars(char *read, int *i)
{
	while (!is_whitespace(read[*i]) && read[*i] != '\0'
		&& !is_delim_or_redir(read[*i]))
		(*i)++;
	(*i)--;
	return (TKN_CHAR);
}

static t_token_type	get_token(char *read, int *i)
{
	t_token_type	ret;

	if (read[*i] == '"' || read[*i] == '\'')
		ret = identify_quotes(read, i);
	else if (read[*i] == ';')
		ret = TKN_SEMICOLON;
	else if (read[*i] == '&' && read[*i + 1] != '&')
		ret = TKN_AMP;
	else if (read[*i] == '|' && read[*i + 1] != '|')
		ret = TKN_SINGLE_OR;
	else if (read[*i] == '<')
		ret = TKN_REDIR_LEFT;
	else if (read[*i] == '>' && read[*i + 1] != '>')
		ret = TKN_REDIR_RIGHT;
	else if (ft_strncmp(&read[*i], ">>", 2) == 0
		|| ft_strncmp(&read[*i], "||", 2) == 0
		|| ft_strncmp(&read[*i], "&&", 2) == 0)
		ret = identify_doublectrls(read, i);
	else
		ret = identify_chars(read, i);
	(*i)++;
	return (ret);
}

int	lexer(t_arg *arg, char *read, int token_info[][3])
{
	int		i;
	int		starti;
	int		tki_i;

	(void)arg;
	i = 0;
	tki_i = 0;
	while (1)
	{
		skip_whitespace(read, &i);
		if (read[i] == '\0')
			break ;
		starti = i;
		token_info[tki_i][0] = get_token(read, &i);
		token_info[tki_i][1] = starti;
		token_info[tki_i++][2] = i;
	}
	token_info[tki_i][0] = TKN_EOF;
	token_info[tki_i][1] = i;
	token_info[tki_i++][2] = i;
	return (0);
}
