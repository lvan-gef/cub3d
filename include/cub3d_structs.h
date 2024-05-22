#ifndef CUB3D_STRUCTS_H
#define CUB3D_STRUCTS_H

#include <stdint.h>

#include "../MLX42/include/MLX42/MLX42.h"

#define ASSETS_SIZE 4

typedef enum e_player_pos {
  N,
  S,
  W,
  E,
} t_players_pos;

typedef enum e_tokens { NO, SO, WE, EA, F, C, SIZE } t_tokens;

typedef struct s_vector {
  int col;
  int row;
} t_vector;

typedef	struct	s_render
{
	t_vector		resolution;
	t_vector		player_pos;
	t_players_pos	direction;
	mlx_image_t		*image;
	mlx_texture_t	*mlx_textures[ASSETS_SIZE];
	mlx_t			*mlx;
}	t_render;

typedef struct s_program
{
	char			*textures[ASSETS_SIZE];     // naam van de texture?
	int				floor_rgb[3];     // rgb van de vloer
	uint32_t		usable_floor;     // weet niet wat dit is
	uint32_t		usable_ceiling;   // weet niet wat dit is
	int				ceiling_rgb[3];   // rgb van het plafon
	char			**map;            // de map van het spel
	t_vector		max_xy;           // map grote (x, y cords)
	t_vector		start_pos;        // player start (x, y cords)
	t_players_pos	spawning_pos;     // welke kant het poppetje op kijkt
	t_render		*render;
}	t_program;

// debugging
void	print_program(t_program *program);
#endif
