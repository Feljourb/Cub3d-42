/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 06:32:36 by feljourb          #+#    #+#             */
/*   Updated: 2025/04/11 21:57:21 by feljourb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
void	free_gnl(void);
int		f_strlen(char *str);
int		f_strchr(char *g_save);
char	*f_strjoin(char *buff, char *g_save);
char	*ft_save(char *g_save, char *line);
char	*ft_get_line(char *g_save);
char	*read_file(int fd, char *g_save);
char	*f_strdup(char *str);

#endif