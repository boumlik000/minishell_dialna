/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:37:02 by csouita           #+#    #+#             */
/*   Updated: 2024/10/21 12:17:14 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"




void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL || fd == -1)
	{
		return ;
	}
	write(fd, s, ft_strlen_parsing(s));
}


char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (s[i] != (char)c)
	{
		if (str[i] == '\0')
			return (NULL);
		i++;
	}
	return (str + i);
}


// int main(int argc, char const *argv[])
// {
//     printf("%s\n",ft_strchr("souita",'i'));
//     return 0;
// }
