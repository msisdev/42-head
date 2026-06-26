/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:40:55 by minseobk          #+#    #+#             */
/*   Updated: 2025/12/25 19:07:16 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_double(char **p)
{
	char	**t;

	if (!p)
		return ;
	t = p;
	while (*t)
	{
		free(*t);
		t++;
	}
	free(p);
}

char	*ft_strjoin2(const char *s1, const char *s2, const char *with)
{
	size_t	ssiz;
	char	*s;

	ssiz = ft_strlen(s1) + ft_strlen(s2) + 2;
	s = malloc(ssiz);
	if (!s)
		return (NULL);
	s[0] = '\0';
	ft_strlcat(s, s1, ssiz);
	ft_strlcat(s, with, ssiz);
	ft_strlcat(s, s2, ssiz);
	return (s);
}

t_error	resolve_path(char **paths, const char *name, char **res)
{
	if (!paths || !name || !res)
		return (ERROR_DEBUG);
	if (!ft_strchr(name, '/'))
	{
		while (*paths)
		{
			*res = ft_strjoin2(*paths, name, "/");
			if (!*res)
				return (ERROR_INTERNAL);
			if (access(*res, F_OK) == 0)
				return (ERROR_NOT_FOUND);
			if (access(*res, X_OK) == 0)
				return (ERROR_NOT_EXEC);
			free(*res);
			paths++;
		}
	}
	*res = ft_strdup(name);
	if (!*res)
		return (ERROR_INTERNAL);
	return (ERROR_NOT_FOUND);
}

t_error	set_paths(char ***paths, char **envp)
{
	if (!paths || !envp)
		return (ERROR_DEBUG);
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH", 4))
		{
			*paths = ft_split(*envp + 5, PATHSEP);
			if (!*paths)
				return (ERROR_INTERNAL);
			return (ERROR_OK);
		}
		envp++;
	}
	return (ERROR_UNEXPECTED);
}
