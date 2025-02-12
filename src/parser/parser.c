/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.42.fr>              +#+                   */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:37 by lvan-gef       #+#    #+#                */
/*   Updated: 2024/11/21 20:33:30 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static	bool	_free_parser(char **elements, bool state)
{
	size_t	row;

	if (elements != NULL)
	{
		row = 0;
		while (row <= SIZE)
		{
			if (elements[row] != NULL)
				free(elements[row]);
			row++;
		}
		free(elements);
	}
	if (state == false)
		ft_putendl_fd("Error\nWhile parsing file.", 2);
	return (state);
}

bool	parser(char *arg, t_program *program)
{
	char		**elements;

	if (check_cub(arg) != true)
		return (_free_parser(NULL, false));
	elements = tokenize_input(arg);
	if (errno != 0 || elements == NULL)
		return (_free_parser(elements, false));
	if (validate_nr_of_identifiers(elements) != true)
		return (_free_parser(elements, false));
	if (validate_paths(elements, program) != true)
		return (_free_parser(elements, false));
	if (validate_rgb_input(elements, program) != true)
		return (_free_parser(elements, false));
	if (validate_map(elements[SIZE], program) != true)
		return (_free_parser(elements, false));
	return (_free_parser(elements, true));
}
