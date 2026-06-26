/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 00:40:32 by minseobk          #+#    #+#             */
/*   Updated: 2026/05/27 17:43:56 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "def.h"

void	*mem_get(size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
		return (NULL);
	memset(p, 0, size);
	return (p);
}
