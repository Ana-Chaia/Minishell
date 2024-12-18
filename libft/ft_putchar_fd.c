/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:57:38 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/18 11:09:30 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_putchar_fd(char c, int fd)
// {
// 	write (fd, &c, 1);
// }



int	ft_putchar_fd(char c, int fd)
{
	int	result;

	result = write(fd, &c, 1);
	return (result);
}
