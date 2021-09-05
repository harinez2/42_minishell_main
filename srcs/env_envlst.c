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

static t_env	*create_newnode(char *env, char *value, t_arg *arg)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		print_perror_exit(errno, "", "", arg);
	new_env->env = env;
	new_env->value = value;
	new_env->next = NULL;
	return (new_env);
}

void	push_back_envlst(t_env	**envlst, char *env, char *value, t_arg *arg)
{
	t_env	*new_env;
	t_env	*head;
	t_env	*tmp;

	tmp = get_node_from_envlst(arg, env);
	if (tmp)
	{
		secure_free(tmp->value);
		tmp->value = value;
		return ;
	}
	new_env = create_newnode(env, value, arg);
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

void	delete_env_from_envlst(t_arg *arg, char *envname)
{
	t_env		*e;
	t_env		*e_prev;

	e = arg->envlst;
	e_prev = NULL;
	while (e != NULL)
	{
		if (ft_strncmp(e->env, envname, ft_strlen(envname) + 1) == 0)
		{
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
}
