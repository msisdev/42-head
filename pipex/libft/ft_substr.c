/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:10:44 by minseobk          #+#    #+#             */
/*   Updated: 2025/11/21 20:21:05 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	min_size_t(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

/*
PARAMETERS
	s		The original string from which to create the substring.
	start	The starting index of the substring within ’s’.
	len		The maximum length of the substring.
*/
char	*ft_substr(
	char const *s,
	unsigned int start,
	size_t len)
{
	size_t	slen;
	size_t	dlen;
	char	*d;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		dlen = 0;
	else
		dlen = min_size_t(slen - start, len);
	d = (char *)malloc(sizeof(char) * (dlen + 1));
	if (d == NULL)
		return (NULL);
	ft_strlcpy(d, s + min_size_t(slen, start), dlen + 1);
	return (d);
}
