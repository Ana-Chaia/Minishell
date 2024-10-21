

int	call_builtins(char *token)
{
	int	 	builtin;
	char	**cmd;

	builtin = -1;
	cmd = ft_split(token, ' ');
	if(!cmd || !cmd[0])
		return (builtin);	
	if (!ft_strcmp(cmd[0], "echo"))
		builtin = echo(cmd);
	else if (!ft_strcmp(cmd[0], "cd"))
		builtin = cd(cmd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		builtin = pwd(cmd);
	else if (!ft_strcmp(cmd[0], "export"))
		builtin = export(cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
		builtin = unset(cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		builtin = env(cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
		builtin = exit(cmd);
	ft_free_split(cmd);
	return (builtin);
}

/*
https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html
Output the args, separated by spaces, terminated with a newline. The return status is 0 unless a write error occurs. 
If -n is specified, the trailing newline is suppressed. 
If the -e option is given, interpretation of the following backslash-escaped characters is enabled. 
The -E option disables the interpretation of these escape characters, 
even on systems where they are interpreted by default. 
The xpg_echo shell option may be used to dynamically determine whether or 
not echo expands these escape characters by default. echo does not interpret -- to mean the end of options.

não vamos trabalhar com backslash, por isso ignorei o -e.
*/

int	echo(char **cmd)
{
	int	new_line;
	int	space;
	int i;

	i = 1;
	space = 0;
	new_line = 1;
	while(check_minus_nnnns(cmd[i]))
	{
		i++;
		new_line = 0;
	}
	while(cmd[i])
	{
		if (space)
			ft_putchar_fd (' ', 1);
		else
			space++;
		ft_putstr_fd (cmd[i++], 1);
	}
	if (new_line)
		ft_putchar_fd ('\n', 1);
	return (0)
}

int	check_minus_nnnns (char *cmd)
{
	int	i;

	if (cmd && !ft_strncmp(cmd, "-n", 2))
	{
		i = 2;
		while (cmd[i] == 'n')
			i++;
		if (!cmd[i])
			return (1);
	}
	return (0);
}

void ft_free_split(char **cmd)
{
	int i;

	i = 0;
	if (!cmd)
		return;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}
