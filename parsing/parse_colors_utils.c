/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 06:53:29 by feljourb          #+#    #+#             */
/*   Updated: 2025/04/18 06:58:15 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	print_error(char *msg, char **num, t_trim *trim)
{
	write(2, msg, ft_strlen(msg));
	if (trim)
		free_trim(trim->r, trim->g, trim->b);
	free_split(num);
	return (0);
}

void	init_trim(t_trim *trim)
{
	trim->r = NULL;
	trim->g = NULL;
	trim->b = NULL;
}

int	validate_trim(t_trim *trim, char **num)
{
	if (!*trim->r || !*trim->g || !*trim->b)
		return (print_error("Error: one of the RGB values is empty!\n",
				num, trim));
	if (!ft_isdigit_chaine(trim->r) || !ft_isdigit_chaine(trim->g)
		|| !ft_isdigit_chaine(trim->b))
		return (print_error("Error: non-numeric RGB value detected!\n",
				num, trim));
	return (1);
}
