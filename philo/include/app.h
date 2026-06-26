/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 17:48:48 by minseobk          #+#    #+#             */
/*   Updated: 2026/06/03 15:11:46 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include "lib.h"
# define COND_EAT_COUNT_INFINITE -1
# define COND_DIE_TOLERANCE 1

typedef enum e_act			t_act;
typedef struct s_board		t_board;
typedef struct s_clock		t_clock;
typedef struct s_cond		t_cond;
typedef struct s_event		t_event;
typedef enum e_fork			t_fork;
typedef struct s_logger		t_logger;
typedef struct s_store		t_store;
typedef struct s_table		t_table;

/* ---------------------------------- */
/* act                                */
/* ---------------------------------- */

typedef enum e_act
{
	ACT_NONE,
	ACT_THINK,
	ACT_GRAB_ONE,
	ACT_EAT,
	ACT_SLEEP,
	ACT_DIE,
}	t_act;

/* ---------------------------------- */
/* cond                               */
/* ---------------------------------- */

typedef struct s_cond
{
	int		ph_count;
	t_ms_d	die;
	t_ms_d	eat;
	t_ms_d	sleep;
	int		eat_count;
}	t_cond;

t_error			cond_parse(t_ctx *c, int argc, char **argv, t_cond *dst);

/* ---------------------------------- */
/* counter                            */
/* ---------------------------------- */

typedef struct s_counter
{
	int		*eat_arr;
	int		ph_count;
	int		eat_count;
	int		eat_done_count;
}	t_counter;

t_error			counter_init(
					t_ctx *c_ref, const t_cond *cond_ref, t_counter *cnt_ref);
void			counter_drop(t_counter *cnt_ref);
bool			counter_inc(t_counter *cnt_ref, t_phid id);

/* ---------------------------------- */
/* event                              */
/* ---------------------------------- */

typedef struct s_event
{
	t_phid			id;
	t_ms_t			at;
	t_act			act;
}	t_event;

t_event			event_make(t_phid id, t_ms_t at, t_act t);
void			event_print_unsafe(t_event e);

/* ---------------------------------- */
/* philo                              */
/* ---------------------------------- */

typedef struct s_philo
{
	t_cond			cond;
	t_act			act;
	t_ms_t			end_at;
	t_ms_t			die_at;
	t_ms_t			*now_ref;
}	t_philo;

t_philo			philo_make(const t_cond *cond_ref, t_ms_t *now_ref);
void			philo_drop(t_philo *p_ref);
bool			philo_is_dead(t_philo *p_ref);
t_act			philo_get_act(const t_philo *p_ref);
t_act			philo_set_or_die(t_philo *p_ref, t_act act);
t_act			philo_set_think(t_philo *p_ref);
t_act			philo_set_eat(t_philo *p_ref);
t_act			philo_set_sleep(t_philo *p_ref);

/* ---------------------------------- */
/* seat                               */
/* ---------------------------------- */

typedef struct s_seat
{
	t_mutex		*mx_ref;
	t_mutex		*fmx1_ref;
	t_mutex		*fmx2_ref;
	bool		*fork1_ref;
	bool		*fork2_ref;
	bool		no_fork;
}	t_seat;

t_seat			seat_make(t_table *tab_ref, t_phid id);
bool			seat_try_grab(t_seat *seat_ref);
void			seat_release(t_seat *seat_ref);

/* ---------------------------------- */
/* store                              */
/* ---------------------------------- */

typedef struct s_store
{
	t_mutex		mx;
	t_error		err;
	bool		is_end;
	t_counter	cnt;
}	t_store;

t_error			store_init(
					t_ctx *c_ref, t_store *s_ref, const t_cond *cond_ref);
void			store_drop(t_store *s_ref);

/* ---------------------------------- */
/* table                              */
/* ---------------------------------- */

typedef struct s_table
{
	t_mutex			mx;
	int				ph_count;
	bool			*f_arr;
	t_mutex			*fmx_arr;
}	t_table;

t_error			table_init(t_ctx *c_ref, t_table *t_ref, int ph_count);
void			table_drop(t_table *t_ref);
int				_table_first_index(const t_table *t_ref, t_phid id);
int				_table_second_index(const t_table *t_ref, t_phid id);

#endif // APP_H
