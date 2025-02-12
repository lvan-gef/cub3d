/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_ident_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.42.fr>              +#+                   */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:37 by lvan-gef       #+#    #+#                */
/*   Updated: 2024/11/21 21:19:01 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	_check_rgb_input(char **elements)
{
	size_t		index;
	char		*temp;

	index = 0;
	while (elements[index] != NULL)
		index++;
	if (index != 3)
		return (false);
	index = 0;
	while (elements[index])
	{
		temp = ft_strtrim(elements[index], WHITESPACE);
		if (temp == NULL)
		{
			ft_putendl_fd("Faield to trim", 2);
			return (false);
		}
		free(elements[index]);
		elements[index] = temp;
		index++;
	}
	return (true);
}
