/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 18:40:32 by minseobk          #+#    #+#             */
/*   Updated: 2026/05/26 19:07:29 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

t_error	mutex_init(t_ctx *c_ref, t_mutex *mx_ref)
{
	if (!mx_ref->is_init)
	{
		if (pthread_mutex_init(&mx_ref->mx, NULL) != MUTEX_INIT_OK)
			return (seterr(c_ref, ERROR_MUTEX));
		mx_ref->is_init = true;
	}
	return (ERROR_OK);
}

void	mutex_destroy(t_mutex *mx_ref)
{
	if (mx_ref->is_init)
	{
		pthread_mutex_destroy(&mx_ref->mx);
		mx_ref->is_init = false;
	}
}

void	mutex_lock(t_mutex *mx_ref)
{
	if (!mx_ref->is_init)
		return ;
	pthread_mutex_lock(&mx_ref->mx);
}

void	mutex_unlock(t_mutex *mx_ref)
{
	if (!mx_ref->is_init)
		return ;
	pthread_mutex_unlock(&mx_ref->mx);
}
