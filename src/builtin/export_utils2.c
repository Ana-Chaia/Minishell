/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:09:19 by jbolanho          #+#    #+#             */
/*   Updated: 2024/12/19 16:32:29 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**come_together_env(char **new_env, t_exp *curr)
{
	char	**up_env;
	int		i;

	i = 0;
	up_env = new_env;
	while (up_env[i])
		i++;
	up_env[i] = join_env(curr->name, curr->value);
	up_env[i + 1] = NULL;
	return (up_env);
}

char	*join_env(char const *s1, char const *s2)
{
	char	*new;
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new = (char *)malloc ((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	if (s2)
	{
		new[i++] = '=';
		while (s2[j] != '\0')
			new[i++] = s2[j++];
	}
	new[i] = '\0';
	return (new);
}

int	list_export(char *token, t_exp **export_list, int i)
{
	char		*curr;
	char		*name;
	char		*value;
	int			on_env;
	t_exp		*node;

	i = 0;
	value = NULL;
	on_env = 0;
	curr = token;
	while (curr[i] != '=' && curr[i] != '\0')
		i++;
	name = substr_noquote(curr, 0, i);
	if (curr[i] != '\0')
		value = substr_noquote(curr, i + 1, ft_strlen(curr) - i);
	on_env = compare_to_env(name);
	node = create_node_exp(name, value, on_env, curr[i]);
	make_lst_exp(export_list, node);
	return (0);
}

int	compare_to_env(char *name)
{
	char	**env_shellzito_copy;
	int		i;
	int		j;
	char	*substr;

	env_shellzito_copy = env_shellzito(NULL);
	i = 0;
	while (env_shellzito_copy[i])
	{
		j = 0;
		while (env_shellzito_copy[i][j] != '='
			&& env_shellzito_copy[i][j] != '\0')
			j++;
		substr = ft_substr(env_shellzito_copy[i], 0, j);
		if (ft_strcmp(substr, name) == 0)
		{
			return (42);
		}
		free(substr);
		i++;
	}
	return (0);
}

t_exp	*create_node_exp(char *name, char *value, int on_env, char eq)
{
	t_exp	*new;

	new = malloc(sizeof(t_exp));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->on_env = on_env;
	if (eq == '=')
		new->equal = 1;
	else
		new->equal = 0;
	new->next = NULL;
	new->prev = NULL;
	free(name);
	free(value);
	return (new);
}
