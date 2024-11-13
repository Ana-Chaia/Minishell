/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:17:54 by anacaro5          #+#    #+#             */
/*   Updated: 2024/11/04 10:12:45 by anacaro5         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	export(char **cmd, t_export **export_list)
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
				printf("export: %s: not a valid identifier\n", curr[i]);
			}
			else
				list_export(curr[i], export_list);
			i++;
		}
		all_you_need_is_env(export_list, i);
	}
	return (0);
}

void	all_you_need_is_env(t_export **export_list, int i)
{
	char		**new_env;
	char		**env;
	t_export	*curr;
	int			j;
	int			k;
	char		**shell;
	int x;

	k = 0;
	env = env_shellzito(NULL);
	new_env = strawberry_fields_forenv(env, i);
	// while (env[k])
	// {
	// 	new_env[k] = ft_strdup(env[k]);
	// 	k++;
	// }
	curr = *export_list;
	while (curr)
	{
		if ((curr->on_env == 42 && curr->equal == 1) || curr->on_env == 0)
		{
			j = 0;
			while (new_env[j])
			{
				x = 0;
				while (new_env[j][x] != '=' && new_env[j][x] != '\0')
					x++;
				printf("Comparando %s com %s\n", new_env[j], curr->name);
				if (ft_strcmp(ft_substr(new_env[j], 0, x), curr->name) == 0)
				{
					printf("Substituindo %s com %s\n", new_env[j], curr->name);
					// usar unset para eliminar a linha
					free(new_env[j]);
					new_env[j] = join_env(curr->name, curr->value);
					curr->on_env = 42;
				}	
				j++;
			}
			if (curr->on_env == 0)
				new_env = come_together_env(new_env, curr);
		}
		curr = curr->next;
	}
	// while (env[k])
	// {
	// 	printf("env: %s\n", env[k]);
	//  	k++;
	// }
	// k = 0;
	while (new_env[k])
	{
		printf("new_env: %s\n", new_env[k]);
	 	k++;
	}
	env_shellzito (new_env);
	k = 0;
	shell = env_shellzito(NULL);
	while (shell[k])
	{
	 	printf("env_shellzito: %s\n", shell[k]);
	 	k++;
	}
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
	printf("len_strawberry: %zu\n", len);
	new_env = (char **)malloc((len + i + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	while (env[k])
	{
		new_env[k] = ft_strdup(env[k]);
		if (!new_env[k])
		{
			while (k > 0)
			{
				free(new_env[k]);
				k--;
			}
			free(new_env);
			return (NULL);
		}
		k++;
	}
	new_env[k] = NULL;
	return (new_env);
}

char	**come_together_env(char **new_env, t_export *curr)
{
	char **up_env;
	int	i;
	int	k;

	k = 0;
	i = 0;
	up_env = new_env;
	while (up_env[i])
		i++;
	up_env[i] = join_env(curr->name, curr->value);
	//up_env[i + 1] = (char *)malloc((1) * sizeof(char *));
	up_env[i + 1] = NULL;
	// while (up_env[k])
	// {
	// 	printf("up_env: %s\n", up_env[k]);
	// 	k++;
	// }
	return (up_env);
}



size_t	ft_strlen_env(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*join_env(char const *s1, char const *s2)
{
	char	*new;
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_strlen_env(s1) + ft_strlen_env(s2) + 1;
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
		// new[i++] = '"';
		while (s2[j] != '\0')
		{
			new[i] = s2[j];
			i++;
			j++;
		}
	}
	// new[i++] = '"';
	new[i] = '\0';
	printf("join_env_line: %s\n", new);
	return (new);
}

int	list_export(char *token, t_export **export_list)
{
	int			i;
	char		*curr;
	char		*name;
	char		*value;
	int			on_env;
	t_export	*node;

	i = 0;
	value = NULL;
	on_env = 0;
	curr = token;
	while (curr[i] != '=' && curr[i] != '\0')
		i++;
	name = substr_noquote(curr, 0, i);
	if (curr[i] != '\0')
		value = substr_noquote(curr, i + 1, ft_strlen(curr) - i);
	printf("name: %s \n", name);
	printf("value: %s \n", value);
	on_env = compare_to_env(name);
	node = create_node_exp(name, value, on_env, curr[i]);
	make_lst_exp(export_list, node);
	return (0);
}

int	compare_to_env(char *name)
{
	char	**env_shellzito_copy;
	int		i;
	int j;

	env_shellzito_copy = env_shellzito(NULL);
	i = 0;
	while (env_shellzito_copy[i])
	{
		j = 0;
		while (env_shellzito_copy[i][j] != '=' && env_shellzito_copy[i][j] != '\0')
			j++;
		if (ft_strcmp(ft_substr(env_shellzito_copy[i], 0, j), name) == 0)
		{
			printf("ja existe\n");
			return (42);
		}	
		i++;
	}
	printf("nao existe\n");
	return (0);
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

t_export	*create_node_exp(char *name, char *value, int on_env, char eq)
{
	t_export	*new;
	int			x;

	x = 0;
	new = malloc(sizeof(t_export));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	//criar var com aspas e valor??? ou var pronta para colocar no env??
	new->on_env = on_env;
	if (eq == '=')
		new->equal = 1;
	else
		new->equal = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	make_lst_exp(t_export **export_list, t_export *export_node)
{
	t_export	*curr;

	if (!export_node)
		return ;
	curr = NULL;
	if (*export_list == NULL)
	{
		*export_list = export_node;
		printf("colocou o nó inicial \n");
	}	
	else
	{
		curr = *export_list;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = export_node;
		export_node->prev = curr;
		printf("colocou o nó: %s na lista \n", curr->next->name);
	}
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
	printf("len b4: %zu\n", len);
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	printf("len after: %zu\n", len);
	mem = (char *)malloc((len + 1) * sizeof(char));    //MUDEI
	if (mem == NULL)
		return (NULL);
	while (s[start + i] != '\0' && i < len)
	{
		//if (s[start + i] == '"' || s[start + i] == '\'')
		//	start++;
		mem[i] = s[start + i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}

void	print_export(char **copy)
{
	int		i;
	int 	j;
	int 	k;
	char 	*temp;
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

