/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_shellzito.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:48:56 by jbolanho          #+#    #+#             */
/*   Updated: 2024/10/28 09:28:06 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	copy_env(void)
{
	char	**our_env;
	char	**env;
	int		i;

	i = 0;
	env = __environ;
	while (env[i])
		i++;
	our_env = ft_calloc(sizeof(char *), (i + 1));
	i = 0;
	while (env[i])
	{
		our_env[i] = ft_strdup(env[i]);
		if (!our_env[i])
		{
			while (i--)
				free(our_env[i]);
			free(our_env);
		}
		i++;
	}
	env_shellzito(our_env);
}

void	free_env(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**env_shellzito(char **our_env)
{
	static char	**env_shellzito;

	if (our_env && env_shellzito)
		free_env(env_shellzito);
	if (our_env)
		env_shellzito = our_env;
	return (env_shellzito);
}
