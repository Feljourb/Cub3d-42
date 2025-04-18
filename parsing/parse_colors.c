/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:41:48 by feljourb          #+#    #+#             */
/*   Updated: 2025/04/18 06:57:58 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// int	print_error(char *msg, char **num, t_trim *trim)
// {
// 	write(2, msg, ft_strlen(msg));
// 	if (trim)
// 		free_trim(trim->r, trim->g, trim->b);
// 	free_split(num);
// 	return (0);
// }

// static void	init_trim(t_trim *trim)
// {
// 	trim->r = NULL;
// 	trim->g = NULL;
// 	trim->b = NULL;
// }

// static int	validate_trim(t_trim *trim, char **num)
// {
// 	if (!*trim->r || !*trim->g || !*trim->b)
// 		return (print_error("Error: one of the RGB values is empty!\n",
// 				num, trim));
// 	if (!ft_isdigit_chaine(trim->r) || !ft_isdigit_chaine(trim->g)
// 		|| !ft_isdigit_chaine(trim->b))
// 		return (print_error("Error: non-numeric RGB value detected!\n",
// 				num, trim));
// 	return (1);
// }

int	parse_rgb_values(char *line, int *r, int *g, int *b)
{
	int		i;
	char	**num;
	t_trim	trim ;

	init_trim(&trim);
	i = 0;
	while (line[i] == ' ' || line[i] == 'F' || line[i] == 'C')
		i++;
	num = ft_split(&line[i], ',');
	if (!num || !num[0] || !num[1] || !num[2] || num[3])
		return (print_error("Error: wrong number of RGB values!\n",
				num, &trim));
	trim.r = ft_strtrim(num[0], " \n");
	trim.g = ft_strtrim(num[1], " \n");
	trim.b = ft_strtrim(num[2], " \n");
	if (!validate_trim(&trim, num))
		return (0);
	*r = ft_atoi(trim.r);
	*g = ft_atoi(trim.g);
	*b = ft_atoi(trim.b);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (print_error("Error: RGB values out of range (0-255) !\n",
				num, &trim));
	return (free_trim(trim.r, trim.g, trim.b), free_split(num), 1);
}

int	extract_clr(char *line)
{
	int	r;
	int	g;
	int	b;
	int	color;

	if (!parse_rgb_values(line, &r, &g, &b))
		return (-1);
	color = (r << 16 | g << 8 | b);
	printf("r = %d\n", r);
	printf("g = %d\n", g);
	printf("b = %d\n", b);
	printf("color = %d\n", color);
	return (color);
}

static void	set_floor_colors(t_config *config_clr, t_map *map,
		char *line, char *str)
{
	int	color;

	if (config_clr->floor_color != -1)
	{
		free_all(config_clr, map, str);
		free(line);
		free_gnl();
		exit(write(2, "Error: duplicate F\n", 19));
	}
	color = extract_clr(line);
	if (color == -1)
	{
		free_all(config_clr, map, str);
		free(line);
		free_gnl();
		exit (1);
	}
	config_clr->floor_color = color;
}

static void	set_ceiling_color(t_config *config_clr, t_map *map,
		char *line, char *str)
{
	int	color;

	if (config_clr->ceiling_color != -1)
	{
		free_all(config_clr, map, str);
		free(line);
		free_gnl();
		exit(write(2, "Error: duplicate C\n", 19));
	}
	color = extract_clr(line);
	if (color == -1)
	{
		free_all(config_clr, map, str);
		free(line);
		free_gnl();
		exit (1);
	}
	config_clr->ceiling_color = color;
}

void	config_colors(char *line, t_config *config_clr, t_map *map, char *str)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		set_floor_colors(config_clr, map, line, str);
	if (ft_strncmp(line, "C ", 2) == 0)
		set_ceiling_color(config_clr, map, line, str);
}
