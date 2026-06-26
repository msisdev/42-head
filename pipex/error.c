/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:32:26 by minseobk          #+#    #+#             */
/*   Updated: 2026/01/01 18:20:32 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	*map_err_msg(t_error err)
{
	if (err == ERROR_DEBUG)
		return (MSG_DEBUG);
	if (err == ERROR_ARG)
		return (MSG_ARG);
	if (err == ERROR_NOT_EXEC)
		return (MSG_NOT_EXEC);
	if (err == ERROR_NOT_FOUND)
		return (MSG_NOT_FOUND);
	return (strerror(errno));
}

static void	puterr_fmt(t_error err, const char *app, const char *name)
{
	ft_putstr_fd((char *)app, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(map_err_msg(err), STDERR_FILENO);
	if (name)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd((char *)name, STDERR_FILENO);
	}
	else
		ft_putchar_fd('\n', STDERR_FILENO);
}

void	puterr(t_context c)
{
	if (c.err == ERROR_DEBUG || c.err == ERROR_ARG)
		return (puterr_fmt(c.err, c.app__, NULL));
	if (c.err == ERROR_OPEN)
		return (puterr_fmt(c.err, c.app__, c.fname_));
	if (c.err == ERROR_NOT_EXEC || c.err == ERROR_NOT_FOUND)
		return (puterr_fmt(c.err, c.app__, c.sp[0]));
	perror(c.app__);
}

t_error	seterr(t_context *ctx, t_error err)
{
	ctx->err = err;
	return (err);
}

int	maperr(t_error err)
{
	if (err == ERROR_NOT_EXEC || err == ERROR_NOT_FOUND)
		return (err);
	return (EXIT_FAILURE);
}
