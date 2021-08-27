#include "main.h"

void	expander_char(t_arg *arg, int option)
{
	int	cnt;

	cnt = 0;
	while(arg->envp[cnt])
	{
///		printf("%s\n%d\n", arg->envp[cnt], cnt);

		cnt ++;
	}
	(void)option;
}

void	expander_multiple_char(t_arg *arg)
{
	int	cnt;
	
	cnt = 0;
	while (arg->cmdlst->param[cnt])
	{
		expander_char(arg, cnt);
		cnt ++;
	}
}

void	expander(t_arg *arg)
{
	expander_multiple_char(arg);

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
	printf("-----------\n%s\n------------\n", value);
}
