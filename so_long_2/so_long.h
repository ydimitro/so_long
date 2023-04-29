/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitro <ydimitro@students.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:58:51 by ydimitro          #+#    #+#             */
/*   Updated: 2022/12/09 18:58:51 by ydimitro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "mlx/mlx.h"
# include "libft/libft.h"

# define IMG_HEIGHT			100
# define IMG_WIDTH			100

# define WALL				'1'
# define FLOOR 				'0'
# define COLLECTIBLE		'C'
# define PLAYER				'P'
# define MAP_EXIT 		 	'E'

# define KEY_W				13
# define KEY_A				0
# define KEY_S				1
# define KEY_D				2

# define KEY_LEFT  			123
# define KEY_RIGHT 			124
# define KEY_DOWN  			125
# define KEY_UP  			126

# define KEY_Q				12
# define KEY_ESC  			53

# define WALL_XPM			"lib/images/wall-resize.xpm"
# define FLOOR_XPM			"lib/images/background-resize.xpm"
# define COLLECTIBLE_XPM	"lib/images/collectible-resize.xpm"
# define PLAYER_XPM			"lib/images/player-resize.xpm"
# define OPEN_EXIT_XPM		"lib/images/open_exit-resize.xpm"
# define EXIT_CLOSED_XPM	"lib/images/exit_closed-resize.xpm"

# define GREEN				"\033[0;32m"
# define RED 				"\033[1;31m"
# define GREY 				"\033[0;90m"
# define CYAN				"\033[1;96m"
# define RESET 				"\033[0m"

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_position
{
	int	x;
	int	y;
}	t_positon;

typedef struct s_image
{
	void	*xpm_ptr;
	int		x;
	int		y;
}	t_image;

typedef struct s_map
{
	char		**full;
	int			rows;
	int			columns;
	int			collectible;
	int			exit;
	int			foundcollectibles;
	int			players;
	t_positon	player;
}	t_map;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			movements;
	t_map		map;
	t_bool		map_alloc;
	t_image		wall;
	t_image		floor;
	t_image		collectible;
	t_image		player;
	t_image		open_exit;
	t_image		exit_closed;
}	t_game;

//map_init.c
void		check_command_line_arguments(int argc, char **argv, t_game *game);
char		*ft_strappend(char *s1, const char *s2);
void		init_map(t_game *game, char *argv);
void		check_for_empty_line(char *map, t_game *game);

//game_init.c
void		init_vars(t_game *game);
void		init_mlx(t_game *game);
void		init_sprites(t_game *game);
t_image		new_sprite(void *mlx, char *path, t_game *game);

//map_render.c
int			render_map(t_game *game);
void		identify_sprite(t_game *game, int x, int y);
void		render_sprite(t_game *game, t_image sprite, int column, int line);
void		print_movements(t_game *game);

//map_check.c
void		check_map(t_game *game);
void		check_rows(t_game *game);
void		check_columns(t_game *game);
void		count_map_parameters(t_game *game);
void		verify_map_parameters(t_game *game);

//input_frame.c
int			handle_input(int keysym, t_game *game);
void		player_move(t_game *game, int x, int y);

//game_close.c
int			victory(t_game *game);
int			error_msg(char *message, t_game *game);
int			close_game(t_game *game);

//free_memory.c
void		free_all_allocated_memory(t_game *game);
void		destroy_images(t_game *game);
void		free_map(t_game *game);

//valid_path.c
t_bool		check_map_accessible(t_game *game);

//other
char		*get_next_line(int fd);

#endif
