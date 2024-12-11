/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:18:15 by anacaro5          #+#    #+#             */
/*   Updated: 2024/10/28 17:18:04 by anacaro5         ###   ########.fr       */
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
			printf("unset: %s: not a valid identifier\n", cmd[i]);
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
			printf("unset: %s: not a valid identifier\n", var);
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
