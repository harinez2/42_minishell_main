#include "main.h"

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

char	*expander_char_env_judge(char *env, t_arg *arg)
{
	t_env	*tmp;
	char	*value;

	tmp = arg->envlst;
	while (tmp->next)
	{
		if (!ft_strncmp(env, tmp->env, ft_strlen(env)))
		{
			value = ft_strdup2(tmp->value, ft_strlen(tmp->value));
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	expander_char_env_cut(char **text, int start, int end, t_arg *arg)
{
	char	*env;
	char	*before;
	char	*after;
	char	*value;
	char	*tmp;

	env = ft_strdup2(&(*text)[start + 1], end - start - 1);
///	write(1,"hello\n",6);
///	printf("-------\n%s\n--------\n", env);
	value = expander_char_env_judge(env, arg);
	if (!value)
	{
		free(env);
		return (0);
	}
	before = ft_strdup2((*text), start);
	after = ft_strdup2(&(*text)[end], ft_strlen(*text) - end);
	tmp = ft_strjoin3(before, value, after);
	free(*text);
	free(before);
	free(after);
	free(value);
	free(env);
	(*text) = tmp;
	return (1);
}

void	expander_char_env_replace(char **text, int *cnt, t_arg *arg)
{
	char	*tmp;
	int		i;

	tmp = *text;
	i = *cnt;
	if (tmp[(*cnt) + 1] == '"')
	{
		(*cnt) += 2;
		return ;
	}
///	write(1,"hello\n",6);
	while (tmp[i])
	{
		if (tmp[i] == '"')
		{
			if (!(expander_char_env_cut(text, *cnt, i, arg)))
				exit (1); /// please fix
			(*cnt) = i + 1;
			break ;
		}
///	write(1,"hello\n",6);
///		printf("%c\n",tmp[i]);
		i++;
	}
	if (i == (int)ft_strlen(*text))
	{
		if (!(expander_char_env_cut(text, *cnt, ft_strlen(*text), arg)))
			exit (1); /// please fix
		(*cnt) = i + 1;
	}
}

void	expander_char_env(char **text, t_arg *arg)
{
	int		cnt;
	int		escape;
	char	*tmp;

	cnt = 0;
	tmp = *text;
	escape = 0;
///		printf("-----\n%s\n-------\n",tmp);
	while (tmp[cnt])
	{
		if (tmp[cnt] == '\'' && escape == 0)
			escape = 1;
		if (tmp[cnt] == '\'' && escape == 1)
			escape = 0;		
		if (tmp[cnt] == '$' && escape != 1)
			expander_char_env_replace(text, &cnt, arg);
		if (tmp[cnt] == '\\')
			cnt ++;
	///	printf("%c\n",tmp[cnt]);
		cnt ++;
	}
}

void	expander_char_quote(char **text)
{
	char	*new;
	int		cnt;
	int		i;
	int		escape;
	int		single_quote;

	new = (char *)malloc(ft_strlen(*text));
	cnt = 0;
	i = 0;
	escape = 0;
	single_quote = 0;
///	write(1,"hello\n",6);
	while ((*text)[cnt])
	{
		if ((*text)[cnt] == '\'')
		{
			single_quote ^= 1;
			cnt ++;
			continue ;
		}
		if ((*text)[cnt] == '\\' && single_quote == 0 && escape == 0)
		{
			escape = 1;
			cnt ++;
			continue ;
		}
		if ((*text)[cnt] == '\"' && escape == 0)
		{
			cnt ++;
			continue ;			
		}
		new[i] = (*text)[cnt];
		i ++;
		cnt ++;
		if (escape == 1)
			escape = 0;
	}
	new[i] = '\0';
	(*text) = new;
}

void	expander_char(char **text, t_arg *arg)
{
	int		cnt;
	char	*tmp;

	cnt = 0;
	tmp = *text;
	expander_char_env(text, arg);
///	printf("%s\n%s\n", arg->cmdlst->param[0], arg->cmdlst->param[1]);
	expander_char_quote(text);
	printf("%s\n%s\n", arg->cmdlst->param[0], arg->cmdlst->param[1]);
}

void	expander_multiple_char(t_arg *arg)
{
	int	cnt;

	cnt = 0;
	while (arg->cmdlst->param[cnt])
	{
		expander_char(&(arg->cmdlst->param[cnt]), arg);
		cnt ++;
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
///	printf("%s\n%s\n", arg->cmdlst->param[0], arg->cmdlst->param[1]);
///	expander_multiple_char(arg);
///	expander_char(&(arg->cmdlst->redir_in));
///	expander_char(&(arg->cmdlst->redir_out));

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
