/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:18:15 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/18 11:57:20 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	unset(char **cmd)
{
	int		i;

	if (!cmd[1])
		return (0);
	i = 1;
	while (cmd[i])
	{
		if (validate_name(cmd[i]) != 1)
		{
			ft_printf_fd(STDERR_FILENO, "unset: not a valid identifier\n");
			//printf("unset: %s: not a valid identifier\n", cmd[i]);
			get_status(1);
		}
		else
			delete_variable(cmd[i]);
		i++;
	}
	return (1);
}

void	delete_variable(char *var)
{
	char	**env;
	int		x;
	int		i;
	int		j;

	env = env_shellzito(NULL);
	i = 0;
	x = 0;
	while (var[x])
	{
		if (var[x] == '=')
		{
			ft_printf_fd(STDERR_FILENO, "unset: not a valid identifier\n");
			//printf("unset: %s: not a valid identifier\n", var);
			get_status(1);
			return ;
		}
		x++;
	}
	while (env[i])
	{
		x = 0;
		while (env[i][x] != '=' && env[i][x] != '\0')
			x++;
		if (ft_strcmp(ft_substr(env[i], 0, x), var) == 0)
		{
			free(env[i]);
			j = i;
			while (env[j])
			{
				env[j] = env[j + 1];
				j++;
			}
			break ;
		}
		i++;
	}
}
