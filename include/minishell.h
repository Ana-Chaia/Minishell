
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "struct.h"
# include "tokenize.h"
# include "redirect.h"
# include "ast.h"

# include <readline/readline.h>
# include <readline/history.h>
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

int	call_builtins(char *token);
void	ft_free_split(char **cmd);

int	export(char **token);
int	validate_export_name(char *token);
int	validate_export_token2(char *token);
char	*substr_noquote(char const *s, unsigned int start, size_t len);
void	print_export(char **copy);

//printers
void	print_env_copy(char **copy);
void	free_env(char **array);



#endif