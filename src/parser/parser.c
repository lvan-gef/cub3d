#include "../../include/cub3d_parser.h"
#include "libft.h"

bool	parser(t_program *program, char *argv[])
{
	char		**elements;

	// if error return false and clean up own state
	check_cub(argv[1]);
	elements = tokenize_input(argv[1]);
	validate_nr_of_identifiers(elements);
	validate_structure_paths(elements, program);
	validate_rgb_input(elements, program);
	validate_map(elements[SIZE], program);

	// free_char_arr(elements);
	// elements = NULL;
	return (true);
}
