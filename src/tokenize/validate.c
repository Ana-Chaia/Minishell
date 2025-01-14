/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:28:44 by jbolanho          #+#    #+#             */
/*   Updated: 2025/01/14 17:05:54 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	validate_input(t_minishell *mini)
{
	if ((quotes_closed(mini->input) != 42))
	{
		ft_putstr_fd("Shellzito: error quotes not closed\n", 2);
		get_status(2);
		return (1);
	}
	return (0);
}

void	invalid_input(char c)
{
	if ((c == '(') || (c == ')') || (c == '\\') || (c == ';'))
	{
		ft_putstr_fd("Shellzito: error invalid character\n", 2);
		exit(2);
	}
}

int	quotes_closed(char *str)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (str[i])
	{
		if (str[i] == '"')
			d_quote = count_quote(str, &i, '"');
		else if (str[i] == '\'')
			s_quote = count_quote(str, &i, '\'');
		else
		{
			invalid_input(str[i]);
			i++;
		}
	}
	if ((s_quote % 2 == 0) && (d_quote % 2 == 0))
		return (42);
	return (0);
}

int	count_quote(char *str, int *i, char quote_type)
{
	int	count;

	count = 1;
	(*i)++;
	while (str[*i])
	{
		while (str[*i] && str[*i] != quote_type)
			(*i)++;
		if (str[*i] == quote_type)
		{
			count++;
			(*i)++;
		}
	}
	return (count);
}
