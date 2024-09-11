

#include "../include/minishell.h"

void	validate_input(t_minishell *mini)
{
	if ((double_quotes_closed(mini->input) != 42)
		|| (single_quotes_closed(mini->input) != 42)
		|| (parenthesis_closed(mini->input) != 42))
		ft_printf("%s\n", "DEU RUIM!!");
	if (not_oblig_backslash(mini->input) != 42)
		ft_printf("%s\n", "DEU errado backslash!!");
}

int	double_quotes_closed(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '"')
			quote++;
		i++;
	}
	if (quote % 2 == 0)
		return (42);
	return (0);
}

int	single_quotes_closed(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			quote++;
		i++;
	}
	if (quote % 2 == 0)
		return (42);
	return (0);
}

// int	parenthesis_closed(char *str)
// {
// 	int	i;
// 	int	paren;
// 	int	thesis;

// 	i = 0;
// 	paren = 0;
// 	thesis = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '"')
// 		{
// 			i++;
// 			while (str[i] != '"')
// 				i++;
// 		}
// 		if (str[i] == '\'')
// 		{
// 			i++;
// 			while (str[i] != '\'')
// 				i++;
// 		}
// 		if (str[i] == '(')
// 			paren++;
// 		if (str[i] == ')')
// 			thesis++;
// 		i++;
// 	}
// 	if (paren == thesis)
// 		return (42);
// 	return (0);
// }

// int parenthesis_closed(char *str)
// {
//     int i;
//     int in_double_quotes;
//     int in_single_quotes;

//     i = 0;
//     in_double_quotes = 0;
//     in_single_quotes = 0;

//     while (str[i])
//     {
//         if (str[i] == '"')
//         {
//             in_double_quotes = !in_double_quotes;
//             i++;
//             continue;
//         }
//         if (str[i] == '\'')
//         {
//             in_single_quotes = !in_single_quotes;
//             i++;
//             continue;
//         }
//         if ((str[i] == '(' || str[i] == ')') && !in_double_quotes && !in_single_quotes)
//             return 1;  // Retorna 1 se encontrar '(' ou ')' fora de aspas
//         i++;
//     }
//     return 0;  // Retorna 0 se não encontrar nenhum '(' ou ')' fora de aspas
// }


int parenthesis_closed(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')int parenthesis_closed(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] == '"')
				i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\'')
				i++;
		}
		else if (str[i] == '(' || str[i] == ')')
			return (1);  // Retorna 1 se encontrar '(' ou ')' fora de aspas
		else
			i++;
	}
	return (42);  // Retorna 0 se não encontrar nenhum '(' ou ')' fora de aspas
}
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\'')
				i++;
		}
		else if (str[i] == '(' || str[i] == ')')
		{
			return 1;  // Retorna 1 se encontrar '(' ou ')' fora de aspas
		}
		else
		{
			i++;
		}
	}
	return 0;  // Retorna 0 se não encontrar nenhum '(' ou ')' fora de aspas
}

int	not_oblig_backslash(char *str)
{
	int	i;
	int	bkslsh;

	i = 0;
	bkslsh = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '\\')
			bkslsh++;
		i++;
	}
	if (bkslsh == 0)
		return (42);
	return (0);
}
