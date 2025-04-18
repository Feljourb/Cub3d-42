/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:20:26 by feljourb          #+#    #+#             */
/*   Updated: 2025/04/18 06:49:39 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_config(t_config *config)
{
	if (config->texture_NO)
		free(config->texture_NO);
	if (config->texture_SO)
		free(config->texture_SO);
	if (config->texture_WE)
		free(config->texture_WE);
	if (config->texture_EA)
		free(config->texture_EA);
	free(config);
}

void	free_all(t_config *config, t_map *map, char *str)
{
	if (str)
		free(str);
	if (config)
		free_config(config);
	if (map)
	{
		if (map->map)
			free_split(map->map);
		free(map);
	}
}

void	free_split(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_trim(char *r, char *g, char *b)
{
	if (r)
		free(r);
	if (g)
		free(g);
	if (b)
		free(b);
}
