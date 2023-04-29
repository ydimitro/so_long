/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitro <ydimitro@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:15:24 by ydimitro          #+#    #+#             */
/*   Updated: 2023/04/29 19:10:35 by ydimitro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_visited(int **visited)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (visited[i])
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

static int	**create_visited(t_game *game)
{
	int	**visited;
	int	i;

	visited = (int **)ft_calloc(game->map.rows + 1, sizeof(int *));
	if (!visited)
		return (0);
	i = 0;
	while (i < game->map.rows)
	{
		visited[i] = (int *)ft_calloc(game->map.columns + 1, sizeof(int ));
		if (!visited[i])
		{
			free_visited(visited);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

static void	dfs_visit(t_game *game, int y, int x, int **visited)
{
	static int	foundcollectibles = 0;

	visited[x][y] = true;
	if (game->map.full[x][y] == COLLECTIBLE)
	{
		foundcollectibles++;
		if (game->map.collectible == foundcollectibles)
			game->map.foundcollectibles = true;
	}
	if (game->map.full[x][y] == MAP_EXIT)
	{
		game->map.exit++;
		return ;
	}
	if (x - 1 >= 0 && game->map.full[x - 1][y] != WALL && !visited[x - 1][y])
		dfs_visit(game, y, x - 1, visited);
	if (x + 1 < game->map.rows && game->map.full[x + 1][y] != WALL &&
		!visited[x + 1][y])
		dfs_visit(game, y, x + 1, visited);
	if (y - 1 >= 0 && game->map.full[x][y - 1] != WALL && !visited[x][y - 1])
		dfs_visit(game, y - 1, x, visited);
	if (y + 1 < game->map.columns && game->map.full[x][y + 1] != WALL &&
		!visited[x][y + 1])
		dfs_visit(game, y + 1, x, visited);
}

static t_bool	dfs_traverse_map_from_position(t_game *game, int x, int y)
{
	int	**visited;

	visited = create_visited(game);
	if (!visited)
	{
		return (false);
	}
	dfs_visit(game, x, y, visited);
	free_visited(visited);
	if (game->map.foundcollectibles == false || game->map.exit == false)
		return (false);
	return (true);
}

t_bool	check_map_accessible(t_game *game)
{
	game->map.foundcollectibles = false;
	game->map.exit = false;
	return (dfs_traverse_map_from_position(game, \
	game->map.player.x, game->map.player.y));
}
