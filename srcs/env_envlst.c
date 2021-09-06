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

void	delete_env_from_envlst(t_env **envlst, char *envname)
{
	t_env		*e;
	t_env		*e_prev;

	e = *envlst;
	e_prev = NULL;
	while (e != NULL)
	{
		if (ft_strncmp(e->env, envname, ft_strlen(envname) + 1) == 0)
		{
			if (e == *envlst)
				*envlst = e->next;
			else
				e_prev->next = e->next;
			secure_free(e->env);
			secure_free(e->value);
			secure_free(e);
			return ;
		}
		e_prev = e;
		e = e->next;
	}
	return ;
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
	e = arg->shellenvlst;
	while (e)
	{
		secure_free(e->env);
		secure_free(e->value);
		e_tmp = e;
		e = e->next;
		secure_free(e_tmp);
	}
	arg->shellenvlst = NULL;
}
