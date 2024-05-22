#include "../../include/cub3d_parser.h"

static const char	*g_positions[4] = {"N", "S", "W", "E"};

int	check_characters(char *map)
{
	int		i;
	char	flag_player;

	i = 0;
	flag_player = '\0';
	while (map[i])
	{
		if ((ft_strchr(PLAYER_POS, map[i]) != NULL) && flag_player == '\0')
		{
			flag_player = map[i];
			i++;
		}
		if (ft_strchr(VALID_MAP_CHARS, map[i]) != NULL)
			i++;
		else
			print_error("Invalid map: wrong character input");  // leaks map
	}
	if (!flag_player)
		print_error("Invalid map: No player input");  // leaks map
	i = 0;
	while (g_positions[i])
	{
		if (*g_positions[i] == flag_player)
			break ;
		i++;
	}
	return (i);
}

void	find_max_xy(char *map, t_program *program)
{
	int	counter;
	int	max_row;
	int	max_col;
	int	max_col_counter;

	max_row = 1;
	max_col = 0;
	max_col_counter = 0;
	counter = 0;
	while (map[counter])
	{
		if (map[counter] != '\n')
			max_col_counter++;
		if (map[counter] == '\n')
		{
			max_row++;
			if (max_col_counter > max_col)
				max_col = max_col_counter;
			max_col_counter = 0;
		}
		counter++;
	}
	if (max_col_counter > max_col)
		max_col = max_col_counter;
	if (max_row < 3)
		print_error("Invalid map: Map not big enough");  // leaks map
	program->max_xy.row = max_row;
	program->max_xy.col = max_col;
}

void	fill_map(char *map, t_program *program)
{
	char	**temp_map;
	char	**dst_map;
	int		row_counter;

	row_counter = 0;
	temp_map = ft_split(map, '\n'); // NULL check
	dst_map = ft_calloc(program->max_xy.row + 1, sizeof(char *));  // NULL check, leak map,  temp_map
	while (row_counter < program->max_xy.row)
	{
		dst_map[row_counter] = ft_calloc(program->max_xy.col + 1, sizeof(char));  // NULL check, leak map,  temp_map
		ft_memset(dst_map[row_counter], ' ', program->max_xy.col);
		ft_memcpy(dst_map[row_counter], temp_map[row_counter], \
			ft_strlen(temp_map[row_counter]));
		row_counter++;
	}
	free_char_arr(temp_map);
	free(map);
	program->map = dst_map;
}

void	fill_player(t_program *program)
{
	int	count_x;
	int	count_y;

	count_x = 0;
	count_y = 0;
	while (count_y < program->max_xy.row)
	{
		while (count_x < program->max_xy.col)
		{
			if (ft_strchr(PLAYER_POS, program->map[count_y][count_x]) != NULL)
			{
				program->start_pos.col = count_x;
				program->start_pos.row = count_y;
				return ;
			}
			count_x++;
		}
		count_x = 0;
		count_y++;
	}
}

void	validate_map(char *map, t_program *program)
{
	program->spawning_pos = check_characters(map);
	find_max_xy(map, program);
	fill_map(map, program);
	fill_player(program);
	printf("col: %i\n row: %i\n", program->start_pos.col, program->start_pos.row);
	check_surrounded_walls(program);
}
