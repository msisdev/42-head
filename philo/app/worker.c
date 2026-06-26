/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:03:39 by minseobk          #+#    #+#             */
/*   Updated: 2026/06/02 18:02:09 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_error	worker_init(t_ctx *c_ref, t_app *a_ref, t_phid id, t_worker *w_ref)
{
	memset(w_ref, 0, sizeof(t_worker));
	w_ref->id = id;
	w_ref->cond = a_ref->cond;
	w_ref->clk = clock_clone(&a_ref->clk);
	w_ref->phi = philo_make(&w_ref->cond, &w_ref->clk.now);
	w_ref->seat = seat_make(&a_ref->tab, id);
	w_ref->sto_ref = &a_ref->sto;
	if (thread_create(c_ref, &w_ref->th, _worker_main, w_ref) != ERROR_OK)
		return (worker_drop(w_ref), geterr(c_ref));
	return (ERROR_OK);
}

void	worker_drop(t_worker *w_ref)
{
	(void)w_ref;
}
