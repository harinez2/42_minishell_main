#include "main.h"

char	*get_env_from_envlst(t_arg *arg, char *envname)
{
	t_env		*e;

	e = arg->envlst;
	while (e != NULL)
	{
		if (ft_strncmp(e->env, envname, ft_strlen(e->env)) == 0)
			return (e->value);
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
