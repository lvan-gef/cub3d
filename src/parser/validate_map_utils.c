/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:41 by tosinga       #+#    #+#                 */
/*   Updated: 2024/11/25 19:22:17 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static	bool	_is_player(char map_pos)
{
	if (ft_strchr(PLAYER_POS, map_pos) != NULL)
		return (true);
	return (false);
}

bool	_check_chars(const char *map, char *start_dir)
{
	size_t		index;

	index = 0;
	while (map[index] != '\0')
	{
		if (_is_player(map[index]))
		{
			if (*start_dir == '\0')
				*start_dir = map[index];
			else
			{
				ft_putendl_fd("To many players!", 2);
				return (false);
			}
			index++;
		}
		if (ft_strchr(VALID_MAP_CHARS, map[index]) == NULL)
		{
			ft_putendl_fd("Invalid map: wrong character input", 2);
			return (false);
		}
		index++;
	}
	return (true);
}

bool	_create_map(t_program *program)
{
	t_player	*player;
	size_t		index;

	player = program->player;
	player->map = ft_calloc(player->max_map.row + 1, sizeof(*player->map));
	if (player->map == NULL)
	{
		ft_putendl_fd("Failed to calloc the rows", 2);
		return (false);
	}
	index = 0;
	while (index < player->max_map.row)
	{
		player->map[index] = ft_calloc(
				player->max_map.col + 1, sizeof(*player->map[index]));
		if (player->map[index] == NULL)
		{
			ft_putendl_fd("Failed to calloc the cols...", 2);
			return (false);
		}
		index++;
	}
	return (true);
}

bool	_set_map(t_player *player, char **temp_map)
{
	size_t		row;
	const char	*line;

	row = 0;
	while (row < player->max_map.row)
	{
		line = temp_map[row];
		if (line != NULL)
		{
			ft_memset(player->map[row], ' ', (int32_t)player->max_map.col);
			ft_memcpy(player->map[row], line, ft_strlen(line));
		}
		else
			player->map[row] = NULL;
		row++;
	}
	return (true);
}
