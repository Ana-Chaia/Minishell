/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:06:03 by anacaro5          #+#    #+#             */
/*   Updated: 2024/11/28 12:11:53 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "struct.h"
# include "tokenize.h"
# include "redirect.h"
# include "ast.h"
# include "signal.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

#include <fcntl.h>   // Para O_CREAT, O_RDWR, O_TRUNC
#include <errno.h>   // Para errno
#include <string.h>  // Para strerror
#include <sys/types.h>  // Para open
#include <termios.h>
#include <signal.h>

typedef struct termios	t_termios;

extern volatile int g_signal;

int		shellzito_on(t_minishell *mini);
void	init_struct(t_minishell *mini);
void	clear_and_free(t_minishell *mini);
void	take_token(char *input);
void	free_tokenlist(t_token *tokenlist);
void	close_fds(int fd_bckp);
// apagar printer
//void	ft_tree_printer(t_ast *root);

//expand_variable
void	across_the_universe(t_token **token_list);
char	*find_dollar(char *cmd);
char	*change_dollar(char *cmd, int start, int end);
char	*cut_value(char *name, char **env);

//builtins
void	copy_env(void);
void	free_env(char **array);
char	**env_shellzito(char **our_env);

//int		call_builtins(char *token, t_export **export_list);
void	ft_free_split(char **cmd);

int		export(char **token);
// int	validate_export_name(char *token);
// int	validate_export_token2(char *token);
char	*substr_noquote(char const *s, unsigned int start, size_t len);
void	print_export(char **copy);
int		list_export(char *token, t_export **export_list);
int		validate_name(char *token);
int		compare_to_env(char *name);
t_export	*create_node_exp(char *name, char *value, int on_env, char equal);
void	make_lst_exp(t_export **export_list, t_export *export_node);
void	all_you_need_is_env(t_export **export_list, int i);
char	**come_together_env(char **new_env, t_export *curr);
char	**strawberry_fields_forenv(char **env, int i);
char	*join_env(char const *s1, char const *s2);

int		echo(char **cmd);
int		check_minus_nnnns(char *cmd);

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

//cd
int	    cd(char **cmd);
char    *get_path(char *path);
void	vars_to_env(char *old_pwd, char *pwd);

//env
int 	env(char **cmd);

//signal
void	init_signal(void);
void	signal_handler(int signal);
void	signal_exec(int pid);
void	signal_main(void);
void	ctrld(char *input, int fd_heredoc, t_token *token_node, int std_in);
void	init_signal_heredoc(int fd_heredoc);
void	signal_handler_heredoc(int signal);
void	init_signal_exec(void);
void	signal_handler_exec(int signal);

//exec
void    execution(t_ast *node);
int	    is_builtin(char *cmd);
int     execute_pipe(t_ast *node);
void    child_process(int *task, t_ast *node, int nb_pid);
int	    execute_builtin(char *token_tree);
int     get_status(int exit_status);


int	execute_redirect(t_ast *node);
int	open_file(t_ast *node, int *svd_stdin, int *svd_stdout);
int	dup_dup(t_ast *node, int *fd);

int	execute_others(t_ast *node);
void	validate_cmd(char *cmd);
char	**split_path(void);
void	get_cmd(t_ast *node);

#endif