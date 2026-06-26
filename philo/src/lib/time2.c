/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:19:36 by minseobk          #+#    #+#             */
/*   Updated: 2026/06/02 16:15:01 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_ms_d	time_dur_ms(t_time from, t_time to)
{
	if (from.tv_sec > to.tv_sec
		|| (from.tv_sec == to.tv_sec && from.tv_usec >= to.tv_usec))
		return (0);
	return ((to.tv_sec - from.tv_sec) * SEC_TO_MSEC
		+ (to.tv_usec - from.tv_usec) / MSEC_TO_USEC);
}

t_us_d	time_dur_us(t_time from, t_time to)
{
	if (from.tv_sec > to.tv_sec
		|| (from.tv_sec == to.tv_sec && from.tv_usec >= to.tv_usec))
		return (0);
	return ((to.tv_sec - from.tv_sec) * SEC_TO_USEC
		+ (to.tv_usec - from.tv_usec));
}

t_ms_t	time_now_ms(t_time begin)
{
	return (time_dur_ms(begin, time_get()));
}
