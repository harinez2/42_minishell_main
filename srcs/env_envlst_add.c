#include "main.h"

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

int	concat_envvalue(char *text, int pos, int len, t_arg *arg)
{
	t_env	*tmp;
	char	*env;
	char	*value;
	char	*new_value;

	env = ft_substr(text, 0, pos - 1);
	value = ft_substr(text, pos + 1, len);
	tmp = get_node_from_envlst(arg->shellenvlst, env);
	if (!tmp)
		tmp = get_node_from_envlst(arg->envlst, env);
	if (tmp)
	{
		new_value = ft_strjoin(tmp->value, value);
		secure_free(tmp->value);
		tmp->value = new_value;
		secure_free(env);
		secure_free(value);
		return (1);
	}
	secure_free(env);
	secure_free(value);
	return (0);
}
