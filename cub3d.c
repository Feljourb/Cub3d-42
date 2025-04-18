/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 21:57:37 by feljourb          #+#    #+#             */
/*   Updated: 2025/04/16 18:55:40 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// print map va suprimé 
void	print_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		printf("%s\n", map->map[i]);
		i++;
	}
}

void	read_config(int fd, char **str, t_closed *closed)
{
	char	*line;
	bool	map_started;

	map_started = false;
	line = get_next_line(fd);
	while (line)
	{
		extract_config(line, str, closed, &map_started);
		free(line);
		line = get_next_line(fd);
	}
}

void	checks(char *str, t_map *map, t_config *config, t_closed *closed)
{
	init_map(str, map, config);
	check_caractere(str, config, map);
	check_pos_player(str, config, map);
	if (str)
	{
		free(str);
		str = NULL;
	}
	print_map(map);
	find_player_position(config, map); // Repère (x, y) et direction du joueur
	check_map_closed(closed);
}

int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		write(1, "error fd\n", 9);
		exit(1);
	}
	return (fd);
}

void	init_data(char **str, t_config **config, t_map **map)
{
	*str = ft_strdup("");
	*config = malloc(sizeof(t_config));
	if (!*config)
	{
		free(*str);
		exit (1);
	}
	init_config(*config);
	*map = malloc(sizeof(t_map));
	if (!*map)
	{
		free(*str);
		free (*config);
		exit (1);
	}
	(*map)->map = NULL;
	(*map)->max_cols = 0;
	(*map)->rows = 0;
}

int	main(int ac, char **av)
{
	int			fd;
	char		*str;
	t_config	*config;
	t_map		*map;
	t_closed	closed;

	check_args(ac);
	parse_extension(av[1]);
	fd = open_file(av[1]);
	init_data(&str, &config, &map); // alloue mémoire
	closed.map = map;        // ✅ très important !
	closed.config = config;
	read_config(fd, &str, &closed); // lit le .cub
	checks(str, map, config, &closed); // parse la map
	check_presence_textures(config, map, str);
	free_all(config, map, NULL); // free les textures .
	return (close(fd), 0);
}
