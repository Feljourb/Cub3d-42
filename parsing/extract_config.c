/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:44:26 by feljourb          #+#    #+#             */
/*   Updated: 2025/04/16 19:17:24 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	handle_unknown_line(char *line, t_closed *closed,
	char *str, bool *map_started)
{
	if (*map_started)
		write(2, "Error: invalid line after map started\n", 38);
	else
		write(2, "Error: unknown line in .cub file\n", 33);
	free_all(closed->config, closed->map, str);
	free(line);
	free_gnl();
	exit(1);
}

static void	append_map_line(char *line, char **str)
{
	char	*temp;

	temp = ft_strjoin(*str, line);
	free(*str);
	*str = temp;
}

static void	handle_emty_line(char *line, t_config *config,
	t_map *map, char *str)
{
	write(2, "Error: empty line in map section\n", 33);
	free(line);
	free_all(config, map, str);
	free_gnl();
	exit(1);
}

void	extract_config(char *line, char **str,
	t_closed *closed, bool *map_started)
{
	int	i;

	i = 0;
	if (!*map_started && (is_textures_line(line) || is_colors_line(line)))
	{
		handle_config_lines(closed->config, line, closed->map, *str);
		return ;
	}
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
	{
		if (*map_started)
			handle_emty_line(line, closed->config, closed->map, *str);
		return ;
	}
	if (ft_isdigit(line[i]))
	{
		*map_started = true;
		append_map_line(line, str);
	}
	else
		handle_unknown_line(line, closed, *str, map_started);
}
