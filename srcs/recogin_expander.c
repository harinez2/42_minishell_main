#include "main.h"

void	expander_char(char **text)
{
	int		cnt;
	char	*tmp;

	cnt = 0;
	tmp = *text;
	while(tmp[cnt])
	{

		cnt ++;
	}
}

void	expander_multiple_char(t_arg *arg)
{
	int	cnt;

	cnt = 0;
	while (arg->cmdlst->param[cnt])
	{
		expander_char(&(arg->cmdlst->param[cnt]));
		cnt ++;
	}
}

ssize_t	ft_strchr(const char *s, int c)
{
	ssize_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (i);
}

static char	*ft_strdup2(const char *s1, ssize_t n)
{
	ssize_t	i;
	char	*p;

	p = (char *)malloc(sizeof(char) * (n + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	ft_push_back_list(t_env	**envlst, char *env, char *value)
{
	t_env	*new_env;
	t_env	*head;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		exit (1); /// please change this
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
/*	while (arg->envlst->next != NULL)
	{
		printf("%s  |  %s\n", arg->envlst->env, arg->envlst->value);
		arg->envlst = arg->envlst->next;
	}*/
}

void	expander(t_arg *arg)
{
	init_env(arg);
	expander_multiple_char(arg);

/*
    extern char **environ;
    char **env = environ;

    while(*env) {
        const char *val;

        val = *env;
        if (val) {
            printf("%s\n", val);
        }
		env++;
	}
	const char *value;
	value = getenv("PWD");
	printf("-----------\n%s\n------------\n", value);*/
}
