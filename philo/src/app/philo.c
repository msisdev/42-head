/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 16:14:06 by minseobk          #+#    #+#             */
/*   Updated: 2026/05/29 18:54:56 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

t_philo	philo_make(const t_cond *cond_ref, t_ms_t *now_ref)
{
	t_philo	p;

	memset(&p, 0, sizeof(t_philo));
	p.cond = *cond_ref;
	p.act = ACT_THINK;
	p.end_at = 0;
	p.die_at = cond_ref->die + 1;
	p.now_ref = now_ref;
	return (p);
}

void	philo_drop(t_philo *p_ref)
{
	(void)p_ref;
}

t_act	philo_get_act(const t_philo *p_ref)
{
	return (p_ref->act);
}

bool	philo_is_dead(t_philo *p_ref)
{
	if (p_ref->die_at <= *p_ref->now_ref)
	{
		p_ref->act = ACT_DIE;
		return (true);
	}
	else
		return (false);
}
