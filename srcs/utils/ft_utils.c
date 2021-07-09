/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 17:50:12 by iharchi           #+#    #+#             */
/*   Updated: 2021/07/09 07:35:04 by iharchi          ###   ########.fr       */
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
