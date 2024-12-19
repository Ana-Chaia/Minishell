/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:53:17 by jbolanho          #+#    #+#             */
/*   Updated: 2024/12/19 16:33:04 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_export(char **copy)
{
	int		i;
	int		k;
	char	*value;
	char	*name;

	if (copy == NULL)
		return ;
	sort_export(copy);
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

void	sort_export(char **copy)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
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
}

int	validate_name(char *token)
{
	int	i;

	i = 1;
	if (!((token[0] >= 'A' && token[0] <= 'Z')
			|| (token[0] >= 'a' && token[0] <= 'z')
			|| (token[0] == '_')
			|| (token[0] == '"') || (token[0] == '\'')))
		return (0);
	while (token[i] && token[i] != '=')
	{
		if ((token[i] >= 'A' && token[i] <= 'Z')
			|| (token[i] >= 'a' && token[i] <= 'z')
			|| (token[i] >= '0' && token[i] <= '9')
			|| (token[i] == '_')
			|| (token[i] == '"') || (token[i] == '\''))
			i++;
		else
			return (0);
	}
	return (1);
}

char	*substr_noquote(char const *s, unsigned int start, size_t len)
{
	char			*mem;
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	mem = (char *)malloc((len + 1) * sizeof(char));
	if (mem == NULL)
		return (NULL);
	while (s[start + i] != '\0' && i < len)
	{
		mem[i] = s[start + i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}

void	make_lst_exp(t_exp **export_list, t_exp *export_node)
{
	t_exp	*curr;

	if (!export_node)
		return ;
	curr = NULL;
	if (*export_list == NULL)
	{
		*export_list = export_node;
	}
	else
	{
		curr = *export_list;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = export_node;
		export_node->prev = curr;
	}
}

// size_t	ft_strlen_env(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	if (str == NULL)
// 		return (0);
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }
//troquei pela ft_strlen