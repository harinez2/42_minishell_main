/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:42:01 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/20 17:09:00 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	heredoc_readline(int fd, char *eof_name)
{
	char	*read;

	while (1)
	{
		read = readline("> ");
		if (read == NULL)
			break ;
		if (ft_strncmp(read, eof_name, ft_strlen(eof_name)) == 0)
			break ;
		write(fd, read, ft_strlen(read));
		write(fd, "\n", 1);
		secure_free(read);
	}
	secure_free(read);
	return (0);
}

static int	open_available_tempfile(t_arg *arg, char *outfilepath)
{
	int			fd;
	int			i;
	struct stat	st;

	ft_strlcpy(outfilepath, "./heredoc", HEREDOC_FILENAME_LEN - 4);
	fd = -1;
	i = -1;
	while (fd == -1 && ++i < MAX_RETRY_HEREDOC)
	{
		outfilepath[9] = i / 100 + '0';
		outfilepath[10] = i % 100 - i % 10 + '0';
		outfilepath[11] = i % 10 + '0';
		outfilepath[12] = '\0';
		if (stat(outfilepath, &st) == 0)
			continue ;
		fd = open(outfilepath, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	}
	if (arg->dbg)
		printf("    heredoc filename:%s\n", outfilepath);
	return (fd);
}

char	*heredoc_read(t_arg *arg, char *eof_name)
{
	char		*outfilepath;
	int			fd;

	outfilepath = malloc(sizeof(char) * HEREDOC_FILENAME_LEN);
	if (!outfilepath)
		print_perror_exit(errno, NULL, NULL, arg);
	fd = open_available_tempfile(arg, outfilepath);
	if (fd == -1)
	{
		secure_free(outfilepath);
		print_custom_error_exit(ERR_HEREDOC, NULL, NULL, arg);
	}
	heredoc_readline(fd, eof_name);
	close(fd);
	return (outfilepath);
}
