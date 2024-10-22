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

int	export(char **token)
{
	int		i;
	char	*name;
	char	*value;
	char**	env_shellzito_copy;

	i = 0;
	value = NULL;
	if (!token[1])
		print_export(env_shellzito(NULL));
	else
	{
		if (token[2] && validate_export_token2(token[2]) == 0)
		{
			printf("export: %s: not a valid token4\n", token[2]);
			return (1);
		}
		while (token[1][i])
		{
			if (validate_export_name(token[1]) == 0)
			{
				printf("export: %s: not a valid identifier (name)\n", token[1]);
				return (1);
			}
			if (token[1][i] != '=' || token[1][i] != '\0')
				i++;
		}
		name = substr_noquote(token[1], 0, (i - 1));
		if (token[1][i] != '\0' && token[1][i + 1])
				value = substr_noquote(token[1], i + 1, 
						ft_strlen(token[1]) - i - 1);
		printf("name: %s \n", name);
		printf("value: %s \n", value);
		
		env_shellzito_copy = env_shellzito(NULL);
		if (ft_strcmp(env_shellzito_copy[0], value) == 0)
			printf("ja existe\n");
		else
			printf("nao existe\n");
	}
	return (0);
}


int	validate_export_name(char *token)
{
	int	i;

	i = 0;
	while (token[i] && token[i] != '=')
	{
		if (!((token[i] >= 'A' && token[i] <= 'Z') 
				|| (token[i] >= 'a' && token[i] <= 'z')
				|| (token[i] >= '0' && token[i] <= '9')
				|| (token[i] == '_')))
			return (0);
		i++;
	}
	return (1);
}

int	validate_export_token2(char *token)
{
	int	i;

	i = 1;
	while (token[i])
	{
		if (((token[0] >= 'A' && token[0] <= 'Z') 
				|| (token[0] >= 'a' && token[0] <= 'z'))
			&& ((token[i] >= 'A' && token[i] <= 'Z')
				|| (token[i] >= 'a' && token[i] <= 'z')
				|| (token[i] >= '0' && token[i] <= '9')))
				i++;
		else
			return (0);
	}
	return (1);
}

char	*substr_noquote(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	len_s;
	size_t	i;

	len_s = 0;
	if (!s)
		return (NULL);
	while (s[len_s] != '\0')
		len_s++;
	if (len_s < start)
		return (ft_strdup(""));
	if (len >= len_s)
		new = (char *)malloc (len_s - start + 1);
	else
		new = (char *)malloc (len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (len-- >= 0 && s[start] != '\0')
	{
		if (s[start] == '"' || s[start] == '\'')
			start++;
		new[i++] = s[start++];
	}
	new[i] = '\0';
	return (new);
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
}



