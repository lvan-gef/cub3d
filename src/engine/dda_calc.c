/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dda_calc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:22:13 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/25 19:58:14 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static	void	_set_dir(t_dda *dda)
{
	if (dda->ray_dir.col < 0)
	{
		dda->step_map.col = -1;
		dda->side_dist.col = (dda->player_pos.col - dda->map_pos.col) * \
			dda->delta_dist.col;
	}
	else
	{
		dda->step_map.col = 1;
		dda->side_dist.col = (dda->map_pos.col + 1.0 - dda->player_pos.col) * \
			dda->delta_dist.col;
	}
	if (dda->ray_dir.row < 0)
	{
		dda->step_map.row = -1;
		dda->side_dist.row = (dda->player_pos.row - dda->map_pos.row) * \
			dda->delta_dist.row;
	}
	else
	{
		dda->step_map.row = 1;
		dda->side_dist.row = (dda->map_pos.row + 1.0 - dda->player_pos.row) * \
			dda->delta_dist.row;
	}
}

static	void	_find_wall(t_dda *dda, t_player *player)
{
	while (1)
	{
		if (dda->side_dist.col < dda->side_dist.row)
		{
			dda->side_dist.col += dda->delta_dist.col;
			dda->map_pos.col += dda->step_map.col;
			dda->current_side = X_SIDE;
		}
		else
		{
			dda->side_dist.row += dda->delta_dist.row;
			dda->map_pos.row += dda->step_map.row;
			dda->current_side = Y_SIDE;
		}
		if (hit_wall(player->map, dda->map_pos.row, dda->map_pos.col))
			break ;
	}
}

void	_set_lines(t_dda *dda)
{
	if (dda->current_side == X_SIDE)
		dda->perp_wall_dist = (dda->map_pos.col - dda->player_pos.col + \
			(1.0 - (double)dda->step_map.col) / 2.0) / dda->ray_dir.col;
	else
		dda->perp_wall_dist = (dda->map_pos.row - dda->player_pos.row + \
			(1.0 - (double)dda->step_map.row) / 2.0) / dda->ray_dir.row;
	if (dda->perp_wall_dist == 0)
		dda->line.heigth = SCR_HEIGHT;
	else
		dda->line.heigth = (int)(SCR_HEIGHT / dda->perp_wall_dist);
	dda->line.start = (SCR_HEIGHT / 2) - (dda->line.heigth / 2);
	dda->line.end = (SCR_HEIGHT / 2) + (dda->line.heigth / 2);
}

bool	hit_wall(char **map, int32_t row, int32_t col)
{
	return (map[row][col] == '1');
}

void	dda_info(t_dda *dda, t_player *player, size_t col)
{
	dda->camera_col = 2 * ((double)col / (double)SCR_WIDTH) - 1;
	dda->ray_dir.col = dda->player_dir.col + (dda->plane.col * dda->camera_col);
	dda->ray_dir.row = dda->player_dir.row + (dda->plane.row * dda->camera_col);
	dda->map_pos.col = (int32_t)dda->player_pos.col;
	dda->map_pos.row = (int32_t)dda->player_pos.row;
	if (dda->ray_dir.col == 0)
		dda->delta_dist.col = (double)INFINITY;
	else
		dda->delta_dist.col = fabs(1 / dda->ray_dir.col);
	if (dda->ray_dir.row == 0)
		dda->delta_dist.row = (double)INFINITY;
	else
		dda->delta_dist.row = fabs(1 / dda->ray_dir.row);
	_set_dir(dda);
	_find_wall(dda, player);
	_set_lines(dda);
}
