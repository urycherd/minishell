/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 19:44:53 by qsergean          #+#    #+#             */
/*   Updated: 2022/09/13 23:17:33 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*iter;

	i = 0;
	iter = lst;
	while (iter)
	{
		i++;
		iter = iter->next;
	}
	return (i);
}
