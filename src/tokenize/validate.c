

#include "../include/minishell.h"

void validate_input(t_minishell mini->input);

// ' '
// ""
// ()
// \
// ;
{
	if ((double_quotes_closed(mini->input) != 1) 
		|| (single_quote_closed(mini->input) != 1) 
		||	(parenthesis_closed(mini->input) != 1))


}

int	double_quotes_closed(char *str)
{
	int	i;
	int	quote;

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