/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:03:05 by minseobk          #+#    #+#             */
/*   Updated: 2026/01/01 14:25:38 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	run(t_context *c, const char *cmd)
{
	ctx_resolve(c, cmd);
	if (!c->path)
		panic(c);
	execve(c->path, c->sp, c->envp__);
	panic(c);
}

void	run_file_in(t_context *c, const char *file, const char *cmd)
{
	t_fd	in;

	in = wopen(c, file, true);
	wdup2(c, in, STDIN_FILENO);
	wdup2(c, c->p[P_WR], STDOUT_FILENO);
	wclose(c, in);
	wclose(c, c->p[P_RD]);
	wclose(c, c->p[P_WR]);
	return (run(c, cmd));
}

void	run_file_out(t_context *c, const char *file, const char *cmd)
{
	t_fd	out;

	out = wopen(c, file, false);
	wdup2(c, c->p[P_RD], STDIN_FILENO);
	wdup2(c, out, STDOUT_FILENO);
	wclose(c, out);
	wclose(c, c->p[P_RD]);
	wclose(c, c->p[P_WR]);
	return (run(c, cmd));
}

/**
 *	Example
 *
 *		`./pipex infile "ls -l" "wc -l" outfile
 *
 *		is equivalent to `< infile ls -l | wc -l > outfile`
 *
 *		`./pipex infile "grep a1" "wc -w" outfile
 *
 *		is equivalent to `< infile grep a1 | wc -w > outfile`
 */
int	main(int argc, char *argv[], char *envp[])
{
	t_context	ctx;
	int			stat;
	pid_t		pid1;
	pid_t		pid2;

	if (ctx_init(&ctx, argc, argv, envp) != ERROR_OK)
		panic(&ctx);
	wfork(&ctx, &pid1);
	if (pid1 == 0)
		run_file_in(&ctx, argv[1], argv[2]);
	wfork(&ctx, &pid2);
	if (pid2 == 0)
		run_file_out(&ctx, argv[4], argv[3]);
	wclose(&ctx, ctx.p[P_RD]);
	wclose(&ctx, ctx.p[P_WR]);
	wwaitpid(&ctx, pid1, &stat);
	wwaitpid(&ctx, pid2, &stat);
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	return (EXIT_SUCCESS);
}
