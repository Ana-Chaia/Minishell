/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:28:44 by jbolanho          #+#    #+#             */
/*   Updated: 2024/09/13 09:30:05 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	validate_input(t_minishell *mini)
{
	if ((quotes_closed(mini->input) != 42))
		ft_printf("%s\n", "DEU RUIM!!");
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
		{
			d_quote++;
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] == '"')
			{
				d_quote++;
				i++;
			}		
		}
		else if (str[i] == '\'')
		{
			s_quote++;
				i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\'')
			{
				s_quote++;
				i++;
			}	
		}
		else
		{
			invalid_input(str[i]);
			i++;
		}	
	}
	printf("s_quote:%d\n", s_quote);
	printf("d_quote:%d\n", d_quote);
	if ((s_quote % 2 == 0) && (d_quote % 2 == 0))
		return (42);
	return (0);
}

void	invalid_input(char c)
{
	if ((c == '(') || (c == ')') || (c == '\\') || (c == ';'))
		ft_printf("%s\n", "muito RUIM!!");
}
