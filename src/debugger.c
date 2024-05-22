
#include "../include/cub3d_parser.h"

void	print_program(t_program *program)
{
	int row;
	int col;

	printf("\nmax y: %d, max x: %d\n", program->max_xy.col, program->max_xy.row);
	printf("player looking at: %d\n", program->spawning_pos);
	printf("player start xy: %d, %d\n", program->start_pos.col, program->start_pos.row);

	printf("map:\n");
	row = 0;
	while (row < program->max_xy.row)
	{
		col = 0;
		while (col < program->max_xy.col)
		{
			printf("%c", program->map[row][col]);
			col++;
		}
		printf("\n");
		row++;
	}

	printf("file paths:\n%s\n%s\n%s\n%s\n", program->textures[0], program->textures[1], program->textures[2], program->textures[3]);
}
