/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.42.fr>              +#+                   */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:37 by lvan-gef       #+#    #+#                */
/*   Updated: 2024/11/25 19:21:38 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static	ssize_t	check_characters(const char *map, const char *positions[])
{
	ssize_t				index;
	char				start_dir;

	start_dir = '\0';
	if (_check_chars(map, &start_dir) != true)
	{
		return (-1);
	}
	if (start_dir == '\0')
	{
		ft_putendl_fd("No player found in map!", 2);
		return (-1);
	}
	index = 0;
	while (positions[index])
	{
		if (*positions[index] == start_dir)
			break ;
		index++;
	}
	return (index);
}

static	bool	set_map_size(char **map, t_program *program)
{
	size_t	index;
	size_t	col_len;

	index = 0;
	while (map[index] != NULL)
	{
		program->player->max_map.row++;
		col_len = ft_strlen(map[index]);
		if (col_len > program->player->max_map.col)
			program->player->max_map.col = col_len;
		index++;
	}
	if (program->player->max_map.row < 3)
		return (false);
	return (true);
}

static	bool	fill_map(const char *map, t_program *program)
{
	char		**temp_map;

	temp_map = ft_split(map, '\n');
	if (temp_map == NULL)
	{
		ft_putstr_fd("Failed to split the map\n", 2);
		return (false);
	}
	if (set_map_size(temp_map, program) != true)
	{
		ft_putendl_fd("Map is to small to play...", 2);
		return (false);
	}
	if (_create_map(program) != true)
	{
		free_char_arr(temp_map);
		return (false);
	}
	if (_set_map(program->player, temp_map) != true)
		return (false);
	free_char_arr(temp_map);
	return (true);
}

static	bool	fill_player(t_program *program)
{
	size_t	col;
	size_t	row;

	row = 0;
	while (row < program->player->max_map.row)
	{
		col = 0;
		while (col < program->player->max_map.col)
		{
			if (ft_strchr(PLAYER_POS, program->player->map[row][col]) != NULL)
			{
				program->player->player_pos.col = (double)col;
				program->player->player_pos.row = (double)row;
				return (true);
			}
			col++;
		}
		row++;
	}
	ft_putstr_fd("Failed to find player position\n", 2);
	return (false);
}

bool	validate_map(const char *map, t_program *program)
{
	ssize_t				pos;
	static const char	*positions[] = {"N", "S", "W", "E", NULL};

	pos = check_characters(map, positions);
	if (pos == -1)
		return (false);
	program->player->starting_dir = *positions[pos];
	if (fill_map(map, program) != true)
		return (false);
	if (fill_player(program) != true)
		return (false);
	if (_check_surrounded_walls(program->player->map) != true)
	{
		ft_putendl_fd("Invalid map", 2);
		return (false);
	}
	return (true);
}
