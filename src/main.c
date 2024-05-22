#include "../include/cub3d_parser.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include "../include/cub3d_structs.h"
#include "../libft/include/libft.h"

void	free_char_arr(char **arr)
{
	size_t	index;

	if (arr == NULL)
		return ;
	index = 0;
	while (arr[index] != NULL)
	{
		free(arr[index]);
		index++;
	}
	free(arr);
}

void	free_engine(t_program *program)
{
	if (program->render == NULL)
		return ;
	if (program->render->mlx != NULL)
	{
		if (program->render->image != NULL)
			mlx_delete_image(program->render->mlx, program->render->image);
		mlx_close_window(program->render->mlx);
		mlx_terminate(program->render->mlx);
	}
	free(program->render);
}

void	free_program(t_program *program)
{
	size_t	index;

	if (program == NULL)
		return ;
	index = 0;
	while (index < ASSETS_SIZE)
	{
		if (program->textures[index] != NULL)
			free(program->textures[index]);
		index++;
	}
	free_engine(program);
	if (program->map != NULL)
		free_char_arr(program->map);
	free(program);
}

int main(int argc, char *argv[])
{
    t_program	*program;
	int			exit_code;

    if (argc != 2) {
        print_error("Invalid argument(s)");
        exit(1);
    }
	exit_code = 0;
	program = ft_calloc(1, sizeof(*program));
	if (program == NULL)
	{
		exit_code = 2;
		ft_putendl_fd("Faled to create a placeholder for program", 2);
	}
	else if (parser(program, argv) != true)
		exit_code = 3;
	else if (init_game(program) != true)
		exit_code = 4;
	// else if (run_game(program) != true)
	// 	exit_code = 4;
	print_program(program);
	free_program(program);
    return (exit_code);
}
