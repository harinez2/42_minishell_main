#include "main.h"

static void	expander_char(char **text, t_arg *arg)
{
	expander_char_env(text, arg);
	expander_char_quote(text);
}

static int	set_shellenv(char *text, t_arg *arg)
{
	int		pos;
	int		len;
	int		plus;

	pos = ft_strchr(text, '=');
	len = ft_strlen(text);
	plus = 0;
	if (pos == len || pos == 0)
		return (0);
	if (pos >= 1 && text[pos - 1] == '+')
		plus = 1;
	if (pos == 0 || !is_shellver_char(text, 0, pos - plus))
		return (0);
	if (plus && concat_envvalue(text, pos, len, arg) == 1)
		;
	else
		push_back_envlst(&arg->shellenvlst, ft_substr(text, 0, pos - plus),
			ft_substr(text, pos + 1, len), arg);
	return (1);
}

static void	expander_cmd(t_arg *arg, t_cmd *c)
{
	int	i;

	i = 0;
	while (c->param[i])
		expander_char(&(c->param[i++]), arg);
	if (c->redir_in)
		expander_char(&(c->redir_in), arg);
	i = 0;
	while (i < c->redir_out_cnt)
		expander_char(&(c->redir_out[i++]), arg);
	i = 0;
	while (c->param[i])
	{
		if (set_shellenv(c->param[i], arg) == 1)
		{
			i++;
			continue ;
		}
		else
			break ;
	}
}

void	expander(t_arg *arg)
{
	t_cmd	*c;

	if (arg->dbg)
		printf(COL_TX_CYAN"<<< expander results >>>\n"COL_TX_RESET);
	c = arg->cmdlst;
	while (c)
	{
		expander_cmd(arg, c);
		c = c->next;
	}
	if (arg->dbg)
		printf("\n");
	if (arg->dbg)
		cmd_print(arg->cmdlst);
}
