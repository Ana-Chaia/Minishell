/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   across_the_universe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:59:39 by jbolanho          #+#    #+#             */
/*   Updated: 2024/12/10 11:59:58 by jbolanho         ###   ########.fr       */
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
    int i;
    int start;
    char *new;
    char *temp;
    char *value;

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
			printf("NEW inicio =%s\n", new);
			free(temp);
        }
        if (cmd[i] == '$')
        {
            start = i;
            i++; 
            if (cmd[i] == '?')
            {
                value = ft_itoa(get_status(-1));
                i++;
            }
            else
            {
                start = i - 1;
                while (cmd[i] != '\0' && cmd[i] != ' ' && cmd[i] != '$')
                    i++;
				printf("cmd[start] = %c\n", cmd[start]);	
				printf("cmd[i] = %c\n", cmd[i]);	
                value = change_dollar(cmd, start, i - 1);
				printf("VALUE = %s\n", value);
            }
            if (value)
            {
                new = ft_strjoin(new, value);
				free(value);
				printf("NEWfinal= %s\n", new);
            }
        }
	}
    return (new);
}



/*
char	*find_dollar(char *cmd)
{
	int		i;
	int		x;
	char	*value;
	char	*new;
	char	*substr;
	char	*temp;

	i = 0;
	new = NULL;
	value = cmd;
	temp = NULL;
	while (cmd[i])
	{
		new = not_expanded(cmd, i, temp);
		printf("FINDDOLLAR_new= %s\n", new);     //apagar
		if (cmd[i] == '$')
		{
			if (cmd[i + 1] == '?')
			{
				value = ft_itoa(get_status(-1));
				new = ft_strjoin(new, value);
				i += 2;
			}
			x = i;
			while (cmd[i] != ' ' && cmd[i] != '\0')
				i++;
			value = change_dollar(cmd, x, i);
			if (value)
			{
				new = (ft_strjoin(new, value));
				printf("AQUI1:new %s\n", new);
			}
			free(value);
		}
		x = i;
		while (cmd[i] && cmd[i] != '$')
			i++;
		substr = ft_substr(cmd, x, i);
		temp = ft_strjoin(new, substr);
		printf("AQUI2:temp %s\n", temp);
		free(substr);
		//new = ft_strjoin(new, ft_substr (cmd, x, i));
	}
	free(new);
	return (temp);
}

char *not_expanded(char *cmd, int i, char *temp)
{
	char *str;
	int	idx;
	char	*result;
	int		len;

	idx = i;
	while (cmd[idx] != '\0' && cmd[idx] != '$') 
		idx++;
	len = idx - i;
	printf("LEN: %d\n", len);
	if (len == 0)
		return (NULL);
	str = (char *)malloc ((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	printf("AQUI: str1 %s\n", str);
	str = ft_strxcpy(str, &cmd[i], len);
	printf("AQUI: str2 %s\n", str);
	if (temp == NULL)
		return (str);
	result = ft_strjoin(temp, str);
	free(str);
	printf("AQUI3:result %s\n", result);
	return (result);
}
*/

char	*ft_strxcpy(char *dest, char *src, size_t destsize)
{
	size_t	i;

	if (destsize == 0)
		return (src);
	i = 0;
	while (i < destsize -1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


char	*change_dollar(char *cmd, int start, int end)
{
	char	*name;
	char	*value;
	char	**our_env;

	printf("PASSOU EM CHANGE DOLLAR \n");
	name = ft_substr(cmd, (start + 1), (end - start));
	our_env = env_shellzito(NULL);
	value = cut_value (name, our_env);
	printf("VALUE $$$ = %s\n", value);
	free (name);
	return (value);
}

char	*cut_value(char *name, char **env)
{
	int		i;
	int		j;
	char	*value;
	char	*temp;
	char	*temp2;

	i = 0;
	j = 0;
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
				temp2 = ft_substr(env[i], (j + 1), (ft_strlen(env[i])
							- j));
				value = temp2;
				free (temp);
				//free (temp2);
			}
			return (value);
		}
		free (temp);
		// else
		// 	return (NULL);
		i++;
	}
	return (value);
}
