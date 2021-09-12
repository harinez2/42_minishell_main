#include "main.h"

static void	expander_char(char **text, t_arg *arg)
{
	expander_char_env(text, arg);
	expander_char_quote(text);
}

// accept 'NAME=value' or 'NAME+=value'
static int	accept_envname_value_pair(char *text, t_arg *arg)
{
	int		eqpos;
	int		len;
	int		plus;

	if (!is_valid_env_definition(text))
		return (0);
	eqpos = ft_strchr(text, '=');
	len = ft_strlen(text);
	plus = 0;
	if (text[eqpos - 1] == '+')
		plus = 1;
	if (plus && concat_envvalue(text, eqpos, len, arg) == 1)
		;
	else
		push_back_envlst(&arg->shellenvlst, ft_substr(text, 0, eqpos - plus),
			ft_substr(text, eqpos + 1, len), arg);
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
		if (accept_envname_value_pair(c->param[i], arg) == 0)
			break ;
		i++;
	}
	while (i-- > 0)
		remove_cmdparam_head(c);
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
