/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:59:51 by jbolanho          #+#    #+#             */
/*   Updated: 2024/12/09 12:12:31 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	echo(char **cmd)
{
	int	new_line;
	int	space;
	int	i;

	i = 1;
	space = 0;
	new_line = 1;
	while (check_minus_nnnns(cmd[i]))
	{
		i++;
		new_line = 0;
	}
	while (cmd[i])
	{
		if (space)
			ft_putchar_fd (' ', 1);
		else
			space++;
		ft_putstr_fd (cmd[i++], 1);
	}
	if (new_line)
		ft_putchar_fd ('\n', 1);
	return (0);
}

int	check_minus_nnnns(char *cmd)
{
	int	i;

	if (cmd && !ft_strncmp(cmd, "-n", 2))
	{
		i = 2;
		while (cmd[i] == 'n')
			i++;
		if (!cmd[i])
			return (1);
	}
	return (0);
}
