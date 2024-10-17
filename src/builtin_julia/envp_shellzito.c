//na main tem que ter envp como variavel

void    copy_envp(char **envp)
{
    char    **our_env;
    int     i;

    i = 0;
    while(envp[i])
        i++;
    our_env = malloc(sizeof(char*) * (i + 1));
    i = 0;
    while (envp[i])
    {
        our_env[i] = ft_strdup(envp[i]);
        if (!our_env[i])
        {
            ft_free_list(&our_env);
            exit();
        }
    }
    our_env[i] = NULL;
    env_shellzito(our_env);
}

char    **env_shellzito(char **our_env)
{
    static char **env_shellzito;

    if(our_env && env_shellzito)
        ft_free_list(&env_shellzito);
    if(our_env)
        env_shellzito = our_env;
    return (env_shellzito);
}
