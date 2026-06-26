/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:05:59 by minseobk          #+#    #+#             */
/*   Updated: 2026/01/01 18:26:41 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# ifdef _WIN32
#  ifndef PATHSEP
#   define PATHSEP ';'
#  endif
# else
#  ifndef PATHSEP
#   define PATHSEP ':'
#  endif
# endif
# ifndef P_RD
#  define P_RD 0
# endif
# ifndef P_WR
#  define P_WR 1
# endif
# ifndef MSG_DEBUG
#  define MSG_DEBUG "Debug your program"
# endif
# ifndef MSG_ARG
#  define MSG_ARG "Usage: pipex <file1> <cmd1> <cmd2> <file2>"
# endif
# ifndef MSG_NOT_EXEC
#  define MSG_NOT_EXEC "Command is not executable"
# endif
# ifndef MSG_NOT_FOUND
#  define MSG_NOT_FOUND "Command not found"
# endif

typedef int	t_fd;

typedef enum e_error
{
	ERROR_OK,
	ERROR_DEBUG,
	ERROR_INTERNAL,
	ERROR_UNEXPECTED,
	ERROR_ARG,
	ERROR_CLOSE,
	ERROR_DUP,
	ERROR_EXEC,
	ERROR_FORK,
	ERROR_OPEN,
	ERROR_PIPE,
	ERROR_WAIT,
	ERROR_NOT_EXEC = 126,
	ERROR_NOT_FOUND = 127,
}	t_error;

/**
 *	DESCRIPTION
 *
 *		- `env_field__`
 *		- `nullable_field_`
 *		- `need_free_field`
 */
typedef struct s_context
{
	char		*app__;
	char		**envp__;
	t_fd		p[2];
	char		**paths;
	const char	*fname_;
	char		*cmd_;
	char		**sp;
	char		*path;
	t_error		err;
}	t_context;

/* context.c */
t_error	ctx_init(t_context *ctx, int argc, char *argv[], char *envp[]);
t_error	ctx_resolve(t_context *ctx, const char *name);
void	ctx_del(t_context *ctx);
void	panic(t_context *ctx);

/* error.c */
void	puterr(t_context c);
t_error	seterr(t_context *ctx, t_error err);
int		maperr(t_error err);

/* util.c */
void	free_double(char **p);
char	*ft_strjoin2(const char *s1, const char *s2, const char *with);
t_error	resolve_path(char **paths, const char *name, char **res);
t_error	set_paths(char ***paths, char **envp);

/* wrap.c */
void	wdup2(t_context *c, t_fd fd, t_fd fd2);
void	wclose(t_context *c, t_fd fd);
void	wfork(t_context *c, pid_t *pid);
t_fd	wopen(t_context *c, const char *fname, bool is_read);
void	wwaitpid(t_context *c, pid_t pid, int *stat);

#endif // MAIN_H
