
#ifdef TOKENIZE_H
# define TOKENIZE_H

/**
 * @brief:gmhkmg
 * @param:
 * @return:
 */
void validate_input(t_minishell mini->input);
int	double_quotes_closed(char *str);
int	single_quotes_closed(char *str);
int	parenthesis_closed(char *str);

#endif