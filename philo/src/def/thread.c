/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 18:46:22 by minseobk          #+#    #+#             */
/*   Updated: 2026/05/12 18:49:40 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

t_error	thread_create(t_ctx *c_ref,
	t_thread *th_ref, void *(*f)(void *), void *arg)
{
	if (!th_ref->is_running)
	{
		if (pthread_create(&th_ref->th, NULL, f, arg) != THREAD_CREATE_OK)
			return (seterr(c_ref, ERROR_THREAD));
		th_ref->is_running = true;
	}
	return (ERROR_OK);
}

t_error	thread_join(t_ctx *c_ref, t_thread *th_ref)
{
	if (th_ref->is_running)
	{
		if (pthread_join(th_ref->th, NULL) != THREAD_JOIN_OK)
			return (seterr(c_ref, ERROR_THREAD));
		th_ref->is_running = false;
	}
	return (ERROR_OK);
}
