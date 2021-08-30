#ifndef PROTOTYPES_H
# define PROTOTYPES_H

// arg_init_destroy.c
void			init_arg(int argc, char **argv, char **envp, t_arg *arg);
void			update_envpath(t_arg *arg);
void			destroy_arg(t_arg *arg);
// builtin_cd.c
void			builtincmd_cd(t_arg *arg, t_cmd *cmd);
// builtin_echo.c
void			builtincmd_echo(t_arg *arg, t_cmd *cmd);
// builtin_env.c
void			builtincmd_env(t_arg *arg, t_cmd *cmd);
// builtin_export.c
void			builtincmd_export(t_arg *arg, t_cmd *cmd, char **envp);
// builtin_pwd.c
void			builtincmd_pwd(t_arg *arg, t_cmd *cmd);
// error.c
void			print_error(int errcode, char *txt);
void			error_exit(int errcode, t_arg *arg);
// executer.c
int				executer(t_arg *arg);
// executer_cmdexec.c
void			free_param(char **cmd_with_param);
void			exec_command(t_cmd *cmd, t_arg *arg);
// executer_util.c
void			dbg_print_cmdstart(t_arg *arg, char *s);
void			dbg_print_cmdend(t_arg *arg, int status);
void			close_pipe(t_arg *arg, char *who, int fd);
void			check_and_exit_program(t_arg *arg, t_cmd *c);
// lexer.c
int				lexer(t_arg *arg, int token_info[][3]);
// lexer_util.c
int				is_whitespace(char c);
int				is_delim_or_redir(char c);
void			skip_whitespace(char *read, int *i);
void			print_token_type(t_token_type type);
void			print_token_info(int token_info[][3], char *read);
// lib_ft.c
size_t			ft_strlen(const char *str);
void			ft_putstr(char *s, int len);
int				ft_strncmp(char *s1, char *s2, unsigned int n);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
// lib_ft2.c
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin3(char const *s1, char const *s2, char const *s3);
char			*ft_substr(char const *s, unsigned int start, size_t len);
// lib_util.c
void			dbg_print_str(t_arg *arg, char *s);
void			dbg_print_int(t_arg *arg, int i);
void			dbg_print_strint(t_arg *arg, char *s, int i);
void			copy_array(int *to, int *from, int len, int offset_to);
void			secure_free(void *p);
// parser.c
int				bnf_piped_commands(t_arg *arg, int token_info[][3], int *i);
int				bnf_separation_op(t_arg *arg, int token_info[][3], int *i);
int				bnf_command_line(t_arg *arg, int token_info[][3], int *i);
int				parser(t_arg *arg, int token_info[][3]);
// parser_bnf_compoundcmd.c
int				bnf_redirection(t_arg *arg, int token_info[][3], int *i, int leftflg);
int				bnf_param_redir(t_arg *arg, int token_info[][3], int *i);
int				bnf_command_elements(t_arg *arg, int token_info[][3], int *i);
int				bnf_simple_command(t_arg *arg, int token_info[][3], int *i);
int				bnf_compoud_command(t_arg *arg, int token_info[][3], int *i);
// parser_bnf_redirection.c
void			bnf_redirection_op(t_arg *arg, int token_info[][3], int *i, int leftflg);
// parser_heredoc.c
char			*heredoc_read(t_arg *arg, char *eof_name);
// recogin_expander.c
void			expander(t_arg *arg);
// struct_add.c
int				cmd_add_redir_filename(t_arg *arg, int inout,
					char *read, int len);
int				cmd_add_flg(t_arg *arg, t_token_type t, int flg);
int				cmd_add_param(t_arg *arg, char *cmdtxt, int len);
// struct_init_destroy.c
t_cmd			*cmd_create_node_with_param(
					t_arg *arg, char *cmdtxt, int len);
t_cmd			*cmd_create_node_with_redir(
					t_arg *arg, int inout, char *cmdtxt, int len);
void			cmd_destroy(t_arg *arg);
// struct_lst.c
t_cmd			*cmd_get_last_node(t_cmd *cmd);
// struct_print.c
void			cmd_print(t_cmd *c);

#endif
