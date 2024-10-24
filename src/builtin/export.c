
//export
//export [-fn] [-p] [name[=value]]
//Mark each name to be passed to child processes in the environment.
//If the -f option is supplied, the names refer to shell functions; otherwise the names refer to shell variables. 
//The -n option means to no longer mark each name for export. 
//If no names are supplied, or if the -p option is given, a list of names of all exported variables is displayed.
// The -p option displays output in a form that may be reused as input. 
//If a variable name is followed by =value, the value of the variable is set to value.

//The return status is zero unless an invalid option is supplied, one of the names is not a valid shell variable name,
// or -f is supplied with a name that is not a shell function.

#include "../include/minishell.h"

int	export(char **token, t_export **export_list)
{
	int			i;
	char		**curr;

	i = 1;
	curr = token;
	*export_list = NULL;
	if (!curr[1])
		print_export(env_shellzito(NULL));
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
	
	return (0);
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
	name = substr_noquote(curr, 0, i - 1);
	if (curr[i] != '\0')
		value = substr_noquote(curr, i + 1, ft_strlen(curr) - i - 1);
	printf("name: %s \n", name);
	printf("value: %s \n", value);
	on_env = compare_to_env(name);
	node = create_node_exp(name, value, on_env);
	make_lst_exp(export_list, node);
	return (0);
}

int	compare_to_env(char *name)
{
	char	**env_shellzito_copy;
	int		i;

	env_shellzito_copy = env_shellzito(NULL);
	i = 0;
	while (env_shellzito_copy[i])
	{
		if (ft_strcmp(env_shellzito_copy[i], name) == 0)
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
		|| (token[0] == '_')))
			return (0);
	while (token[i] && token[i] != '=')
	{
		if ((token[i] >= 'A' && token[i] <= 'Z')
			|| (token[i] >= 'a' && token[i] <= 'z')
			|| (token[i] >= '0' && token[i] <= '9')
			|| (token[0] == '_'))
				i++;
		else
			return (0);
	}
	return (1);
}

t_export	*create_node_exp(char *name, char *value, int on_env)
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

// char	*substr_noquote(char const *s, unsigned int start, size_t len)
// {
// 	char	*new;
// 	size_t	len_s;
// 	size_t	i;

// 	len_s = 0;
// 	if (!s)
// 		return (NULL);
// 	while (s[len_s] != '\0')
// 		len_s++;
// 	if (len_s < start)
// 		return (ft_strdup(""));
// 	if (len >= len_s)
// 		new = (char *)malloc (len_s - start + 1);
// 	else
// 		new = (char *)malloc (len + 1);
// 	if (!new)
// 		return (NULL);
// 	i = 0;
// 	while (len-- >= 0 && s[start] != '\0')
// 	{
// 		if (s[start] == '"' || s[start] == '\'')
// 			start++;
// 		new[i++] = s[start++];
// 	}
// 	new[i] = '\0';
// 	return (new);
// }

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
	while (s[start + i] != '\0' && i <= len)
	{
		if (s[start] == '"' || s[start] == '\'')
			start++;
		mem[i] = s[start + i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}



void	print_export(char **copy)
{
	int	i;

	i = 0;
	if (copy == NULL)
		printf("VERIFICAR\n");
	while (copy[i])
	{
		printf("declare -x: %s\n", copy[i]);
		i++;
	}
	// em ordem alfabética
}


// int	export(char **token)
// {
// 	int		i;
// 	int		j;
// 	char	*name;
// 	char	*value;
// 	char	**env_shellzito_copy;

// 	i = 0;
// 	j = 0;
// 	value = NULL;
// 	if (!token[1])
// 		print_export(env_shellzito(NULL));
// 	else
// 	{
// 		if (token[2] && validate_export_token2(token[2]) == 0)
// 		{
// 			printf("export: %s: not a valid token4\n", token[2]);
// 			return (1);
// 		}
// 		while (token[1][i])
// 		{
// 			if (validate_export_name(token[1]) == 0)
// 			{
// 				printf("export: %s: not a valid identifier (name)\n", token[1]);
// 				return (1);
// 			}
// 			if (token[1][i] != '=' || token[1][i] != '\0')
// 				i++;
// 		}
// 		name = substr_noquote(token[1], 0, (i - 1));
// 		if (token[1][i] != '\0' && token[1][i + 1])
// 				value = substr_noquote(token[1], i + 1, 
// 						ft_strlen(token[1]) - i - 1);
// 		printf("name: %s \n", name);
// 		printf("value: %s \n", value);
		
// 		env_shellzito_copy = env_shellzito(NULL);
// 		if (ft_strcmp(env_shellzito_copy[0], value) == 0)
// 			printf("ja existe\n");
// 		else
// 			printf("nao existe\n");
// 	}
// 	return (0);
// }


// int	validate_export_name(char *token)
// {
// 	int	i;

// 	i = 0;
// 	while (token[i] && token[i] != '=')
// 	{
// 		if (!((token[i] >= 'A' && token[i] <= 'Z') 
// 				|| (token[i] >= 'a' && token[i] <= 'z')
// 				|| (token[i] >= '0' && token[i] <= '9')
// 				|| (token[i] == '_')))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	validate_export_token2(char *token)
// {
// 	int	i;

// 	i = 1;
// 	while (token[i])
// 	{
// 		if (((token[0] >= 'A' && token[0] <= 'Z') 
// 				|| (token[0] >= 'a' && token[0] <= 'z'))
// 			&& ((token[i] >= 'A' && token[i] <= 'Z')
// 				|| (token[i] >= 'a' && token[i] <= 'z')
// 				|| (token[i] >= '0' && token[i] <= '9')))
// 				i++;
// 		else
// 			return (0);
// 	}
// 	return (1);
// }