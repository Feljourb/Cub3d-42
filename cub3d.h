/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 21:57:28 by feljourb          #+#    #+#             */
/*   Updated: 2025/04/18 07:08:46 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include "Gnl/get_next_line.h"
# include "libft/libft.h"

typedef struct s_config
{
	int		height; // hauteur
	int		width;// largeur
	char	*texture_nord; // du nord
	char	*texture_south; // du south
	char	*texture_west; // du west
	char	*texture_east; // du east
	int		floor_color; // SOL
	int		ceiling_color; //plafond
	int		player_x;
	int		player_y;
	char	player_dir; // 'N', 'S', 'E' ou 'W'
}	t_config;

typedef struct s_map
{
	char	**map; //map 2d
	int		rows; // number lignes 
	int		max_cols; // Largeur maximale (calculée)
}	t_map;

typedef struct s_closed
{
	t_map		*map;
	t_config	*config;
}	t_closed;

// juste juste pour mois de 4argmts dans textures .
typedef struct s_txtctx
{
	t_config	*config_txt;
	t_map		*map;
	char		*line;
	char		*str;
}	t_txtctx;
// juste pour mois de 4argmts dans print_error()
typedef struct s_trim
{
	char	*r;
	char	*g;
	char	*b;
}	t_trim;

//_________________________config_________________________________
void	init_config(t_config *config);
// void	replace_newline(char *str);
// void	config_texture(char *line, t_config *config_txt);
void	config_texture(char *line, t_config *config_txt, t_map *map, char *str);
int		extract_clr(char *line);
// void	config_colors(char *line, t_config *config_clr);
void	config_colors(char *line, t_config *config_clr, t_map *map, char *str);
// void	extract_config(char *line, char **str, t_config *config);
// void	extract_config(char *line, char **str, t_config *config, t_map *map);
void	extract_config(char *line, char **str,
			t_closed *closed, bool *map_started);
void	check_presence_textures(t_config *config, t_map *map, char *str);
// void	check_presence_colors(t_config *config, t_map *map, char *str);
void	find_player_position(t_config *config, t_map *map);
int		is_textures_line(char *line);
int		is_colors_line(char *line);
void	handle_config_lines(t_config *config, char *line,
			t_map *map, char *str);
char	*texture_error(char *error_msg, char *path);

//______________________extract_clr________________________________
int		extract_clr(char *line);
int		parse_rgb_values(char *line, int *r, int *g, int *b);
// int		print_error(char *msg , char **num, char *r, char *g, char *b);
int		print_error(char *msg, char **num, t_trim *trim);
void	init_trim(t_trim *trim);
int		validate_trim(t_trim *trim, char **num);

//______________________________map_______________________________
// int		check_caractere(char *str);
int		check_caractere(char *str, t_config *config, t_map *map);
// void	check_pos_player(char *str);
void	check_pos_player(char *str, t_config *config, t_map *map);
void	init_map(char *str, t_map *map_init, t_config *config);
// void	check_murs_horizontal(t_map *map_murs);
// void	check_murs_horizontal(t_map *map_murs, t_config *config);
// void	check_murs_vertical(t_map *map_murs);
// void	check_murs_vertical(t_map *map_murs, t_config *config);
// void	check_empty_line(char *str);
// void	check_map_closed(t_map *map, t_config *config);
void	check_map_closed(t_closed *closed);
int		dfs(char **map, int x, int y, int rows);

//__________________________free___________________________________
void	free_all(t_config *config, t_map *map, char *str);
void	free_config(t_config *config);
void	free_split(char **tab);
void	free_trim(char *r, char *g, char *b);

//_________________________Organisation_du_main__________________________

void	init_data(char **str, t_config **config, t_map **map);
int		open_file(char *filename);
void	check_args(int ac);
// void	checks(char *str, t_map *map);
// void	checks(char *str, t_map *map, t_config *config);
void	checks(char *str, t_map *map, t_config *config, t_closed *closed);
// void	read_config(int fd, char **str, t_config *config);
// void	read_config(int fd, char **str, t_config *config, t_map *map);
void	read_config(int fd, char **str, t_closed *closed);
void	print_map(t_map *map);
int		parse_extension(char *av);
int		has_xpm_extension(char *texture);

#endif