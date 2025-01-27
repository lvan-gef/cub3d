/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:22:13 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/23 20:33:27 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static uint32_t	_get_pixel_value(t_mlx_state *mlx_state, \
								t_uvector tc, \
								int32_t ti)
{
	const uint8_t	*pixels;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;

	pixels = mlx_state->textures[ti]->pixels;
	r = pixels[(tc.row * mlx_state->textures[ti]->width + tc.col) * 4];
	g = pixels[(tc.row * mlx_state->textures[ti]->width + tc.col) * 4 + 1];
	b = pixels[(tc.row * mlx_state->textures[ti]->width + tc.col) * 4 + 2];
	a = pixels[(tc.row * mlx_state->textures[ti]->width + tc.col) * 4 + 3];
	return ((uint32_t)(r << 24 | g << 16 | b << 8 | a));
}

static t_uvector	_get_tex_cords(t_mlx_state *mlx_state, \
								t_dda *dda, \
								int32_t ti)
{
	double		wall_x;
	t_uvector	tex;

	tex.col = 0;
	tex.row = 0;
	if (dda->current_side == X_SIDE)
		wall_x = dda->player_pos.row + dda->perp_wall_dist * dda->ray_dir.row;
	else
		wall_x = dda->player_pos.col + dda->perp_wall_dist * dda->ray_dir.col;
	wall_x -= (floor(wall_x));
	tex.col = (uint32_t)(wall_x * mlx_state->textures[ti]->width);
	if (ti == S_INDEX || ti == W_INDEX)
		tex.col = mlx_state->textures[ti]->width - tex.col - 1;
	return (tex);
}

static void	_set_textures(t_mlx_state *mlx_state, \
								t_dda *dda, \
								size_t col, \
								int32_t ti)
{
	t_uvector	tc;
	double		step;
	double		tex_pos;
	int32_t		row;

	tc = _get_tex_cords(mlx_state, dda, ti);
	step = 1.0 * (mlx_state->textures[ti]->height) / dda->line.heigth;
	tex_pos = 0;
	row = dda->line.start;
	while (row < 0)
	{
		tex_pos += step;
		row++;
	}
	while (row < SCR_HEIGHT && row <= dda->line.end)
	{
		tc.row = ((uint32_t)tex_pos) & ((mlx_state->textures[ti]->height) - 1);
		tex_pos += step;
		mlx_state->img_buffer[row][col] = _get_pixel_value(mlx_state, tc, ti);
		row++;
	}
}

static int32_t	_get_tex_index(const t_dda *dda)
{
	if (dda->current_side == X_SIDE && dda->ray_dir.col < 0)
		return ((int32_t)W_INDEX);
	else if (dda->current_side == X_SIDE && dda->ray_dir.col > 0)
		return ((int32_t)E_INDEX);
	else if (dda->current_side == Y_SIDE && dda->ray_dir.row < 0)
		return ((int32_t)N_INDEX);
	else
		return ((int32_t)S_INDEX);
}

void	textures(t_mlx_state *mlx_state, t_dda *dda, size_t col)
{
	int32_t	tex_index;

	tex_index = _get_tex_index(dda);
	_set_textures(mlx_state, dda, col, tex_index);
}
