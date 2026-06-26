/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:15:51 by minseobk          #+#    #+#             */
/*   Updated: 2025/10/14 14:51:03 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;
	t_list	*t;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	p = *lst;
	while (p != NULL)
	{
		t = p->next;
		ft_lstdelone(p, del);
		p = t;
	}
	*lst = NULL;
}
