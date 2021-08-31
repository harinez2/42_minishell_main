#include "main.h"

void	ft_push_back_list(t_env	**envlst, char *env, char *value)
{
	t_env	*new_env;
	t_env	*head;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		 ; /// please change this
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

void	init_env(t_arg *arg)
{
	int		cnt;
	int		dest;
	char	*env;
	char	*value;

	cnt = 0;
	arg->envlst = NULL;
	while (arg->envp[cnt])
	{
		dest = ft_strchr(arg->envp[cnt], '=');
		env = ft_strdup2(arg->envp[cnt], dest);
		value = ft_strdup2(&(arg->envp[cnt][dest + 1]), ft_strlen(arg->envp[cnt]) - dest);
		ft_push_back_list(&(arg->envlst), env, value);
		cnt ++;
	}
}
