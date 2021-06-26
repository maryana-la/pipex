/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:43:20 by rchelsea          #+#    #+#             */
/*   Updated: 2020/11/22 21:51:25 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int		i;
	char	string;

	i = 0;
	if (s && fd > 0)
	{
		while (s[i] != '\0')
		{
			string = s[i];
			write(fd, &string, 1);
			i++;
		}
	}
}
