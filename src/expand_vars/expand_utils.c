/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:02:03 by anacaro5          #+#    #+#             */
/*   Updated: 2025/01/16 17:02:46 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*change_dollar(char *cmd, int start, int end)
{
	char	*name;
	char	*value;
	char	**our_env;

	name = ft_substr(cmd, (start + 1), (end - start));
	our_env = env_shellzito(NULL);
	value = cut_value (name, our_env, 0, 0);
	free (name);
	return (value);
}

char	*cut_value(char *name, char **env, int i, int j)
{
	char	*value;
	char	*temp;
	char	*temp2;

	value = NULL;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=' && env[i][j] != '\0')
			j++;
		temp = ft_substr(env[i], 0, j);
		if (ft_strcmp(temp, name) == 0)
		{
			if (env[i][j + 1] && env[i][j + 2])
			{
				temp2 = ft_substr(env[i], (j + 1), (ft_strlen(env[i]) - j));
				value = temp2;
				free (temp);
			}
			return (value);
		}
		free (temp);
		i++;
	}
	return (value);
}
