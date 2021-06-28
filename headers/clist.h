/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 09:56:42 by iharchi           #+#    #+#             */
/*   Updated: 2021/06/28 12:42:04 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIST_H
# define CLIST_H
# include <stdlib.h>

typedef struct s_clist 
{
	void			*content;
	struct s_clist	*next;
	int				index;
}			   t_clist;

t_clist	*ft_new_clist(void *content);
void	ft_destroy_clist(t_clist *node, void (*fun)(void *content));
int		ft_add_clist(t_clist **list, t_clist *node);
#endif