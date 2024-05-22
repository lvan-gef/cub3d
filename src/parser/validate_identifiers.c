#include "../../include/cub3d_parser.h"

void	validate_structure_paths(char **elements, t_program *program)
{
	int	i;

	i = 0;
	while (i < ASSETS_SIZE)
	{
		if (!check_png(elements[i]) || (ft_strncmp("./", elements[i], 2) != 0))
			print_error("Incorrect filepath input!");  // leak elements and program
		program->textures[i] = ft_strdup(elements[i]);  // NUll check or program must handle it
		free (elements[i]);
		i++;
	}
}

void	convert_digits(char **input, int *colors)
{
	int	i;
	// int	j;  // set but never used

	i = 0;
	// j = 0;
	while (i < 3)
	{
		colors[i] = ft_atorgb(input[i]);
		if (colors[i] < 0)
			print_error("Incorrect RGB input");  // leak elements, input and **inputs
		i++;
	}
}

void	convert_rgb(char *input, int *colors)
{
	char	**split_elements;
	char	*temp;
	int		i;

	i = 0;
	split_elements = ft_split(input, ',');  // NULL check
	while (split_elements[i])  // error when split_elements is NULL
		i++;
	if (i != 3)
		print_error("Incorrect RGB input");  // leak elements, split_elements[i] and input
	i = 0;
	while (split_elements[i])
	{
		temp = ft_strtrim(split_elements[i], WHITESPACE);  // NULL check
		free(split_elements[i]);
		split_elements[i] = temp;
		i++;
	}
	convert_digits(split_elements, colors);
	free_char_arr(split_elements);
	free(input);
}

void	validate_rgb_input(char **elements, t_program *program)
{
	convert_rgb(elements[F], program->floor_rgb);
	convert_rgb(elements[C], program->ceiling_rgb);
}

void	validate_nr_of_identifiers(char **elements)
{
	int	i;

	i = 0;
	while (i < SIZE + 1)
	{
		if (elements[i] == NULL)
			print_error("Missing object input");  // leak elements
		i++;
	}
}
