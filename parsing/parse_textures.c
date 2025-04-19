/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:59:21 by feljourb          #+#    #+#             */
/*   Updated: 2025/04/19 03:37:21 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// int	has_xpm_extension(char *texture)
// {
// 	int	len;

// 	len = ft_strlen(texture);
// 	if (len < 4)
// 		return (0);
// 	if (strcmp(&texture[len - 4], ".xpm") == 0)
// 		return (1);
// 	return (0);
// }

// static char	*texture_error(char *error_msg, char *path)
// {
// 	if (path)
// 		free(path);
// 	write(2, error_msg, ft_strlen(error_msg));
// 	return (NULL);
// }

char	*extract_texture_path(char *line)
{
	int		i;
	char	*path;
	int		fd;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	path = ft_strtrim(&line[i], " \t\n");
	if (!path || !path[0])
		return (texture_error("Error: texture path is missing or empty!\n", path));
	if (!has_xpm_extension(path))
		return (texture_error("Error: texture file must be .xpm\n", path));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (texture_error("Error: texture file not found\n", path));
	close(fd);
	return (path);
}

void	check_presence_textures(t_config *config, t_map *map, char *str)
{
	if (!config->texture_nord || !config->texture_south
		|| !config->texture_east || !config->texture_west
		|| config->ceiling_color == -1 || config->floor_color == -1)
	{
		write(2, "Error: missing textures or colors.\n", 35);
		free_all(config, map, str);
		exit(1);
	}
}

static void	assign_texture(char **texture, char *path,
	char *error_mssg, t_txtctx *txtctx)
{
	if (*texture)
	{
		free(path);
		free(txtctx->line);
		get_next_line(-42);
		free_all(txtctx->config_txt, txtctx->map, txtctx->str);
		exit(write(2, error_mssg, ft_strlen(error_mssg)));
	}
	*texture = path;
}

static void	parse_texture_line(char *line, char *path,
	t_config *config_txt, t_txtctx *txtctx)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		assign_texture(&config_txt->texture_nord, path,
			"Error: duplicate NO texture\n", txtctx);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		assign_texture(&config_txt->texture_south, path,
			"Error: duplicate SO texture\n", txtctx);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		assign_texture(&config_txt->texture_east, path,
			"Error: duplicate EA texture\n", txtctx);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		assign_texture(&config_txt->texture_west, path,
			"Error: duplicate WE texture\n", txtctx);
}

void	config_texture(char *line, t_config *config_txt, t_map *map, char *str)
{
	char		*path;
	t_txtctx	txtctx;

	path = extract_texture_path(line);
	if (!path)
	{
		free_all(config_txt, map, str);
		free(line);
		get_next_line(-42);
		exit(1);
	}
	//initialisé la struct txtctx
	txtctx.config_txt = config_txt;
	txtctx.map = map;
	txtctx.line = line;
	txtctx.str = str;
	parse_texture_line(line, path, config_txt, &txtctx);
}
