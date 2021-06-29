/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 09:56:42 by iharchi           #+#    #+#             */
/*   Updated: 2021/06/29 11:15:17 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIST_H
# define CLIST_H
# include <stdlib.h>
# include "types.h"

t_clist	*ft_new_clist(t_philo content);
int		ft_add_clist(t_clist **list, t_clist *node);
#endif