/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:08:59 by minseobk          #+#    #+#             */
/*   Updated: 2026/06/03 15:10:36 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

inline static t_error	init_fmx_arr(t_ctx *c_ref, t_table *t_ref, int ph_count)
{
	int	i;

	t_ref->fmx_arr = mem_get(sizeof(t_mutex) * ph_count);
	i = 0;
	while (i < ph_count)
	{
		if (mutex_init(c_ref, &t_ref->fmx_arr[i]) != ERROR_OK)
			return (table_drop(t_ref), geterr(c_ref));
		i += 1;
	}
	return (ERROR_OK);
}

t_error	table_init(t_ctx *c_ref, t_table *t_ref, int ph_count)
{
	memset(t_ref, 0, sizeof(t_table));
	t_ref->ph_count = ph_count;
	if (mutex_init(c_ref, &t_ref->mx) != ERROR_OK)
		return (table_drop(t_ref), geterr(c_ref));
	t_ref->f_arr = malloc(sizeof(bool) * ph_count);
	if (!t_ref->f_arr)
		return (table_drop(t_ref), seterr(c_ref, ERROR_INTERNAL));
	memset(t_ref->f_arr, true, sizeof(bool) * ph_count);
	if (init_fmx_arr(c_ref, t_ref, ph_count) != ERROR_OK)
		return (table_drop(t_ref), geterr(c_ref));
	return (ERROR_OK);
}

void	table_drop(t_table *t_ref)
{
	int		i;

	mutex_destroy(&t_ref->mx);
	if (t_ref->f_arr)
		free(t_ref->f_arr);
	if (t_ref->fmx_arr)
	{
		i = 0;
		while (i < t_ref->ph_count)
			mutex_destroy(&t_ref->fmx_arr[i++]);
		free(t_ref->fmx_arr);
	}
}

int	_table_first_index(const t_table *t_ref, t_phid id)
{
	if (id % 2 == 0)
		return (id);
	else
		return ((id + 1) % t_ref->ph_count);
}

int	_table_second_index(const t_table *t_ref, t_phid id)
{
	if (id % 2 == 0)
		return ((id + 1) % t_ref->ph_count);
	else
		return (id);
}
