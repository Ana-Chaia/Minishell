/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_shellzito.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:48:56 by jbolanho          #+#    #+#             */
/*   Updated: 2024/10/24 15:27:46 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

//na main tem que ter envp como variavel

void	copy_env()
{
	char	**our_env;
	char	**env;
	int		i;

	i = 0;
	env = __environ;
	while (env[i])
		i++;
	our_env = malloc (sizeof(char*) * (i + 1));
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
	// print_env_copy(our_env);
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
	// print_env_copy(env_shellzito);
	return (env_shellzito);
}
