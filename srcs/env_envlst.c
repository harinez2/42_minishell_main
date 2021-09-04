#include "main.h"

void	init_envlst(t_arg *arg)
{
	extern char	**environ;
	int			cnt;
	int			dest;
	char		*env;
	char		*value;

	cnt = 0;
	arg->envlst = NULL;
	while (environ[cnt])
	{
		dest = ft_strchr(environ[cnt], '=');
		env = ft_strdup2(environ[cnt], dest);
		value = ft_strdup2(&(environ[cnt][dest + 1]),
				ft_strlen(environ[cnt]) - dest);
		push_back_envlst(&(arg->envlst), env, value, arg);
		cnt ++;
	}
}

void	push_back_envlst(t_env	**envlst, char *env, char *value, t_arg *arg)
{
	t_env	*new_env;
	t_env	*head;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		print_perror_exit(errno, "", "", arg);
	new_env->env = env;
	new_env->value = value;
	new_env->next = NULL;
	head = *envlst;
	if (!head)
	{
		(*envlst) = new_env;
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new_env;
	}
}

int	count_envlst(t_arg *arg)
{
	t_env	*e;
	int		ret;

	ret = 0;
	e = arg->envlst;
	while (e)
	{
		ret++;
		e = e->next;
	}
	return (ret);
}

void	destroy_envlst(t_arg *arg)
{
	t_env	*e;
	t_env	*e_tmp;

	e = arg->envlst;
	while (e)
	{
		secure_free(e->env);
		secure_free(e->value);
		e_tmp = e;
		e = e->next;
		secure_free(e_tmp);
	}
	arg->envlst = NULL;
}
