/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:34:26 by minseobk          #+#    #+#             */
/*   Updated: 2026/06/03 14:38:11 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

t_seat	seat_make( t_table *tab_ref, t_phid id)
{
	t_seat	s;

	s.mx_ref = &tab_ref->mx;
	s.fmx1_ref = &tab_ref->fmx_arr[_table_first_index(tab_ref, id)];
	s.fmx2_ref = &tab_ref->fmx_arr[_table_second_index(tab_ref, id)];
	s.fork1_ref = &tab_ref->f_arr[_table_first_index(tab_ref, id)];
	s.fork2_ref = &tab_ref->f_arr[_table_second_index(tab_ref, id)];
	s.no_fork = tab_ref->ph_count <= 1;
	return (s);
}

bool	seat_try_grab(t_seat *s)
{
	bool	ok;

	if (s->no_fork)
		return (false);
	ok = false;
	mutex_lock(s->mx_ref);
	if (*s->fork1_ref && *s->fork2_ref)
	{
		*s->fork1_ref = false;
		*s->fork2_ref = false;
		ok = true;
	}
	mutex_unlock(s->mx_ref);
	if (ok)
	{
		mutex_lock(s->fmx1_ref);
		mutex_lock(s->fmx2_ref);
	}
	return (ok);
}

void	seat_release(t_seat *s)
{
	mutex_unlock(s->fmx1_ref);
	mutex_unlock(s->fmx2_ref);
	mutex_lock(s->mx_ref);
	{
		*s->fork1_ref = true;
		*s->fork2_ref = true;
	}
	mutex_unlock(s->mx_ref);
}
