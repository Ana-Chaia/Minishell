/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbolanho <jbolanho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:15:05 by anacaro5          #+#    #+#             */
/*   Updated: 2024/12/18 12:46:29 by jbolanho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	the_exit(char **cmd, t_minishell *shellzito)
{
	int		i;
	int		count;
	int		status;

	status = get_status(-1);  ///get_status
	count = 0;
	i = 1;
	while (cmd[i] != NULL)
	{
		while (cmd[count] != NULL)
			count++;
		//printf("cmd[count - 1]: %s\n", cmd[count - 1]);
		//printf("count: %d\n", count);
		if (count == 2)
		{
			if (verify_args(&cmd[1]) == 1)
				exit(2);
			else
			{
				status = ft_atoi(cmd[1]);
				//printf("exit deu certo, status = %d\n", status);   //acertar print   "exit"
				status = mod_status(status);
				exit(status);  // ajustar get status?? 
			}
		}
		else
		{
			if (verify_args(&cmd[1]) == 1)
				exit(2);
			ft_printf_fd(STDERR_FILENO, "exit: too many arguments\n");
			//printf("shellzito: exit: %s: too many arguments \n", cmd[i]);
			exit(1);
		}
		i++;
	}
	if (cmd[0] && cmd[1] == NULL)
	{
		bye_bye(shellzito);
		status = mod_status(status);
		//free_ptrptr(cmd);
		exit(status); //pegar o status de final do último cmd, salvar na struct e receber ela;
	//obs: DAR FREE EM TUDO E FECHAR TODOS FDS antes de todos os exits;
	}
	return (0);
}

int	mod_status(int status)
{
	int		result;

	if (status >= 0 && status <= 255)
		return (status);
	result = status % 256;
	if (status < 0)
		result += 256;
	return (result);
}

int	verify_args(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i][j])
	{
		if (is_sign(cmd[i][j]) == 1)
			j++;
		//printf("cmd[%d][%d]: %c\n", i, j, cmd[i][j]);
		if (ft_isdigit(cmd[i][j]) == 0)
		{
			ft_printf_fd(STDERR_FILENO, "exit: numeric argument required\n");
			//printf("shellzito: exit: %s: numeric argument required\n",
				//cmd[i]);
			return (1);
		}
		if (is_longer(cmd[i]) == 1)
			return (1);
		j++;
	}
	return (0);
}

int	is_sign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

int	is_longer(char *cmd)
{
	if ((ft_strlen(cmd) == 19 && ft_strncmp(cmd, "9223372036854775807", 19) > 0)
		|| ((ft_strlen(cmd) == 20 && ft_strncmp(cmd, "-9223372036854775808", 20)
				> 0)))
	{
		ft_printf_fd(STDERR_FILENO, "exit: numeric argument required\n");
		//printf("shellzito: exit: %s: numeric argument required\n", cmd);
		return (1);
	}
	return (0);
}
