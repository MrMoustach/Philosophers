/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 10:49:18 by iharchi           #+#    #+#             */
/*   Updated: 2021/06/28 14:57:06 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/clist.h"

t_clist	*ft_new_clist(void *content)
{
	t_clist *ret;
	
	ret = (t_clist *)malloc(sizeof(t_clist));
	ret->content = content;
	ret->next = NULL;
	return (ret);
}

void	ft_destroy_clist(t_clist *node, void (*fun)(void *content))
{
	fun(node->content);
	free(node);
}

int	ft_add_clist(t_clist **list, t_clist *node)
{
	t_clist *tmp;
	int		i;

	if (!list)
		return (1);
	if (!*list)
	{		
		*list = node;
		node->next = *list;
		node->index = 0;
		return (0);
	}
	tmp = *list;
	i = 1;
	while (tmp->next != *list && tmp->next != NULL)
	{
		i++;	
		tmp = tmp->next;
	}
	tmp->next = node;
	node->next = *list;
	node->index = i;
	return (0);
}