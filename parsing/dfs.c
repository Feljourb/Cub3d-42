/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:48:50 by feljourb          #+#    #+#             */
/*   Updated: 2025/04/16 18:36:48 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	dfs(char **map, int x, int y, int rows)
{
	if (x < 0 || y < 0 || y >= rows || x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == ' ')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (1);
	map[y][x] = 'V';
	if (!dfs(map, x + 1, y, rows))
		return (0);
	if (!dfs(map, x - 1, y, rows))
		return (0);
	if (!dfs(map, x, y + 1, rows))
		return (0);
	if (!dfs(map, x, y - 1, rows))
		return (0);
	return (1);
}

char	**copy_map(char **original, int rows)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * (rows + 1));
	if (!copy)
		return (NULL);
	while (i < rows)
	{
		copy[i] = ft_strdup(original[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	verify_cell_closed(int x, int y, char **map_copy, t_closed *closed)
{
	if (!dfs(map_copy, x, y, closed->map->rows))
	{
		write(2, "Error: map not closed\n", 23);
		free_split(map_copy);
		free_all(closed->config, closed->map, NULL);
		exit(1);
	}
}

static void	loop_check_map(char **map_copy, t_closed *closed)
{
	int	x;
	int	y;

	y = 0;
	while (y < closed->map->rows)
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] == '0' || map_copy[y][x] == 'N'
				|| map_copy[y][x] == 'S' || map_copy[y][x] == 'W'
				|| map_copy[y][x] == 'E')
				verify_cell_closed(x, y, map_copy, closed);
			x++;
		}
		y++;
	}
}

void	check_map_closed(t_closed *closed)
{
	char	**map_copy;

	map_copy = copy_map(closed->map->map, closed->map->rows);
	if (!map_copy)
	{
		write(2, "Error: map copy failed\n", 24);
		free_all(closed->config, closed->map, NULL);
		exit(1);
	}
	loop_check_map(map_copy, closed);
	free_split(map_copy);
}
