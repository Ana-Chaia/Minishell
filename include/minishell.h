/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacaro5 <anacaro5@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:06:03 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/17 09:46:12 by anacaro5         ###   ########.fr       */
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
# include <sys/stat.h>

#include <fcntl.h>   // Para O_CREAT, O_RDWR, O_TRUNC
#include <errno.h>   // Para errno
#include <string.h>  // Para strerror
#include <sys/types.h>  // Para open
#include <termios.h>
#include <signal.h>

typedef struct termios	t_termios;

extern volatile int g_signal;

//main
int		shellzito_on(t_minishell *mini);
void	init_struct(t_minishell *mini);

//tokenize
	//syntax
int		check_syntax(t_token **token_list);
int		pipe_syntax(t_token *token_node);
int		chevron_syntax(t_token *token_node);
	//parsing
void	malloc_cmd_args(t_token *united);
void	change_type(t_token *united);
t_token	*all_together(t_token **token_list);
t_token *clear_list(t_token **token_list);
	//token
void	token_type(char *input, t_token **list);
t_token	*create_node(char *input, int type, int idx, int flag);
int		make_lst(t_token **token_list, t_token *token_node, int idx, int flag);
int		token_d_quotes(t_token **token_list, int idx, char *input);
int		token_s_quotes(t_token **token_list, int idx, char *input);
void 	validate_quote_issue(t_token **token_list, size_t start,
			size_t end,	char *input);
int		token_word(t_token **token_list, int idx, char *input);
int		is_space(char c);
	//validate
int		validate_input(t_minishell *mini);
int		quotes_closed(char *str);
void	invalid_input(char c);

//heredoc
void	search_heredoc(t_token **token_list);
void	is_heredoc(t_token *token_node);
char	*create_file_name(void);
void	filling_a_file(int fd_heredoc, t_token *token_node, int std_in);
int		ft_strcmp(const char *s1, const char *s2);

//ast
t_token	*pipe_to_ast(t_token *tokenlist);
t_token	*redir_to_ast(t_token *tokenlist);
t_token	*find_last_one(t_token *tokenlist);
t_ast	*ast_new_node(t_token *token_node);
int		is_redirect(int curr);
t_ast	*ast_builder(t_ast *ast_node, t_token *tokenlist, int level);


//expand_variable
void	across_the_universe(t_token **token_list);
char	*find_dollar(char *cmd);
char	*change_dollar(char *cmd, int start, int end);
char	*cut_value(char *name, char **env);
//char	*ft_strxcpy(char *dest, char *src, size_t destsize);
//char 	*not_expanded(char *cmd, int i, char *temp);

//env
void	copy_env(void);
void	free_env(char **array);
char	**env_shellzito(char **our_env);

//builtin
    //cd
int		cd(char **cmd);
char	*get_path(char *path);
void	vars_to_env(char *old_pwd, char *pwd);
    //echo
int		echo(char **cmd);
int		check_minus_nnnns(char *cmd);
    //env
int		env(char **cmd);
    //exit
int		the_exit(char **cmd, t_minishell *mini);
int		verify_args(char **cmd);
int		is_sign(char c);
int		is_longer(char *cmd);
    //export
int		export(char **token, t_minishell *mini);
char	*substr_noquote(char const *s, unsigned int start, size_t len);
void	print_export(char **copy);
int		list_export(char *token, t_export **export_list);
int		validate_name(char *token);
int		compare_to_env(char *name);
t_export	*create_node_exp(char *name, char *value, int on_env, char equal);
void	make_lst_exp(t_export **export_list, t_export *export_node);
void	all_you_need_is_env(t_export *export_list, int i);
char	**come_together_env(char **new_env, t_export *curr);
char	**strawberry_fields_forenv(char **env, int i);
char	*join_env(char const *s1, char const *s2);
    //pwd
int		pwd(void);
    //unset
int		unset(char **cmd);
void	delete_variable(char *var);

//signal
void	init_signal(void);
void	signal_handler(int signal);
void	signal_main(void);
void	ctrld(int fd_heredoc, t_token *token_node, int std_in);
void	signal_handler_heredoc(int signal);
void	init_signal_exec(void);
void	signal_handler_exec(int signal);
void	signal_exec(int pid);
//void	init_signal_heredoc(int fd_heredoc);

//exec
void	execution(t_ast *node, t_minishell *mini);
int		is_builtin(char *cmd);
int		get_status(int exit_status);
    //pipe
int		execute_pipe(t_ast *node, t_minishell *mini);
void	child_process(int *task, t_ast *node, int nb_pid, t_minishell *mini);
    //builtin
int		execute_builtin(t_ast *node, t_minishell *mini);
    //redirect
int		execute_redirect(t_ast *node, t_minishell *mini);
int		open_file(t_ast *node, int *svd_stdin, int *svd_stdout);
int		dup_dup(t_ast *node, int *fd);
    //others
int		execute_others(t_ast *node);
void	validate_cmd(char *cmd);
//void	get_cmd(t_ast *node);
char	**split_path(void);
int		gone_wrong(t_ast *node);
int		is_directory(const char *path);
void	wise_status(int status);

//free and close
void	free_tokenlist(t_token *tokenlist);
void	free_export(t_export *export_list);
void	free_ast(t_ast *ast_node);
void	free_mini(t_minishell *mini);
void	free_ptrptr(char **env);
void	bye_bye(t_minishell *mini);
void	close_fds(int fd_bckp);

//printer
void	print_tree(t_ast *root, int nivel);
void	print_env_copy(char **copy);
int		list_size(t_token *list);
void	list_printer(t_token *list);

#endif