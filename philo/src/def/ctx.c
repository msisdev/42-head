/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:22:35 by minseobk          #+#    #+#             */
/*   Updated: 2026/05/12 15:53:01 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

t_ctx	ctx_make(void)
{
	t_ctx	c;

	c.err = ERROR_OK;
	return (c);
}

t_error	seterr(t_ctx *c_ref, t_error err)
{
	c_ref->err = err;
	return (err);
}

t_error	geterr(const t_ctx *c_ref)
{
	return (c_ref->err);
}
