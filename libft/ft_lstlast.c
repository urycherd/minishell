/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 19:47:27 by qsergean          #+#    #+#             */
/*   Updated: 2022/09/13 23:17:33 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*iter;

	if (lst == NULL)
		return (NULL);
	iter = lst;
	while (iter->next)
		iter = iter->next;
	return (iter);
}
