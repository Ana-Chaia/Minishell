/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:17:54 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/19 16:30:51 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	export(char **cmd, t_minishell *mini)
{
	int			i;
	char		**curr;

	i = 1;
	curr = cmd;
	if (!curr[1])
		print_export(env_shellzito(NULL));
	else
	{
		while (curr[i])
		{
			if (validate_name(curr[i]) != 1)
			{
				ft_printf_fd(STDERR_FILENO, "export: not a valid identifier\n");
				get_status(1);
			}
			else
				list_export(curr[i], &(mini)->export_list, 0);
			i++;
		}
		all_you_need_is_env(mini->export_list, i);
	}
	return (0);
}

void	all_you_need_is_env(t_exp *export_list, int i)
{
	char		**new_env;
	char		**env;
	t_exp		*curr;

	env = env_shellzito(NULL);
	new_env = strawberry_fields_forenv(env, i);
	curr = export_list;
	while (curr)
	{
		if ((curr->on_env == 42 && curr->equal == 1) || curr->on_env == 0)
			new_env = update_env_var(new_env, curr);
		curr = curr->next;
	}
	env_shellzito (new_env);
}

char	**update_env_var(char **new_env, t_exp *curr)
{
	int		j;
	int		x;
	char	*substr;

	j = 0;
	while (new_env[j])
	{
		x = 0;
		while (new_env[j][x] != '=' && new_env[j][x] != '\0')
			x++;
		substr = ft_substr(new_env[j], 0, x);
		if (ft_strcmp(substr, curr->name) == 0)
		{
			free(new_env[j]);
			new_env[j] = join_env(curr->name, curr->value);
			curr->on_env = 42;
		}
		free(substr);
		j++;
	}
	if (curr->on_env == 0)
		new_env = come_together_env(new_env, curr);
	return (new_env);
}

char	**strawberry_fields_forenv(char **env, int i)
{
	char	**new_env;
	int		k;
	size_t	len;

	if (!env)
		return (NULL);
	len = 0;
	k = 0;
	while (env[len])
		len++;
	new_env = (char **)malloc((len + i + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	while (env[k])
	{
		new_env[k] = ft_strdup(env[k]);
		if (!new_env[k])
		{
			free_partial_env(new_env, k);
			return (NULL);
		}
		k++;
	}
	new_env[k] = NULL;
	return (new_env);
}

void	free_partial_env(char **new_env, int k)
{
	while (k > 0)
	{
		free(new_env[k]);
		k--;
	}
	free(new_env);
}
// char	**strawberry_fields_forenv(char **env, int i)
// {
// 	char	**new_env;
// 	int		k;
// 	size_t	len;

// 	if (!env)
// 		return (NULL);
// 	len = 0;
// 	k = 0;
// 	while (env[len])
// 		len++;
// 	new_env = (char **)malloc((len + i + 1) * sizeof(char *));
// 	if (!new_env)
// 		return (NULL);
// 	while (env[k])
// 	{
// 		new_env[k] = ft_strdup(env[k]);
// 		if (!new_env[k])
// 		{
// 			while (k > 0)
// 			{
// 				free(new_env[k]);
// 				k--;
// 			}
// 			free(new_env);
// 			return (NULL);
// 		}
// 		k++;
// 	}
// 	new_env[k] = NULL;
// 	return (new_env);
// }
/*
void	print_export(char **copy)
{
	int		i;
	int		j;
	int		k;
	char	*temp;
	char	*value;
	char	*name;

	i = 0;
	if (copy == NULL)
		return ;
	while (copy[i])
	{
		j = i + 1;
		while (copy[j])
		{
			if (ft_strncmp(copy[i], copy[j], ft_strlen(copy[i])) > 0)
			{
				temp = copy[i];
				copy[i] = copy[j];
				copy[j] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (copy[i])
	{
		k = 0;
		while (copy[i][k] != '=' && copy[i][k] != '\0')
			k++;
		value = ft_strchr(copy[i], '=');
		name = ft_substr(copy[i], 0, k);
		if (value)
			printf("declare -x %s=\"%s\"\n", name, value + 1);
		else
			printf("declare -x %s\n", name);
		free(name);
		i++;
	}
}
*/
