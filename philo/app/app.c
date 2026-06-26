/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:29:23 by minseobk          #+#    #+#             */
/*   Updated: 2026/06/03 15:59:58 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

inline static t_error	_init_w_arr(t_ctx *c_ref, t_app *a_ref)
{
	int	i;

	a_ref->w_arr = mem_get(sizeof(t_worker) * a_ref->ph_count);
	if (!a_ref->w_arr)
		return (seterr(c_ref, ERROR_INTERNAL));
	i = 0;
	while (i < a_ref->ph_count)
	{
		if (worker_init(c_ref, a_ref, i, &a_ref->w_arr[i]) != ERROR_OK)
			return (geterr(c_ref));
		i += 1;
	}
	return (ERROR_OK);
}

t_error	app_init(t_ctx *c_ref, t_app *a_ref, int argc, char **argv)
{
	memset(a_ref, 0, sizeof(t_app));
	if (cond_parse(c_ref, argc, argv, &a_ref->cond) != ERROR_OK)
		return (app_drop(a_ref), geterr(c_ref));
	a_ref->ph_count = a_ref->cond.ph_count;
	a_ref->clk = clock_make(a_ref->ph_count * 10);
	if (table_init(c_ref, &a_ref->tab, a_ref->ph_count) != ERROR_OK
		|| store_init(c_ref, &a_ref->sto, &a_ref->cond) != ERROR_OK)
		return (app_drop(a_ref), geterr(c_ref));
	if (a_ref->cond.eat_count == 0)
		return (ERROR_OK);
	if (_init_w_arr(c_ref, a_ref) != ERROR_OK)
		return (app_drop(a_ref), geterr(c_ref));
	return (ERROR_OK);
}

void	app_drop(t_app *a_ref)
{
	int	i;

	table_drop(&a_ref->tab);
	store_drop(&a_ref->sto);
	if (a_ref->w_arr)
	{
		i = 0;
		while (i < a_ref->ph_count)
		{
			worker_drop(&a_ref->w_arr[i]);
			i += 1;
		}
		free(a_ref->w_arr);
	}
}

t_error	app_wait(t_ctx *c_ref, t_app *a_ref)
{
	int	i;

	if (!a_ref->w_arr)
		return (ERROR_OK);
	i = 0;
	while (i < a_ref->ph_count)
	{
		if (thread_join(c_ref, &a_ref->w_arr[i].th) != ERROR_OK)
			return (geterr(c_ref));
		i += 1;
	}
	return (ERROR_OK);
}
