/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:11:02 by jbolanho          #+#    #+#             */
/*   Updated: 2024/12/18 11:27:44 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env(char **cmd)
{
	int		i;
	char	**our_env;

	i = 0;
	if (cmd[1])
	{
		printf("no options or arguments");
		return (0);
	}
	our_env = env_shellzito(NULL);
	while (our_env[i])
	{
		if (our_env[i] && ft_strchr(our_env[i], '='))
			printf("%s\n", our_env[i]);
		i++;
	}
	return (1);
}
