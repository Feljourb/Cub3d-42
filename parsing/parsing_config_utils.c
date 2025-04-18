/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config_lines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:10:38 by feljourb          #+#    #+#             */
/*   Updated: 2025/04/16 20:20:47 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_config(t_config *config)
{
	config->floor_color = -1;
	config->ceiling_color = -1;
	config->texture_NO = NULL;
	config->texture_SO = NULL;
	config->texture_WE = NULL;
	config->texture_EA = NULL;
	config->player_x = -1;
	config->player_y = -1;
	config->player_dir = 0;
}

int	is_textures_line(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0);
}

int	is_colors_line(char *line)
{
	return (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

void	handle_config_lines(t_config *config, char *line, t_map *map, char *str)
{
	if (is_textures_line(line))
		config_texture(line, config, map, str);
	if (is_colors_line(line))
		config_colors(line, config, map, str);
}

char	*texture_error(char *error_msg, char *path)
{
	if (path)
		free(path);
	write(2, error_msg, ft_strlen(error_msg));
	return (NULL);
}
