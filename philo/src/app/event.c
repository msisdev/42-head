/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 17:12:17 by minseobk          #+#    #+#             */
/*   Updated: 2026/06/03 15:11:53 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"
#include <stdio.h>
#include <stdlib.h>

t_event	event_make(t_phid id, t_ms_t at, t_act act)
{
	t_event	e;

	e.id = id;
	e.at = at;
	e.act = act;
	return (e);
}

void	event_print_unsafe(t_event e)
{
	e.id += 1;
	if (e.act == ACT_NONE)
		printf("%d %d debug\n", e.at, e.id);
	else if (e.act == ACT_GRAB_ONE)
		printf("%d %d has taken a fork\n", e.at, e.id);
	else if (e.act == ACT_EAT)
		printf("%d %d is eating\n", e.at, e.id);
	else if (e.act == ACT_SLEEP)
		printf("%d %d is sleeping\n", e.at, e.id);
	else if (e.act == ACT_THINK)
		printf("%d %d is thinking\n", e.at, e.id);
	else if (e.act == ACT_DIE)
		printf("%d %d died\n", e.at, e.id);
}
