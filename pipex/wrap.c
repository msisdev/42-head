/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 19:50:46 by minseobk          #+#    #+#             */
/*   Updated: 2026/01/01 18:19:36 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	wdup2(t_context *c, t_fd fd, t_fd fd2)
{
	if (dup2(fd, fd2) < 0)
	{
		seterr(c, ERROR_PIPE);
		panic(c);
	}
}

void	wclose(t_context *c, t_fd fd)
{
	if (close(fd) < 0)
	{
		seterr(c, ERROR_CLOSE);
		panic(c);
	}
}

void	wfork(t_context *c, pid_t *pid)
{
	*pid = fork();
	if (*pid < 0)
	{
		seterr(c, ERROR_FORK);
		panic(c);
	}
}

t_fd	wopen(t_context *c, const char *fname, bool is_read)
{
	t_fd	fd;

	if (!c || !fname)
	{
		seterr(c, ERROR_DEBUG);
		panic(c);
	}
	c->fname_ = fname;
	if (is_read)
		fd = open(fname, O_RDONLY);
	else
		fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		seterr(c, ERROR_OPEN);
		panic(c);
	}
	return (fd);
}

void	wwaitpid(t_context *c, pid_t pid, int *stat)
{
	if (waitpid(pid, stat, 0) < 0)
	{
		seterr(c, ERROR_WAIT);
		panic(c);
	}
}
