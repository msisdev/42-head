/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 01:33:12 by minseobk          #+#    #+#             */
/*   Updated: 2026/05/31 21:27:33 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

t_error	store_init(t_ctx *c_ref, t_store *s_ref, const t_cond *cond_ref)
{
	s_ref->err = ERROR_OK;
	s_ref->is_end = false;
	if (cond_ref->eat_count == 0)
		s_ref->is_end = true;
	if (counter_init(c_ref, cond_ref, &s_ref->cnt) != ERROR_OK)
		return (geterr(c_ref));
	if (mutex_init(c_ref, &s_ref->mx) != ERROR_OK)
		return (geterr(c_ref));
	return (ERROR_OK);
}

void	store_drop(t_store *s_ref)
{
	counter_drop(&s_ref->cnt);
	mutex_destroy(&s_ref->mx);
}
