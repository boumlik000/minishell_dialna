/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:07:17 by csouita           #+#    #+#             */
/*   Updated: 2024/10/21 12:24:07 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	ft_isdigit_parsing(int c)
{
	return (c >= '0' && c <= '9');
}
