
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

void	token_type(char *input, t_token **list);
t_token	*create_node(char *input, int type, int idx, int flag);
int		make_lst(t_token **token_list, t_token *token_node, int idx, int flag);
int		token_word(t_token **token_list, int idx, char *input);
int		is_space(char c);

int		list_size(t_token *list);
void	list_printer(t_token *list);


int		token_d_quotes(t_token **token_list, int idx, char *input);
int		token_s_quotes(t_token **token_list, int idx, char *input);
int		parenthesis_exists(char *str);
int		quotes_closed(char *str);
void	invalid_input(char c);


int		check_syntax(t_token **token_list);
int		pipe_syntax(t_token *token_node);
int		chevron_syntax(t_token *token_node);

void	change_type(t_token *united);
t_token	*all_together(t_token **token_list);
t_token *clear_list(t_token **token_list);

void validate_quote_issue(t_token **token_list, size_t start,
	size_t end,	char *input);

#endif