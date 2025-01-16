/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:03:05 by anacaro5          #+#    #+#             */
/*   Updated: 2025/01/15 14:05:14 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	search_in_env(char **our_env, char *var, char *value)
{
	int		i;
	char	*to_env;

	to_env = NULL;
	i = 0;
	while (our_env[i])
	{
		if (ft_strncmp(our_env[i], var, ft_strlen(var)) == 0
			&& our_env[i][ft_strlen(var)] == '=')
		{
			to_env = join_env(var, value);
			if (!to_env)
				return (0);
			free(our_env[i]);
			our_env[i] = to_env;
			return (1);
		}
		i++;
	}
	return (i);
}
