#include "main.h"

char	**generate_environ(t_arg *arg)
{
	t_env	*e;
	char	**env;
	int		env_i;

	env = malloc(sizeof(char *) * (count_envlst(arg) + 1));
	if (!env)
		print_perror_exit(errno, "", "", arg);
	env_i = 0;
	e = arg->envlst;
	while (e)
	{
		env[env_i] = ft_strjoin3(e->env, "=", e->value);
		e = e->next;
		env_i++;
	}
	env[env_i] = NULL;
	return (env);
}

void	destroy_environ(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		secure_free(env[i]);
		i++;
	}
	secure_free(env);
}
