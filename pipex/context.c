/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:43:33 by minseobk          #+#    #+#             */
/*   Updated: 2026/01/01 14:21:40 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_error	ctx_init(t_context *ctx, int argc, char *argv[], char *envp[])
{
	ctx->app__ = NULL;
	ctx->envp__ = NULL;
	ctx->p[0] = -1;
	ctx->p[1] = -1;
	ctx->path = NULL;
	ctx->paths = NULL;
	ctx->fname_ = NULL;
	ctx->cmd_ = NULL;
	ctx->sp = NULL;
	ctx->err = ERROR_OK;
	if (!ctx || !argv || !envp)
		return (seterr(ctx, ERROR_DEBUG));
	if (argc != 5)
		return (seterr(ctx, ERROR_ARG));
	ctx->app__ = argv[0];
	ctx->envp__ = envp;
	if (pipe(ctx->p) < 0)
		return (seterr(ctx, ERROR_PIPE));
	return (ERROR_OK);
}

t_error	ctx_resolve(t_context *ctx, const char *name)
{
	if (ctx->paths)
		free_double(ctx->paths);
	ctx->err = set_paths(&(ctx->paths), ctx->envp__);
	if (ctx->err != ERROR_OK)
		return (ctx_del(ctx), ctx->err);
	if (ctx->sp)
		free_double(ctx->sp);
	ctx->sp = ft_split(name, ' ');
	if (!ctx->sp)
	{
		ctx->err = ERROR_INTERNAL;
		return (ctx_del(ctx), ERROR_INTERNAL);
	}
	if (ctx->path)
		free(ctx->path);
	ctx->err = resolve_path(ctx->paths, ctx->sp[0], &(ctx->path));
	return (ctx->err);
}

void	ctx_del(t_context *ctx)
{
	if (!ctx)
		return ;
	if (ctx->path)
		free(ctx->path);
	ctx->path = NULL;
	if (ctx->paths)
		free_double(ctx->paths);
	ctx->paths = NULL;
	ctx->cmd_ = NULL;
	if (ctx->sp)
		free_double(ctx->sp);
	ctx->sp = NULL;
}

void	panic(t_context *ctx)
{
	puterr(*ctx);
	ctx_del(ctx);
	exit(maperr(ctx->err));
}
