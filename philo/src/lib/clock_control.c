/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:45:50 by minseobk          #+#    #+#             */
/*   Updated: 2026/06/03 16:02:19 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

//	sleep until `clk.begin`.
void	clock_ready(t_clock *clk_ref)
{
	t_time	now;
	t_us_d	dur;

	clk_ref->now = 0;
	now = time_get();
	dur = time_dur_us(now, clk_ref->begin);
	if (dur > 0)
		usleep(dur);
}

//	update `clk.now`.
t_ms_t	clock_update(t_clock *clk_ref)
{
	t_time	now_t;
	t_ms_d	now;

	now_t = time_get();
	now = time_dur_ms(clk_ref->begin, now_t);
	clk_ref->now = now;
	return (now);
}

//	sleep until `until` and return `until`.
t_ms_t	clock_sleep_until(t_clock *clk_ref, t_ms_t until)
{
	t_time	now_t;
	t_time	until_t;
	t_us_d	dur;

	if (until <= clk_ref->now)
		return (clk_ref->now);
	now_t = time_get();
	until_t = time_add_ms(clk_ref->begin, until);
	dur = time_dur_us(now_t, until_t);
	if (dur > 0)
		usleep(dur);
	clk_ref->now = until;
	return (until);
}

//	sleep for `d` and return the current time.
t_ms_t	clock_sleep_for(t_clock *clk, t_ms_d d)
{
	t_time	now_t;
	t_time	until_t;
	t_us_d	dur;

	now_t = time_get();
	until_t = time_add_ms(now_t, d);
	dur = time_dur_us(now_t, until_t);
	if (dur > 0)
		usleep(dur);
	clk->now = time_dur_ms(clk->begin, until_t);
	return (clk->now);
}
