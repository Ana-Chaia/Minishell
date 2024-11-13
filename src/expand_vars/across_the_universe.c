/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   across_the_universe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:59:39 by jbolanho          #+#    #+#             */
/*   Updated: 2024/11/04 10:25:23 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	across_the_universe(t_token **token_list)
{
	t_token	*temp;
	char	*curr;

	temp = *token_list;
	while (temp)
	{
		if (temp->type == D_QUOTES || temp->type == S_QUOTES)
		{
			curr = ft_substr(temp->content, 1, (ft_strlen(temp->content) - 2));
			free (temp->content);
			temp->content = curr;
		}
		if (temp->type == D_QUOTES || temp->type == WORD)
		{
			temp->content = find_dollar(temp->content);
		}
		temp = temp->next;
	}
}

char	*find_dollar(char *cmd)
{
	int		i;
	int		x;
	char	*value;
	char	*new;

	i = 0;
	new = NULL;
	value = cmd;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			if (cmd[i + 1] == '?')
			{
				value = ft_itoa(42);
				new = ft_strjoin(new, value);
				i += 2;
			}
			x = i;
			while (cmd[i] != ' ' && cmd[i] != '\0')
				i++;
			value = change_dollar(cmd, x, i);
			if (value)
				new = (ft_strjoin(new, value));
		}
		x = i;
		while (cmd[i] && cmd[i] != '$')
			i++;
		new = ft_strjoin(new, ft_substr (cmd, x, i));
	}
	return (new);
}

char	*change_dollar(char *cmd, int start, int end)
{
	char	*name;
	char	*value;
	char	**our_env;

	name = ft_substr(cmd, (start + 1), (end - start));
	our_env = env_shellzito(NULL);
	value = cut_value (name, our_env);
	return (value);
}

char	*cut_value(char *name, char **env)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	value = NULL;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=' && env[i][j] != '\0')
			j++;
		if (ft_strcmp(ft_substr(env[i], 0, j), name) == 0)
		{
			if (env[i][j + 1] && env[i][j + 2])
				value = ft_substr(env[i], (j + 1), (ft_strlen(env[i])
							- j));
			return (value);
		}
		// else
		// 	return (NULL);
		i++;
	}
	return (value);
}
