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

	pos = ft_strchr(text, '=');
	len = ft_strlen(text);
	if (pos != len)
	{
		push_back_envlst(&arg->shellenvlst, ft_substr(text, 0, pos),
			ft_substr(text, pos + 1, len), arg);
		return (1);
	}
	return (0);
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

	c = arg->cmdlst;
	while (c)
	{
		expander_cmd(arg, c);
		c = c->next;
	}
	if (arg->dbg)
		cmd_print(arg->cmdlst);
}
