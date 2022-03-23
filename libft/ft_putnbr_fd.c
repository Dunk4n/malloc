/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:14:16 by niduches          #+#    #+#             */
/*   Updated: 2019/10/08 15:00:13 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	str[11];
	int		i;
	int		tmp;

	i = 0;
	tmp = (n < 0) ? 1 : 0;
	while (n != 0 || i == 0)
	{
		str[10 - i++] = ((n % 10 < 0) ? -(n % 10) : (n % 10)) + '0';
		n /= 10;
	}
	if (tmp == 1)
		str[10 - i++] = '-';
	write(fd, str + 11 - i, i);
}
