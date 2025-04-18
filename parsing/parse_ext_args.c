/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ext_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:39:35 by feljourb          #+#    #+#             */
/*   Updated: 2025/04/16 18:59:36 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_extension(char *av)
{
	int	i;

	i = 0;
	while (av[i] && av[i] != '.')
		i++;
	if (!av[i])
	{
		write(1, "Error extension: no dot found\n", 30);
		exit(1);
	}
	if (strcmp(&av[i], ".cub") != 0)
	{
		write(1, "Error extension\n", 16);
		exit(1);
	}
	return (0);
}

int	has_xpm_extension(char *texture)
{
	int	len;

	len = ft_strlen(texture);
	if (len < 4)
		return (0);
	if (strcmp(&texture[len - 4], ".xpm") == 0)
		return (1);
	return (0);
}

void	check_args(int ac)
{
	if (ac != 2)
	{
		write(1, "error ac\n", 9);
		exit(1);
	}
}
