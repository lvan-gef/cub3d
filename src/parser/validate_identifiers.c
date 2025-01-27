/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_identifiers.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:37 by tosinga       #+#    #+#                 */
/*   Updated: 2024/11/25 19:20:51 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	validate_paths(char **elements, t_program *program)
{
	size_t	index;

	index = 0;
	while (index < MAX_IMGS)
	{
		program->paths[index] = ft_strtrim(elements[index], WHITESPACE);
		if (program->paths[index] == NULL)
		{
			ft_putendl_fd("Path is NULL", 2);
			return (false);
		}
		if (_check_png(elements[index]) != true)
			return (false);
		index++;
	}
	return (true);
}

static	bool	_convert_digits(char **input, uint32_t *color)
{
	int	i;
	int	colors[3];

	i = 0;
	while (i < 3)
	{
		colors[i] = _atorgb(input[i]);
		if (colors[i] < 0)
			return (false);
		i++;
	}
	*color = (uint32_t)
		(colors[0] << 24 | colors[1] << 16 | colors[2] << 8 | 255);
	return (true);
}

static	bool	_convert_rgb(const char *input, uint32_t *color)
{
	char	**elements;
	size_t	input_len;

	input_len = ft_strlen(input);
	if (input[input_len - 1] == ',')
		return (false);
	elements = ft_split(input, ',');
	if (elements == NULL)
	{
		ft_putendl_fd("Failed to split rgb", 2);
		return (false);
	}
	if (_check_rgb_input(elements) != true)
	{
		free_char_arr(elements);
		return (false);
	}
	if (_convert_digits(elements, color) != true)
	{
		free_char_arr(elements);
		return (false);
	}
	free_char_arr(elements);
	return (true);
}

bool	validate_rgb_input(char **elements, t_program *program)
{
	if (_convert_rgb(elements[F], &program->player->floor_color) != true)
	{
		ft_putendl_fd("Invalid RGB format", 2);
		return (false);
	}
	if (_convert_rgb(elements[C], &program->player->ceiling_color) != true)
	{
		ft_putendl_fd("Invalid RGB format", 2);
		return (false);
	}
	return (true);
}

bool	validate_nr_of_identifiers(char **elements)
{
	size_t	index;

	index = 0;
	while (index < SIZE)
	{
		if (elements[index] == NULL)
		{
			ft_putstr_fd("Missing object input\n", 2);
			return (false);
		}
		index++;
	}
	return (true);
}
