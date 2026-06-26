/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 23:50:46 by minseobk          #+#    #+#             */
/*   Updated: 2026/06/03 14:32:12 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

t_error	counter_init(t_ctx *c_ref, const t_cond *cond_ref, t_counter *cnt_ref)
{
	memset(cnt_ref, 0, sizeof(t_counter));
	cnt_ref->eat_count = cond_ref->eat_count;
	if (cnt_ref->eat_count == COND_EAT_COUNT_INFINITE)
		return (ERROR_OK);
	cnt_ref->ph_count = cond_ref->ph_count;
	cnt_ref->eat_arr = mem_get(sizeof(int) * cnt_ref->ph_count);
	if (!cnt_ref->eat_arr)
		return (seterr(c_ref, ERROR_INTERNAL));
	return (ERROR_OK);
}

void	counter_drop(t_counter *cnt_ref)
{
	if (cnt_ref->eat_arr)
	{
		free(cnt_ref->eat_arr);
		cnt_ref->eat_arr = NULL;
	}
}

//	return true if all philosophers reached goal
bool	counter_inc(t_counter *cnt_ref, t_phid id)
{
	if (!cnt_ref->eat_arr)
		return (false);
	cnt_ref->eat_arr[id] += 1;
	if (cnt_ref->eat_arr[id] == cnt_ref->eat_count)
		cnt_ref->eat_done_count += 1;
	return (cnt_ref->eat_done_count == cnt_ref->ph_count);
}
