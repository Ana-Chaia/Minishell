/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   across_the_universe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:59:39 by jbolanho          #+#    #+#             */
/*   Updated: 2025/01/14 17:04:03 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	across_the_universe(t_token **token_list)
{
	t_token	*temp;
	char	*curr;
	char	*new_content;

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
			new_content = find_dollar(temp->content);
			free(temp->content);
			temp->content = new_content;
		}
		temp = temp->next;
	}
}

char	*find_dollar(char *cmd)
{
	int		i;
	int		start;
	char	*new;
	char	*temp;

	i = 0;
	new = NULL;
	while (cmd[i] != '\0')
	{
		start = i;
		while (cmd[i] != '\0' && cmd[i] != '$')
			i++;
		if (i > start)
		{
			temp = ft_substr(cmd, start, i - start);
			new = ft_strjoin(new, temp);
			free(temp);
		}
		if (cmd[i] == '$')
			new = handle_dollar (cmd, &i, new);
	}
	return (new);
}

char	*handle_dollar(char *cmd, int *i, char *new)
{
	char	*value;
	int		start;

	value = NULL;
	(*i)++;
	if (validate_name (&cmd[*i]) != 1 && cmd[*i] != '?')
		value = ft_strdup("$");
	else if (cmd[*i] == '?')
	{
		value = ft_itoa(get_status(-1));
		(*i)++;
	}
	else
	{
		start = *i - 1;
		while (cmd[*i] != '\0' && cmd[*i] != ' ' && cmd[*i] != '$')
			(*i)++;
		value = change_dollar(cmd, start, *i - 1);
	}
	if (value)
	{
		new = ft_strjoin(new, value);
		free(value);
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
