/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 17:48:07 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/15 13:14:30 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "philo.h"
# define MAXINT 2147483647
# define MININT -2147483648
int		ft_atol(const char *str);
int		ft_is_number(char *s);
int		ft_strlen(char *s);
int		try_parse_int(char *str, int *err);
size_t	get_time();
void	n_sleep(size_t time);
void	express(t_philo	philo, size_t time);
#endif