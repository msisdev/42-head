/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:30:41 by minseobk          #+#    #+#             */
/*   Updated: 2025/10/14 14:38:53 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	checks whether c is a 7-bit unsigned char value that fits into the
	ASCII character set.
*/

int	ft_isascii(int c)
{
	return (0 <= c && c <= 127);
}
