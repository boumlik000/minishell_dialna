/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:53:48 by csouita           #+#    #+#             */
/*   Updated: 2024/10/21 12:31:42 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"




void    handle_sigint(int sig)
{
    (void)sig;
    write(2, "\n", 1);
    rl_replace_line("",0);
    rl_on_new_line();
    rl_redisplay();
}

int	search_in_parsing(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

size_t ft_strlen_parsing(char *str)
{
    size_t i;
    
    i = 0;
	if(!str)
		return 0;
    while(str[i])
        i++;
    return i;
}


char	*ft_strdup_parsing(char *s1)
{
	int		i;
	char	*dest;

	if (!s1)
		return NULL;
	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen_parsing(s1) + 1));
	if (!dest)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr_parsing(char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen_parsing(s))
		return (ft_strdup_parsing("\0"));
	if (start + len >= ft_strlen_parsing(s))
		substr = malloc(sizeof(char) * (ft_strlen_parsing(s) - start + 1));
	else
		substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (s[start] && i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}

t_env *create_node_parsing(char *env)
{
    int i = 0;
    t_env *lst;
    char *key ;
    char *value;
    lst = malloc(sizeof(t_env));
    key = ft_substr_parsing(&env[i],0,search_in_parsing(env,'='));
    lst->key = key;
    value = ft_substr_parsing(&env[i],search_in_parsing(env,'=') + 1,ft_strlen_parsing(env));
    lst->value = value;
    lst->next = NULL;
    return lst;
}

t_env *get_last_node_parsing(t_env *head)
{
    if (!head)
        return NULL;
    while(head->next)
        head = head->next;
    return head;
}

void add_back_parsing(t_env **head ,t_env *new_content)
{
    t_env *last;
    if(!head || !new_content)
        return;
    if(*head)
    {
        last = get_last_node_parsing(*head);
        last->next = new_content;
    }
    else
        *head = new_content;
}

t_env *cp_env_in_liste_parsing(char **env)
{
    int i = 0;
    t_env *lst = 0;
    while(env[i])
    {
        add_back_parsing(&lst,create_node_parsing(env[i]));
        i++;
    }
    return lst;
}

int parsing(int ac ,char *av[], char **envr)
{
    (void)av;
    t_data data;
    t_env *env;
    // char *t_data->line;

    // env = cp_env_to_list(&env);
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
    if (ac != 1)
    {
        write(1,"Error in arguments",19);
        exit(1);
    }
    env = cp_env_in_liste_parsing(envr);
    // while(env)
    // {
    //     printf("%s=",env->key);
    //     printf("%s\n",env->value);
    //     env = env->next;
    // }
    
    while (data.line)
    {
        data.line = readline("minishell> ");
        // exit(1);
        // printf("%s\n",t_data.line);
        if (!data.line)
            break;
        add_history(data.line);
        lexer(&data);
        // display_token_lexer(data.head);
        if (syntax_error(&data) == 0)
        {
            ft_putstr_fd("syntax error\n",2);
            continue ;
        }
        expand(data.head, env);
        display_token_command(parser(&data));

        //
        
        
        // handel_quotes()
        
        // write(1,"\n",1);
    }
    return 0;
}
