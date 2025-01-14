/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:58:23 by anacaro5          #+#    #+#             */
/*   Updated: 2025/01/14 18:33:45 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	invalid_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{	
		if (is_space(input[i]) == 1)
			i++;
		else
			return (0);
	}
	if (input[i] == '\0')
		return (1);
	return (0);
}

void	close_fds_sys(void)
{
	close(3);
	close(103);
	close(39);
	close(38);
	close(37);
}

void	bye_bye_shell(int status)
{
	t_minishell	*mini;

	
	bye_bye(mini);
	close_fds_sys();
	exit(status);
}
