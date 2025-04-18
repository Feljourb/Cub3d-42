/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:48:33 by feljourb          #+#    #+#             */
/*   Updated: 2025/04/16 19:25:52 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_caractere(char *str, t_config *config, t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (map->map[x])
	{
		y = 0;
		while (map->map[x][y])
		{
			if (map->map[x][y] != '1' && map->map[x][y] != '0'
				&& map->map[x][y] != 'N' && map->map[x][y] != 'W'
				&& map->map[x][y] != 'S' && map->map[x][y] != 'E'
				&& map->map[x][y] != ' ')
			{
				write(1, "Error: invalid caractere\n", 25);
				free_all(config, map, str);
				exit(1);
			}
			y++;
		}
		x++;
	}
	return (0);
}

void	check_pos_player(char *str, t_config *config, t_map *map)
{
	int	x;
	int	y;
	int	count;

	x = 0;
	count = 0;
	while (map->map[x])
	{
		y = 0;
		while (map->map[x][y])
		{
			if (map->map[x][y] == 'N' || map->map[x][y] == 'S'
				|| map->map[x][y] == 'E' || map->map[x][y] == 'W')
				count ++;
			y++;
		}
		x++;
	}
	if (count != 1)
	{
		write(1, "Error: just one position\n", 25);
		free_all(config, map, str);
		exit(1);
	}
}

void	init_map(char *str, t_map *map_init, t_config *config)
{
	int	i;
	int	max_width;
	int	len;

	i = 0;
	max_width = 0;
	map_init->map = ft_split(str, '\n');
	if (map_init->map[0] == NULL)
	{
		write(2, "Error: No map found\n", 20);
		free_all(config, map_init, str);
		exit (1);
	}
	while (map_init->map[i])
	{
		len = ft_strlen(map_init->map[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	map_init->rows = i;
	map_init->max_cols = max_width;
}

void	find_player_position(t_config *config, t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (map->map[x])
	{
		y = 0;
		while (map->map[x][y])
		{
			if (map->map[x][y] == 'N' || map->map[x][y] == 'S'
				|| map->map[x][y] == 'E' || map->map[x][y] == 'W')
			{
				config->player_x = x;
				config->player_y = y;
				config->player_dir = map->map[x][y];
			}
			y++;
		}
		x++;
	}
}
