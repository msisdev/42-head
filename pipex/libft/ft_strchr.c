/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:33:02 by minseobk          #+#    #+#             */
/*   Updated: 2025/10/28 15:03:26 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
RETURN
	a pointer to the first occurrence of the
	character c in the string s.

	return a pointer to the matched character
	or NULL if the character is not found.
	
	The terminating null byte is considered part of the string,
	so that if c is specified as '\0', these functions
	return a pointer to the terminator.
*/

char	*ft_strchr(const char *s, int c)
{
	if ((char)c == '\0')
		return (ft_memchr(s + ft_strlen(s), c, 1));
	return (ft_memchr(s, c, ft_strlen(s)));
}
