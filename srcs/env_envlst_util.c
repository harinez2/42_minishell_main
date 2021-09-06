#include "main.h"

t_env	*get_node_from_envlst(t_env	*envlst, char *envname)
{
	t_env		*e;

	e = envlst;
	while (e != NULL)
	{
		if (ft_strncmp(e->env, envname, ft_strlen(envname) + 1) == 0)
			return (e);
		e = e->next;
	}
	return (NULL);
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

static int	update_existing_env(
	t_env	**envlst, char *env, char *value, t_arg *arg)
{
	t_env	*tmp;

	tmp = get_node_from_envlst(*envlst, env);
	if (tmp)
	{
		secure_free(tmp->value);
		tmp->value = value;
		secure_free(env);
		return (1);
	}
	tmp = get_node_from_envlst(arg->envlst, env);
	if (tmp)
	{
		secure_free(tmp->value);
		tmp->value = value;
		secure_free(env);
		return (1);
	}
	return (0);
}

void	push_back_envlst(t_env	**envlst, char *env, char *value, t_arg *arg)
{
	t_env	*new_env;
	t_env	*head;

	if (update_existing_env(envlst, env, value, arg) == 1)
		return ;
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
