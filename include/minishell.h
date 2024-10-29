
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "struct.h"
# include "tokenize.h"
# include "redirect.h"
# include "ast.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

#include <fcntl.h>   // Para O_CREAT, O_RDWR, O_TRUNC
#include <errno.h>   // Para errno
#include <string.h>  // Para strerror

void	init_struct(t_minishell *mini);
void	clear_and_free(t_minishell *mini);
void	take_token(char *input);
void	free_tokenlist(t_token *tokenlist);
// apagar printer
//void	ft_tree_printer(t_ast *root);

//builtins
void	copy_env(void);
void	free_env(char **array);
char	**env_shellzito(char **our_env);

int	call_builtins(char *token, t_export **export_list);
void	ft_free_split(char **cmd);

int	export(char **token, t_export **export_list);
// int	validate_export_name(char *token);
// int	validate_export_token2(char *token);
char	*substr_noquote(char const *s, unsigned int start, size_t len);
void	print_export(char **copy);
int		list_export(char *token, t_export **export_list);
int	validate_name(char *token);
int	compare_to_env(char *name);
t_export	*create_node_exp(char *name, char *value, int on_env, char equal);
void	make_lst_exp(t_export **export_list, t_export *export_node);
void	all_you_need_is_env(t_export **export_list, int i);
char	**come_together_env(char **new_env, t_export *curr);
char	**strawberry_fields_forenv(char **env, int i);
char	*join_env(char const *s1, char const *s2);

//printers
void	print_env_copy(char **copy);
// void	free_env(char **array);

//unset
int		unset(char **cmd);
void	delete_variable(char *var);

//pwd
int		pwd(void);

//exit
int		the_exit(char **cmd);
int		verify_args(char **cmd);
int		is_sign(char c);
int		is_longer(char *cmd);

#endif