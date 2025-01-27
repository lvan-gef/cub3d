/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:23:54 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/23 17:48:41 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static	void	_print_error(const char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
}

static	bool	_init_buffer(t_mlx_state *mlx_state)
{
	size_t	row;

	mlx_state->img_buffer = ft_calloc(
			SCR_HEIGHT + 1, sizeof(*mlx_state->img_buffer));
	if (mlx_state->img_buffer == NULL)
	{
		_print_error("Failed to create placeholder for img buffer");
		return (false);
	}
	row = 0;
	while (row < SCR_HEIGHT)
	{
		mlx_state->img_buffer[row] = ft_calloc(
				SCR_WIDTH + 1, sizeof(*mlx_state->img_buffer[row]));
		if (mlx_state->img_buffer[row] == NULL)
		{
			_print_error("Failed to create placeholder for img buffer col");
			return (false);
		}
		row++;
	}
	return (true);
}

static	bool	_init_texture(t_mlx_state *mlx_state, char **paths)
{
	size_t	index;

	index = 0;
	while (index < MAX_IMGS)
	{
		mlx_state->textures[index] = mlx_load_png(paths[index]);
		if (mlx_state->textures[index] == NULL)
		{
			_print_error(mlx_strerror(mlx_errno));
			return (false);
		}
		index++;
	}
	return (true);
}

static	bool	_init_mlx(t_program *p)
{
	p->mlx_state = ft_calloc(1, sizeof(*p->mlx_state));
	if (p->mlx_state == NULL)
	{
		_print_error("init mlx_state");
		return (false);
	}
	p->mlx_state->mlx = mlx_init(SCR_WIDTH, SCR_HEIGHT, "cub3D", false);
	if (!p->mlx_state->mlx)
	{
		_print_error(mlx_strerror(mlx_errno));
		return (false);
	}
	p->mlx_state->img = mlx_new_image(p->mlx_state->mlx, SCR_WIDTH, SCR_HEIGHT);
	if (!p->mlx_state->img)
	{
		_print_error(mlx_strerror(mlx_errno));
		return (false);
	}
	if (mlx_image_to_window(p->mlx_state->mlx, p->mlx_state->img, 0, 0) == -1)
	{
		_print_error(mlx_strerror(mlx_errno));
		return (false);
	}
	return (true);
}

bool	init_mlx(t_program *program)
{
	if (_init_mlx(program) != true)
		return (false);
	if (_init_buffer(program->mlx_state) != true)
		return (false);
	if (_init_texture(program->mlx_state, program->paths) != true)
		return (false);
	return (true);
}
