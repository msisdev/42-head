/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:24:48 by minseobk          #+#    #+#             */
/*   Updated: 2026/05/31 17:04:06 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

t_clock	clock_make(t_ms_d delay)
{
	t_clock	clk;
	t_time	now;

	now = time_get();
	if (delay > 0)
	{
		clk.begin = time_add_ms(now, delay);
		clk.now = -1;
	}
	else
	{
		clk.begin = now;
		clk.now = 0;
	}
	return (clk);
}

t_clock	clock_clone(const t_clock *clk_ref)
{
	t_clock	copy;

	copy.begin = clk_ref->begin;
	copy.now = clk_ref->now;
	return (copy);
}

t_ms_t	clock_now(const t_clock *clk_ref)
{
	return (clk_ref->now);
}

bool	clock_is_progressed(t_clock *clk_ref)
{
	return (clk_ref->now < clock_update(clk_ref));
}
