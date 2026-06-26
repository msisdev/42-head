/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:29:01 by minseobk          #+#    #+#             */
/*   Updated: 2025/10/05 13:45:20 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == ' '
		|| c == '\f'
		|| c == '\n'
		|| c == '\r'
		|| c == '\t'
		|| c == '\v');
}

static long	read_nums(const char *p)
{
	long	n;

	n = 0;
	while ('0' <= *p && *p <= '9')
	{
		n *= 10;
		n += *p - '0';
		p++;
	}
	return (n);
}

int	ft_atoi(const char *nptr)
{
	int		sign;

	sign = 1;
	while (*nptr && ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	return (sign * read_nums(nptr));
}
