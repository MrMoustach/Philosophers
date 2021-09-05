/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 17:50:12 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/04 15:05:44 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/philo.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_is_number(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '+' || s[i] == '-'))
	{
		if (ft_isdigit(s[i]))
			break ;
		i++;
		if (s[i] == '+' || s[i] == '-')
			break ;
	}
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen(char *s)
{
	int ret;

	ret = 0;
	while (s[ret++])
	;
	return (ret);
}

int try_parse_int(char *str, int *err)
{
	long long	ret;
	
	if (!ft_is_number(str) || ft_strlen(str) > 13)
	{
		(*err)--;
		return (0);
	}
	ret = ft_atol(str);
	if (ret > MAXINT || ret < MININT)
	{
		(*err)--;
		return (0);
	}
	return ((int) ret);
}
