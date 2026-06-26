/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:32:25 by minseobk          #+#    #+#             */
/*   Updated: 2025/10/16 13:13:12 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
erases the data in the n bytes of the memory
	starting at the location pointed to by s,
	by writing zeros (bytes containing '\0') to that
	area.
*/

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
