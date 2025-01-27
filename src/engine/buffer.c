/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buffer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:22:01 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/23 17:47:55 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	_set_floor_ceiling(uint32_t **buffer, t_dda *dda, \
							const t_player *player, size_t col)
{
	int32_t	row;

	row = 0;
	while (row < dda->line.start && row < SCR_HEIGHT)
	{
		buffer[row][col] = player->ceiling_color;
		row++;
	}
	row = dda->line.end + 1;
	if (row <= 0)
	{
		return ;
	}
	while (row < SCR_HEIGHT)
	{
		buffer[row][col] = player->floor_color;
		row++;
	}
}

void	fill_buffer(t_mlx_state *mlx_state, t_dda *dda, \
					const t_player *player, size_t col)
{
	_set_floor_ceiling(mlx_state->img_buffer, dda, player, col);
	textures(mlx_state, dda, col);
}
