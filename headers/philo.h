/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zed <zed@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:01:39 by zed               #+#    #+#             */
/*   Updated: 2021/07/10 14:51:09 by zed              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include "clist.h"
# include "types.h"
# include "utils.h"

t_table	add_philo(t_table table, int id);
t_philo *ft_new_philo(int id, suseconds_t added);
void *routine(void *content);

#endif