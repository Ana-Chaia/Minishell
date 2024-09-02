
#ifndef TOKENIZE_H
# define TOKENIZE_H

/**
 * @brief:gmhkmg
 * @param:
 * @return:
 */
void	validate_input(t_minishell *mini);
int		double_quotes_closed(char *str);
int		single_quotes_closed(char *str);
int		parenthesis_closed(char *str);
int		not_oblig_backslash(char *str);

#endif