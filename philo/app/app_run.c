/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:50:04 by minseobk          #+#    #+#             */
/*   Updated: 2026/06/02 18:02:03 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_error	app_run(t_ctx *c_ref, t_app *a_ref)
{
	bool	is_end;

	(void)c_ref;
	is_end = false;
	clock_ready(&a_ref->clk);
	while (!is_end)
	{
		mutex_lock(&a_ref->sto.mx);
		is_end = a_ref->sto.is_end;
		mutex_unlock(&a_ref->sto.mx);
		usleep(1000);
	}
	return (ERROR_OK);
}
