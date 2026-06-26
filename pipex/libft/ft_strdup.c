/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:33:03 by minseobk          #+#    #+#             */
/*   Updated: 2025/10/13 16:05:15 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
RETURN
	a pointer to a new string
	which is a duplicate of the string s.

	Memory for the new string is obtained with malloc(3), and
	can be freed with free(3).
*/

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*d;

	size = ft_strlen(s) + 1;
	d = (char *)malloc(sizeof(char) * size);
	if (d == NULL)
		return (NULL);
	ft_strlcpy(d, s, size);
	return (d);
}
