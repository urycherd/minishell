/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:01:28 by qsergean          #+#    #+#             */
/*   Updated: 2021/10/23 21:26:09 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;
	t_list	*iter;

	iter = *lst;
	while (iter)
	{
		p = iter->next;
		if (iter->content)
			del(iter->content);
		free(iter);
		iter = p;
	}
	*lst = NULL;
}
