#ifndef PROTOTYPES_H
# define PROTOTYPES_H

// arg_init_destroy.c
void	init_arg(int argc, char **argv, char **envp, t_arg *arg);
void	update_envpath(t_arg *arg);
void	destroy_arg(t_arg *arg);
// builtin_cd.c
void	builtincmd_cd(t_arg *arg, t_cmd *cmd);
// builtin_echo.c
void	builtincmd_echo(t_arg *arg, t_cmd *cmd);
// builtin_env.c
void	builtincmd_env(t_arg *arg, t_cmd *cmd);
// builtin_export.c
void	builtincmd_export(t_arg *arg, t_cmd *cmd);
// builtin_pwd.c
void	builtincmd_pwd(t_arg *arg, t_cmd *cmd);
// builtin_unset.c
void	builtincmd_unset(t_arg *arg, t_cmd *cmd);
// env_environ.c
char	**generate_environ(t_arg *arg);
void	destroy_environ(char **env);
// env_envlst.c
void	init_envlst(t_arg *arg);
void	push_back_envlst(t_env	**envlst, char *env, char *value, t_arg *arg);
char	*get_env_from_envlst(t_arg *arg, char *envname);
void	delete_env_from_envlst(t_arg *arg, char *envname);
int	count_envlst(t_arg *arg);
void	destroy_envlst(t_arg *arg);
// error.c
void	print_perror(int err_no, char *errcmd, char *argtxt);
void	print_custom_error(t_error_no errcode, char *errcmd, char *argtxt);
void	print_perror_exit(int err_no, char *errcmd, char *argtxt, t_arg *arg);
void	print_custom_error_exit(
			t_error_no errcode, char *errcmd, char *argtxt, t_arg *arg);
// executer.c
int	executer(t_arg *arg);
// executer_builtin_nofork.c
int	run_builtin_nofork(t_arg *arg, t_cmd *c);
// executer_cmdexec.c
void	exec_command(t_cmd *cmd, t_arg *arg);
// executer_util.c
void	dbg_print_cmdstart(t_arg *arg, char *s);
void	dbg_print_cmdend(t_arg *arg, int status);
void	connect_pipe(int unused, int old, int new, t_arg *arg);
void	close_pipe(t_arg *arg, char *who, int fd);
void	ignore_toomuch_redirout(t_arg *arg, t_cmd *c);
// expander.c
void	expander_char(char **text, t_arg *arg);
void	expander(t_arg *arg);
// expander_char_env.c
void	expander_char_env(char **text, t_arg *arg);
// expander_char_quote.c
void	expander_char_quote(char **text);
// lexer.c
int	lexer(t_arg *arg, int token_info[][3]);
// lexer_util.c
int	is_whitespace(char c);
int	is_delim_or_redir(char c);
void	skip_whitespace(char *read, int *i);
void	print_token_type(t_token_type type);
void	print_token_info(int token_info[][3], char *read);
// lib_ft.c
size_t	ft_strlen(const char *str);
void	ft_putstr(char *s, int len);
int	ft_strncmp(char *s1, char *s2, unsigned int n);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
// lib_ft2.c
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);
char	*ft_substr(char const *s, unsigned int start, size_t len);
// lib_ft3.c
ssize_t	ft_strchr(const char *s, int c);
char	*ft_strdup2(const char *s1, ssize_t n);
// lib_ft4.c
char	*ft_searchinstr(const char *s, int c);
// lib_util.c
void	putstr_stderr(char *s);
void	copy_array(t_env *to[], t_env *from[], int len, int offset_to);
void	secure_free(void *p);
// lib_util_dbg.c
void	dbg_print_str(t_arg *arg, char *s);
void	dbg_print_int(t_arg *arg, int i);
void	dbg_print_strint(t_arg *arg, char *s, int i);
// main.c
int	main(int argc, char **argv, char **envp);
// parser.c
int	bnf_piped_commands(t_arg *arg, int token_info[][3], int *i);
int	bnf_separation_op(t_arg *arg, int token_info[][3], int *i);
int	bnf_command_line(t_arg *arg, int token_info[][3], int *i);
int	parser(t_arg *arg, int token_info[][3]);
// parser_bnf_compoundcmd.c
int	bnf_redirection(t_arg *arg, int token_info[][3], int *i, int leftflg);
int	bnf_param_redir(t_arg *arg, int token_info[][3], int *i);
int	bnf_command_elements(t_arg *arg, int token_info[][3], int *i);
int	bnf_simple_command(t_arg *arg, int token_info[][3], int *i);
int	bnf_compoud_command(t_arg *arg, int token_info[][3], int *i);
// parser_bnf_redirection.c
void	bnf_redirection_op(t_arg *arg, int token_info[][3], int *i, int leftflg);
// parser_heredoc.c
char	*heredoc_read(t_arg *arg, char *eof_name);
// signal.c
void	sigint_handler(int signum);
void	set_signal(void);
// struct_add.c
int	cmd_add_redir_filename(t_arg *arg, int inout, char *read, int len);
int	cmd_add_flg(t_arg *arg, t_token_type t, int flg);
int	cmd_add_param(t_arg *arg, char *cmdtxt, int len);
// struct_init_destroy.c
t_cmd	*cmd_create_node_with_param(t_arg *arg, char *cmdtxt, int len);
t_cmd	*cmd_create_node_with_redir(
	t_arg *arg, int inout, char *cmdtxt, int len);
void	cmd_destroy(t_arg *arg);
// struct_lst.c
t_cmd	*cmd_get_last_node(t_cmd *cmd);
// struct_print.c
void	cmd_print(t_cmd *c);

#endif
