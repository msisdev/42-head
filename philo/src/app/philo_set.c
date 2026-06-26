/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 13:01:48 by minseobk          #+#    #+#             */
/*   Updated: 2026/05/29 12:43:19 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

t_act	philo_set_or_die(t_philo *p_ref, t_act act)
{
	if (p_ref->act == ACT_DIE)
		return (ACT_DIE);
	if (p_ref->die_at <= *p_ref->now_ref)
	{
		p_ref->act = ACT_DIE;
		return (ACT_DIE);
	}
	if (act == ACT_THINK)
		return (philo_set_think(p_ref));
	if (act == ACT_EAT)
		return (philo_set_eat(p_ref));
	if (act == ACT_SLEEP)
		return (philo_set_sleep(p_ref));
	p_ref->act = act;
	return (act);
}

t_act	philo_set_think(t_philo *p_ref)
{
	p_ref->act = ACT_THINK;
	p_ref->end_at = 0;
	return (ACT_THINK);
}

t_act	philo_set_eat(t_philo *p_ref)
{
	t_ms_t	now;

	now = *p_ref->now_ref;
	p_ref->act = ACT_EAT;
	p_ref->end_at = now + p_ref->cond.eat;
	p_ref->die_at = now + p_ref->cond.die + 1;
	return (ACT_EAT);
}

t_act	philo_set_sleep(t_philo *p_ref)
{
	p_ref->act = ACT_SLEEP;
	p_ref->end_at = *p_ref->now_ref + p_ref->cond.sleep;
	return (ACT_SLEEP);
}
