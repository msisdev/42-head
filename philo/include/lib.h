/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 15:51:10 by minseobk          #+#    #+#             */
/*   Updated: 2026/06/26 14:45:06 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H
# include <stdbool.h>
# include <string.h>
# include "def.h"

typedef struct s_clock		t_clock;

/* ---------------------------------- */
/* clock                              */
/* ---------------------------------- */

typedef struct s_clock
{
	t_time	begin;
	t_ms_t	now;
}	t_clock;

t_clock			clock_make(t_ms_d delay);
t_clock			clock_clone(const t_clock *clk_ref);
void			clock_ready(t_clock *clk_ref);
t_ms_t			clock_now(const t_clock *clk_ref);
t_ms_t			clock_update(t_clock *clk_ref);
t_ms_t			clock_sleep_until(t_clock *clk_ref, t_ms_t t);
t_ms_t			clock_sleep_for(t_clock *clk_ref, t_ms_d d);

/* ---------------------------------- */
/* time                               */
/* ---------------------------------- */

t_time			time_get(void);
t_time			time_add_ms(t_time t, t_ms_d ms);
t_time			time_add_us(t_time t, t_us_d us);
int				time_cmp(t_time a, t_time b);
int				time_cmp_ms(t_time a, t_time b);
t_ms_d			time_dur_ms(t_time from, t_time to);
t_us_d			time_dur_us(t_time from, t_time to);
t_ms_t			time_now_ms(t_time begin);

#endif // LIB_H
