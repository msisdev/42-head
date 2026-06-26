/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cond.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:53:25 by minseobk          #+#    #+#             */
/*   Updated: 2026/06/03 15:10:17 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"
#include <limits.h>

inline static bool	is_digit(char c)
{
	return ('0' <= c && c <= '9');
}

inline static t_error	ft_atoi(t_ctx *c, const char *s, int *dst)
{
	long	n;

	n = 0;
	if (!*s)
		return (seterr(c, ERROR_ARG));
	while (*s)
	{
		if (!is_digit(*s))
			return (seterr(c, ERROR_ARG));
		n = n * 10 + *s - '0';
		if (n > INT_MAX)
			return (seterr(c, ERROR_ARG));
		s++;
	}
	*dst = n;
	return (ERROR_OK);
}

inline static bool	cond_is_valid(t_cond *cond_ref)
{
	return (cond_ref->ph_count > 0
		&& cond_ref->die > 0
		&& cond_ref->eat > 0
		&& cond_ref->sleep > 0
		&& (cond_ref->eat_count == COND_EAT_COUNT_INFINITE
			|| cond_ref->eat_count >= 0));
}

/**
 *	ARGUMENTS
 *
 *		1. `number_of_philosophers`
 *		2. `time_to_die`
 *		3. `time_to_eat`
 *		4. `time_to_sleep`
 *		5. `[number_of_times_each_philosopher_must_eat]`
 */
t_error	cond_parse(t_ctx *c, int argc, char **argv, t_cond *dst)
{
	if (argc != 5 && argc != 6)
		return (seterr(c, ERROR_ARG));
	if (ft_atoi(c, argv[1], &dst->ph_count) != ERROR_OK)
		return (geterr(c));
	if (ft_atoi(c, argv[2], &dst->die) != ERROR_OK)
		return (geterr(c));
	if (ft_atoi(c, argv[3], &dst->eat) != ERROR_OK)
		return (geterr(c));
	if (ft_atoi(c, argv[4], &dst->sleep) != ERROR_OK)
		return (geterr(c));
	if (argc == 6)
	{
		if (ft_atoi(c, argv[5], &dst->eat_count) != ERROR_OK)
			return (geterr(c));
	}
	else
	{
		dst->eat_count = COND_EAT_COUNT_INFINITE;
	}
	if (!cond_is_valid(dst))
		return (seterr(c, ERROR_ARG));
	return (ERROR_OK);
}
