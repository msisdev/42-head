/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 17:05:35 by minseobk          #+#    #+#             */
/*   Updated: 2026/06/03 16:01:18 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	_worker_update_die(t_worker *w_ref, bool *is_end)
{
	*is_end = true;
	mutex_lock(&w_ref->sto_ref->mx);
	if (!w_ref->sto_ref->is_end)
	{
		w_ref->sto_ref->is_end = true;
		event_print_unsafe(event_make(w_ref->id, w_ref->clk.now, ACT_DIE));
	}
	mutex_unlock(&w_ref->sto_ref->mx);
}

void	_worker_update_think(t_worker *w_ref, bool *is_end)
{
	if (*is_end || philo_set_or_die(&w_ref->phi, ACT_THINK) == ACT_DIE)
	{
		_worker_update_die(w_ref, is_end);
		return ;
	}
	mutex_lock(&w_ref->sto_ref->mx);
	if (w_ref->sto_ref->is_end)
		*is_end = true;
	else
		event_print_unsafe(event_make(w_ref->id, w_ref->clk.now, ACT_THINK));
	mutex_unlock(&w_ref->sto_ref->mx);
}

void	_worker_update_eat(t_worker *w_ref, bool *is_end)
{
	if (*is_end || philo_set_or_die(&w_ref->phi, ACT_EAT) == ACT_DIE)
	{
		_worker_update_die(w_ref, is_end);
		return ;
	}
	mutex_lock(&w_ref->sto_ref->mx);
	if (w_ref->sto_ref->is_end)
		*is_end = true;
	else
	{
		event_print_unsafe(event_make(w_ref->id, w_ref->clk.now, ACT_GRAB_ONE));
		event_print_unsafe(event_make(w_ref->id, w_ref->clk.now, ACT_GRAB_ONE));
		event_print_unsafe(event_make(w_ref->id, w_ref->clk.now, ACT_EAT));
	}
	mutex_unlock(&w_ref->sto_ref->mx);
}

void	_worker_update_sleep(t_worker *w_ref, bool *is_end)
{
	if (*is_end || philo_set_or_die(&w_ref->phi, ACT_SLEEP) == ACT_DIE)
	{
		_worker_update_die(w_ref, is_end);
		return ;
	}
	mutex_lock(&w_ref->sto_ref->mx);
	{
		if (w_ref->sto_ref->is_end)
			*is_end = true;
		else if (counter_inc(&w_ref->sto_ref->cnt, w_ref->id))
		{
			*is_end = true;
			w_ref->sto_ref->is_end = true;
		}
		else
			event_print_unsafe(
				event_make(w_ref->id, w_ref->clk.now, ACT_SLEEP));
	}
	mutex_unlock(&w_ref->sto_ref->mx);
}
