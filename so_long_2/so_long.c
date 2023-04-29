/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitro <ydimitro@students.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:12:09 by ydimitro          #+#    #+#             */
/*   Updated: 2022/12/09 20:12:09 by ydimitro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char	**argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (1);
	check_command_line_arguments(argc, argv, game);
	init_map(game, argv[1]);
	init_vars(game);
	init_mlx(game);
	init_sprites(game);
	check_map(game);
	if (check_map_accessible(game))
	{
		render_map(game);
		mlx_hook(game->win_ptr, 02, 1L << 0, handle_input, game);
		mlx_hook(game->win_ptr, 17, 1L << 2, close_game, game);
		mlx_hook(game->win_ptr, 12, 1L << 15, render_map, game);
		mlx_loop(game->mlx_ptr);
	}
	else
	{
		write (2, "Provided map is not playable.\n", 31);
	}
	free_all_allocated_memory(game);
}
