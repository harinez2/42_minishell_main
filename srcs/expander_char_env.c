#include "main.h"

static char	*expander_char_env_judge(char *env, t_arg *arg)
{
	t_env	*tmp;
	char	*value;

	if (ft_strncmp(env, "?", 1) == 0)
		return (ft_itoa(arg->last_exit_status));
	tmp = arg->envlst;
	while (tmp->next)
	{
		if (!ft_strncmp(env, tmp->env, ft_strlen(env)))
		{
			value = ft_strdup2(tmp->value, ft_strlen(tmp->value));
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static int	expander_char_env_cut(char **text, int start, int end, t_arg *arg)
{
	char	*env;
	char	*before;
	char	*after;
	char	*value;
	char	*tmp;
	int		next_start;

	env = ft_strdup2(&(*text)[start + 1], end - start - 1);
	value = expander_char_env_judge(env, arg);
	if (!value)
	{
		free(env);
		return (0);
	}
	before = ft_strdup2((*text), start);
	after = ft_strdup2(&(*text)[end], ft_strlen(*text) - end);
	tmp = ft_strjoin3(before, value, after);
	next_start = ft_strlen(before) + ft_strlen(value);
	free(*text);
	free(before);
	free(after);
	free(value);
	free(env);
	(*text) = tmp;
	return (next_start);
}

static void	expander_char_env_replace(char **text, int *cnt, t_arg *arg)
{
	int		i;
	int		tmp;

	i = *cnt;
	if ((*text)[(*cnt) + 1] == '"')
	{
		(*cnt) += 2;
		return ;
	}
	i++;
	while ((*text)[i])
	{
		if ((*text)[i] < '0' || ('9' < (*text)[i]  && (*text)[i] < 'A') || ('Z' < (*text)[i]  && (*text)[i] < 'a') || ('z' < (*text)[i]))
		{
			tmp = expander_char_env_cut(text, *cnt, i, arg);
			if (tmp == 0)
			{
				(*text) = ft_strdup("");
			}
			(*cnt) = tmp;
			break ;
		}
		i++;
	}
	if (i == (int)ft_strlen(*text))
	{
		tmp = expander_char_env_cut(text, *cnt, i, arg);
		if (tmp == 0)
		{
			(*text) = ft_strdup("");
		}
		// commentted out below line. please check this.
		(*cnt) = tmp;
	}
}

void	expander_char_env(char **text, t_arg *arg)
{
	int		cnt;
	int		escape;

	cnt = 0;
	escape = 0;
	while ((*text)[cnt])
	{	
		if ((*text)[cnt] == '\'' && escape == 0)
			escape = 1;
		else if ((*text)[cnt] == '\'' && escape == 1)
			escape = 0;
		else if ((*text)[cnt] == '$' && escape != 1)
			expander_char_env_replace(text, &cnt, arg);
		else if ((*text)[cnt] == '\\' && (*text)[cnt + 1] != '\0')
			cnt ++;
		cnt ++;
	}
}
