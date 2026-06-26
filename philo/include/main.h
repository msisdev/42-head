/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:03:12 by minseobk          #+#    #+#             */
/*   Updated: 2026/06/02 17:06:36 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>
# include "app.h"

typedef struct s_app	t_app;
typedef struct s_worker	t_worker;

/* ---------------------------------- */
/* app                                */
/* ---------------------------------- */

typedef struct s_app
{
	t_cond		cond;
	int			ph_count;
	t_clock		clk;
	t_table		tab;
	t_store		sto;
	t_worker	*w_arr;
}	t_app;

t_error			app_init(t_ctx *c_ref, t_app *a_ref, int argc, char **argv);
void			app_drop(t_app *a_ref);
t_error			app_wait(t_ctx *c_ref, t_app *a_ref);
t_error			app_run(t_ctx *c_ref, t_app *a_ref);

/* ---------------------------------- */
/* worker                             */
/* ---------------------------------- */

typedef struct s_worker
{
	t_phid		id;
	t_cond		cond;
	t_clock		clk;
	t_philo		phi;
	t_seat		seat;
	t_store		*sto_ref;
	t_thread	th;
}	t_worker;

t_error			worker_init(t_ctx *c_ref,
					t_app *a_ref, t_phid id, t_worker *w_ref);
void			worker_drop(t_worker *w_ref);
void			*_worker_main(void *arg);
t_error			_worker_main_loop(t_ctx *c_ref, t_worker *w_ref);
void			_worker_update_die(t_worker *w_ref, bool *is_end);
void			_worker_update_think(t_worker *w_ref, bool *is_end);
void			_worker_update_eat(t_worker *w_ref, bool *is_end);
void			_worker_update_sleep(t_worker *w_ref, bool *is_end);

#endif // MAIN_H
