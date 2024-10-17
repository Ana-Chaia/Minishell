//export
//export [-fn] [-p] [name[=value]]
//Mark each name to be passed to child processes in the environment.
//If the -f option is supplied, the names refer to shell functions; otherwise the names refer to shell variables. 
//The -n option means to no longer mark each name for export. 
//If no names are supplied, or if the -p option is given, a list of names of all exported variables is displayed.
// The -p option displays output in a form that may be reused as input. 
//If a variable name is followed by =value, the value of the variable is set to value.

//The return status is zero unless an invalid option is supplied, one of the names is not a valid shell variable name,
// or -f is supplied with a name that is not a shell function.


int export(char **token)
{
	int		i;
	char	*equal;
	char	*arg;

	i = 0;
	if (!token[1] || (token[1] == "-p" && !token[2]))
		print_all_env ();
	else


}

void	print_all_env(void)
{
	char		**env;
    size_t		i;
	char    	*print;
    int         position;

	env = env_shellzito(NULL);
	i = 0;
	while (env[i])
		i++;

}

