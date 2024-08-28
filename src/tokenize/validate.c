

#include "../include/minishell.h"

void validate_input(t_minishell *mini)
{
// ' '
// ""
// ()
// \
// 
	if ((double_quotes_closed(mini->input) != 1) 
		|| (single_quotes_closed(mini->input) != 1) 
		||	(parenthesis_closed(mini->input) != 1))

		ft_printf("%s\n", "DEU CERTO!!");
}

int	double_quotes_closed(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;

	while(str[i])
	{
		if(str[i] == '"')
			quote++;
		i++;
	}
	if (quote % 2 == 0)
		return(1);
	return(0);
}

int	single_quotes_closed(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;

	while(str[i])
	{
		if(str[i] == '\'')
			quote++;
		i++;
	}
	if (quote % 2 == 0)
		return(1);
	return(0);
}

int	parenthesis_closed(char *str)
{
	int	i;
	int	paren;
	int	thesis;

	i = 0;
	paren = 0;
	thesis = 0;

	while(str[i])
	{
		if(str[i] == '"')
		{
			i++;
			while(str[i] != '"')
				i++;
		}
		if(str[i] == '\'')
		{
			i++;
			while(str[i] != '\'')
				i++;
		}
		if(str[i] == '(')
			paren++;
		if(str[i] == ')')
			thesis++;
		i++;	
	}
	if (paren == thesis)
		return(1);
	return(0);
}