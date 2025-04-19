/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 06:31:41 by feljourb          #+#    #+#             */
/*   Updated: 2025/04/19 01:13:03 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *g_save)
{
	char	*buff;
	int		rread;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (!g_save)
		g_save = f_strdup("");
	rread = 1;
	while (!f_strchr(g_save) && rread != 0)
	{
		rread = read(fd, buff, BUFFER_SIZE);
		if (rread == -1)
		{
			free(buff);
			free(g_save);
			return (NULL);
		}
		buff[rread] = '\0';
		g_save = f_strjoin(buff, g_save);
	}
	free(buff);
	return (g_save);
}

char	*ft_get_line(char *g_save)
{
	char	*str;
	int		i;

	i = 0;
	while (g_save[i] && g_save[i] != '\n')
		i++;
	str = malloc(i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (g_save[i] && g_save[i] != '\n')
	{
		str[i] = g_save[i];
		i++;
	}
	if (g_save[i] == '\n')
	{
		str[i] = '\n';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_save(char *g_save, char *line)
{
	char	*rest;
	int		i;
	int		j;

	i = f_strlen(line);
	j = 0;
	if (line[0] == '\0')
	{
		free(g_save);
		return (NULL);
	}
	while (g_save[i++])
		j++;
	rest = malloc(j + 1);
	if (!rest)
		return (NULL);
	i = f_strlen(line);
	j = 0;
	while (g_save[i])
		rest[j++] = g_save[i++];
	rest[j] = '\0';
	free(g_save);
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*g_save;

	if (fd == -42)
	{
		if (g_save)
			free(g_save);
		g_save = NULL;
		return NULL;
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	g_save = read_file(fd, g_save);
	if (!g_save)
		return (NULL);
	line = ft_get_line(g_save);
	g_save = ft_save(g_save, line);
	if (!g_save)
		return (free(line), NULL);
	return (line);
}
