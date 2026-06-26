/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:26:24 by minseobk          #+#    #+#             */
/*   Updated: 2026/05/31 17:04:06 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_time	time_get(void)
{
	t_time	t;

	gettimeofday(&t, NULL);
	return (t);
}

t_time	time_add_ms(t_time t, t_ms_d ms)
{
	if (ms >= SEC_TO_MSEC)
	{
		t.tv_sec += ms / SEC_TO_MSEC;
		ms %= SEC_TO_MSEC;
	}
	t.tv_usec += ms * MSEC_TO_USEC;
	if (t.tv_usec >= SEC_TO_USEC)
	{
		t.tv_sec += 1;
		t.tv_usec -= SEC_TO_USEC;
	}
	return (t);
}

t_time	time_add_us(t_time t, t_us_d us)
{
	if (us >= SEC_TO_USEC)
	{
		t.tv_sec += us / SEC_TO_USEC;
		us %= SEC_TO_USEC;
	}
	t.tv_usec += us;
	return (t);
}

int	time_cmp(t_time a, t_time b)
{
	if (a.tv_sec != b.tv_sec)
		return (a.tv_sec < b.tv_sec);
	else
		return (a.tv_usec < b.tv_usec);
}

int	time_cmp_ms(t_time a, t_time b)
{
	if (a.tv_sec != b.tv_sec)
		return (a.tv_sec < b.tv_sec);
	else
		return (a.tv_usec / 1000 < b.tv_usec / 1000);
}
