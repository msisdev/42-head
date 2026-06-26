/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 17:12:39 by minseobk          #+#    #+#             */
/*   Updated: 2026/06/03 16:01:56 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

inline static void	_think(t_worker *w_ref, bool *is_end)
{
	while (!*is_end && !seat_try_grab(&w_ref->seat))
	{
		clock_update(&w_ref->clk);
		if (philo_is_dead(&w_ref->phi))
			*is_end = true;
	}
	_worker_update_eat(w_ref, is_end);
}

inline static void	_eat(t_worker *w_ref, bool *is_end)
{
	while (clock_sleep_for(&w_ref->clk, 1) <= w_ref->phi.end_at)
	{
		if (philo_is_dead(&w_ref->phi))
		{
			*is_end = true;
			break ;
		}
	}
	seat_release(&w_ref->seat);
	_worker_update_sleep(w_ref, is_end);
}

inline static void	_sleep(t_worker *w_ref, bool *is_end)
{
	t_ms_d	delay;

	while (clock_sleep_for(&w_ref->clk, 1) <= w_ref->phi.end_at)
	{
		if (philo_is_dead(&w_ref->phi))
		{
			*is_end = true;
			break ;
		}
	}
	_worker_update_think(w_ref, is_end);
	if (w_ref->cond.ph_count % 2 == 1)
	{
		delay = w_ref->cond.eat * 2 - w_ref->cond.sleep;
		if (delay > 0)
			clock_sleep_for(&w_ref->clk, delay);
	}
}

inline static void	_routine(t_worker *w_ref, bool *is_end)
{
	_think(w_ref, is_end);
	if (*is_end)
		return ;
	_eat(w_ref, is_end);
	if (*is_end)
		return ;
	_sleep(w_ref, is_end);
	if (*is_end)
		return ;
}

void	*_worker_main(void *arg)
{
	t_worker	*w_ref;
	bool		is_end;

	w_ref = (t_worker *)arg;
	is_end = false;
	clock_ready(&w_ref->clk);
	if (w_ref->cond.ph_count > 1 && w_ref->id % 2 == 1)
		clock_sleep_for(&w_ref->clk, w_ref->cond.eat);
	while (!is_end)
		_routine(w_ref, &is_end);
	return (NULL);
}
