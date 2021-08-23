#ifndef PROTOTYPES_H
# define PROTOTYPES_H

// builtin_cd.c
void	builtincmd_cd(t_arg *arg, char *read);
// builtin_echo.c
void	builtincmd_echo(t_arg *arg, char *read);
// builtin_env.c
void	builtincmd_env(t_arg *arg);
// builtin_export.c
void	builtincmd_export(t_arg *arg, char **envp);
// builtin_pwd.c
void	builtincmd_pwd(t_arg *arg);
// cmd_exec.c
void	free_param(char **cmd_with_param);
void	exec_command(char *cmd, t_arg *arg);
// cmd_pipe.c
void	pipe_and_runcommand(t_arg *arg, int nestcnt);
// error.c
void	print_error(int errcode, char *txt);
void	error_exit(int errcode, t_arg *arg);
// lib_ft.c
size_t	ft_strlen(const char *str);
void	ft_putchars(char *s);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
// lib_ft2.c
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
// lib_lst.c
void	lst_print(t_cmd *c);
int		lst_addlast(t_arg *arg, int addpoint, char *cmdtxt, int len);
void	lst_destroy(t_arg *arg);
// lib_util.c
void	copy_array(int *to, int *from, int len, int offset_to);
void	secure_free(void *p);
void	init_arg(int argc, char **argv, char **envp, t_arg *arg);
// recogin_executer.c
int		fork_and_runcmd(t_arg *arg);
// recogin_lexer.c
int		get_token(char *read, int *i);
// recogin_lexer_util.c
int		is_whitespace(char c);
int		is_delim_or_redir(char c);
void	skip_whitespace(char *read, int *i);
void	print_token_type(int type);
// recogin_parser.c
void	add_tree(t_arg *arg, int type, char *cmdtxt, int len);
// recogin_runbuiltincmd.c
int		run_builtincmd(char *read, t_arg *arg);

#endif
