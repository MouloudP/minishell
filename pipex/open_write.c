/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:32:06 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/23 18:42:06 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	write_fd_to_fd(int src_fd, int dst_fd)
{
	char	buffer[1023];
	int		ret;
	int		pipe_fd[2];

	ret = 1;
	pipe(pipe_fd);
	while (ret > 0)
	{
		ret = read(src_fd, buffer, 1023);
		write(dst_fd, buffer, ret);
		write(pipe_fd[1], buffer, ret);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	write_command_output(char *outfile, int fd_src)
{
	int		fd_outfile;

	if (!outfile)
		return (input_error("parse error near '\\n'", NULL, 0));
	fd_outfile = open(outfile, O_RDWR | O_CREAT, S_IRWXU);
	if (fd_outfile == INVALID_FD)
		return (INVALID_FD);
	close(fd_outfile);
	unlink(outfile);
	fd_outfile = open(outfile, O_RDWR | O_CREAT, S_IRWXU);
	if (fd_outfile == INVALID_FD)
		return (INVALID_FD);
	return (write_fd_to_fd(fd_src, fd_outfile));
}

int	open_output(char *outfile, int append)
{
	int		fd_outfile;
	int		readed;
	char	buffer[1023];

	if (!outfile)
		return (input_error("parse error near '\\n'", NULL, 0));
	fd_outfile = open(outfile, O_RDWR | O_CREAT, S_IRWXU);
	if (fd_outfile == INVALID_FD)
		return (INVALID_FD);
	if (append == 0)
	{
		close(fd_outfile);
		unlink(outfile);
		fd_outfile = open(outfile, O_RDWR | O_CREAT, S_IRWXU);
		if (fd_outfile == INVALID_FD)
			return (INVALID_FD);
	}
	else
	{
		readed = 1023;
		while (readed == 1023)
			readed = read(fd_outfile, buffer, 1023);
	}
	return (fd_outfile);
}

int	print_stdout(int fd)
{
	if (fd > 2)
		close(fd);
	if (dup2(1, fd) == -1)
		return (-3);
	return (0);
}
