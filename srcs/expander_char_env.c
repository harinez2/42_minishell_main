#include "main.h"

static char	*get_env_value(char *env, t_arg *arg)
{
	t_env	*tmp;

	if (ft_strncmp(env, "?", 1) == 0)
	{
		secure_free(env);
		return (ft_itoa(arg->last_exit_status));
	}
	tmp = get_node_from_envlst(arg->shellenvlst, env);
	if (!tmp)
		tmp = get_node_from_envlst(arg->envlst, env);
	if (tmp)
	{
		if (arg->dbg)
			printf("      found in env...%s/%s\n", env, tmp->value);
		secure_free(env);
		return (ft_strdup(tmp->value));
	}
	else
	{
		if (arg->dbg)
			printf("      env not found...%s\n", env);
		secure_free(env);
		return (ft_strdup(""));
	}
}

static int	replace_env_value(char **text, int start, int end, t_arg *arg)
{
	char	*before;
	char	*after;
	char	*value;
	char	*new_text;
	int		next_start;

	value = get_env_value(
			ft_strdup2(&(*text)[start + 1], end - (start + 1)), arg);
	before = ft_strdup2((*text), start);
	after = ft_strdup2(&(*text)[end], ft_strlen(*text) - end);
	new_text = ft_strjoin3(before, value, after);
	next_start = ft_strlen(before) + ft_strlen(value) - 1;
	if (arg->dbg)
		printf("      cutting...<%s><%s><%s>, nextstart:%d\n",
			before, value, after, next_start);
	if (arg->dbg)
		printf("      replaced value...<%s>\n", new_text);
	secure_free(*text);
	secure_free(before);
	secure_free(after);
	secure_free(value);
	(*text) = new_text;
	return (next_start);
}

static void	check_and_replace_env(char **text, int *cnt, t_arg *arg)
{
	int		i;
	int		tmp;

	i = *cnt;
	i++;
	while ((*text)[i])
	{
		if (arg->dbg)
			printf("    is env char?...%d,%c\n", i, (*text)[i]);
		if (i == *cnt + 1 && (*text)[i] == '?')
		{
			i++;
			break ;
		}
		else if (is_shellver_char_onechar((*text)[i]))
			i++;
		else
			break ;
	}
	tmp = replace_env_value(text, *cnt, i, arg);
	(*cnt) = tmp;
}

void	expander_char_env(char **text, t_arg *arg)
{
	int		cnt;
	int		escape;

	cnt = 0;
	escape = 0;
	while ((*text)[cnt])
	{	
		if (arg->dbg)
			printf("  cnt: %d, char: %c, esc: %d\n", cnt, (*text)[cnt], escape);
		if ((*text)[cnt] == '\'' && escape == 0)
			escape = 1;
		else if ((*text)[cnt] == '\'' && escape == 1)
			escape = 0;
		else if ((*text)[cnt] == '$' && (*text)[cnt + 1] == '\0')
			return ;
		else if ((*text)[cnt] == '$' && escape != 1)
			check_and_replace_env(text, &cnt, arg);
		else if ((*text)[cnt] == '\\' && (*text)[cnt + 1] != '\0')
			cnt ++;
		cnt ++;
	}
}
