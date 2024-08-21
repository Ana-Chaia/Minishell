
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "struct.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>


void	init_struct(t_minishell *mini);
void	clear_and_free(t_minishell *mini);
void	take_token(char *input);

#endif