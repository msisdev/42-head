/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:30:09 by minseobk          #+#    #+#             */
/*   Updated: 2025/10/16 13:21:39 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*safe_new_map(
	t_list *src,
	void *(*f)(void *),
	void (*del)(void *))
{
	void	*con;
	t_list	*node;

	con = f(src->content);
	node = ft_lstnew(con);
	if (node == NULL)
	{
		del(con);
		return (NULL);
	}
	return (node);
}

t_list	*ft_lstmap(
	t_list *lst,
	void *(*f)(void *),
	void (*del)(void *))
{
	t_list	*head;
	t_list	**p;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	head = NULL;
	p = &head;
	while (lst != NULL)
	{
		*p = safe_new_map(lst, f, del);
		if (*p == NULL)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		p = &((*p)->next);
		lst = lst->next;
	}
	return (head);
}
