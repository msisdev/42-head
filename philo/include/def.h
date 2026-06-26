/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 15:57:09 by minseobk          #+#    #+#             */
/*   Updated: 2026/06/26 14:45:11 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_H
# define DEF_H
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# define THREAD_CREATE_OK 0
# define THREAD_JOIN_OK 0
# define MUTEX_INIT_OK 0
# define MUTEX_DESTROY_OK 0
# define MUTEX_LOCK_OK 0
# define MUTEX_UNLOCK_OK 0
# define SEC_TO_USEC 1000000
# define SEC_TO_MSEC 1000
# define MSEC_TO_USEC 1000

typedef struct s_ctx	t_ctx;
typedef enum e_error	t_error;
typedef int				t_ms_d;
typedef int				t_ms_t;
typedef struct s_mutex	t_mutex;
typedef int				t_phid;
typedef struct s_thread	t_thread;
typedef struct timeval	t_time;
typedef useconds_t		t_us_d;
typedef useconds_t		t_us_t;

/* ---------------------------------- */
/* error                              */
/* ---------------------------------- */

typedef enum e_error
{
	ERROR_OK = 0,
	ERROR_DEBUG,
	ERROR_INTERNAL,
	ERROR_ARG,
	ERROR_MUTEX,
	ERROR_THREAD,
}	t_error;

/* ---------------------------------- */
/* ctx                                */
/* ---------------------------------- */

typedef struct s_ctx
{
	t_error		err;
}	t_ctx;

t_ctx		ctx_make(void);
t_error		seterr(t_ctx *c_ref, t_error err);
t_error		geterr(const t_ctx *c_ref);

/* ---------------------------------- */
/* mem                                */
/* ---------------------------------- */

void		*mem_get(size_t size);

/* ---------------------------------- */
/* mutex                              */
/* ---------------------------------- */

typedef struct s_mutex
{
	pthread_mutex_t	mx;
	bool			is_init;
}	t_mutex;

t_error		mutex_init(t_ctx *c_ref, t_mutex *mx_ref);
void		mutex_destroy(t_mutex *mx_ref);
void		mutex_lock(t_mutex *mx_ref);
void		mutex_unlock(t_mutex *mx_ref);

/* ---------------------------------- */
/* thread                             */
/* ---------------------------------- */

typedef struct s_thread
{
	pthread_t	th;
	bool		is_running;
}	t_thread;

t_error		thread_create(t_ctx *c_ref,
				t_thread *th_ref, void *(*f)(void *), void *arg);
t_error		thread_join(t_ctx *c_ref, t_thread *th_ref);

/* ---------------------------------- */
/* util                               */
/* ---------------------------------- */

size_t			ft_strlen(char *s);

#endif /* DEF_H */
