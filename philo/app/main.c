/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:26:56 by minseobk          #+#    #+#             */
/*   Updated: 2026/06/26 14:49:37 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#define MSG_USAGE "usage: ./philo \
<#_of_philo> <die_ms> <eat_ms> <sleep_ms> [<eat_goal>]"

static void	_print_usage(void)
{
	write(STDERR_FILENO, MSG_USAGE, ft_strlen(MSG_USAGE));
}

int	main(int argc, char **argv)
{
	t_ctx	c;
	t_app	app;

	c = ctx_make();
	if (app_init(&c, &app, argc, argv) != ERROR_OK)
	{
		if (geterr(&c) == ERROR_ARG)
			return (_print_usage(), geterr(&c));
		return (geterr(&c));
	}
	if (app.cond.eat_count == 0)
		return (app_drop(&app), 0);
	if (app_run(&c, &app) != ERROR_OK)
		return (geterr(&c));
	if (app_wait(&c, &app) != ERROR_OK)
		return (geterr(&c));
	return (app_drop(&app), 0);
}
