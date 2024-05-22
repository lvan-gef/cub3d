#ifndef CUB3D_PARSER_H
#define CUB3D_PARSER_H

#include <fcntl.h>
#include <stdbool.h>

#include "./cub3d_structs.h"

#include "../libft/include/libft.h"

#define WHITESPACE "\10\11\12\13\14\15\40"
#define VALID_MAP_CHARS "10\n "
#define PLAYER_POS "NSEW"

// utils
void print_error(char *message);
void *ft_malloc_check(void *s);

// parser
// void parser(char *argv[]);
bool parser(t_program *program, char *argv[]);
char **tokenize_input(char *argv);
char *get_next_line(int fd);
void validate_nr_of_identifiers(char **elements);
void validate_rgb_input(char **elements, t_program *program);
void validate_structure_paths(char **elements, t_program *program);
void validate_map(char *map, t_program *program);
void check_surrounded_walls(t_program *program);

// parse utils
int ft_atorgb(const char *str);
int check_png(char *arg);
int check_cub(char *arg);

// game part
bool init_game(t_program *program);

// tmp
void free_char_arr(char **arr);

#endif
