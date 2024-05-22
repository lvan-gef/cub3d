#include "../../include/cub3d_engine.h"
#include "MLX42/MLX42.h"
#include "libft.h"

static	bool	load_assets(t_program *program)
{
	(void)program;
	size_t	index;

	index = 0;
	while (index < ASSETS_SIZE)
	{
		index++;
	}
	return (true);
}

bool    init_game(t_program *program)
{
	program->render = ft_calloc(1, sizeof(*program->render));
	if (program->render == NULL)
	{
		ft_putendl_fd("Failed to create a placeholder for program->render", 2);
		return (false);
	}
	program->render->mlx = mlx_init(1920, 1080, "cub3d", true);
	if (program->render->mlx == NULL)
	{
		ft_putendl_fd(mlx_strerror(mlx_errno), 2);
		return (false);
	}
	program->render->image = mlx_new_image(program->render->mlx, 1920, 1080);
	if (program->render->image == NULL)
	{
		ft_putendl_fd(mlx_strerror(mlx_errno), 2);
		return (false);
	}
	if (mlx_image_to_window(program->render->mlx, program->render->image, 0, 0) == -1)
	{
		ft_putendl_fd(mlx_strerror(mlx_errno), 2);
		return (false);
	}
	if (load_assets(program) != true)
		return (false);

	// add hooks
	mlx_loop(program->render->mlx);
    return (true);
}
