/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:01:57 by jrosmari          #+#    #+#             */
/*   Updated: 2023/02/26 11:28:45 by jrosmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	read_and_append(char **st_line, int fd, char *buffer, int cnt)
{
	char	*temp;
	int		rd;

	while (1)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd <= 0)
			break ;
		temp = malloc(ft_strlen(*st_line) + rd + 1);
		if (!temp)
			return (-1);
		ft_strcpy(temp, *st_line);
		ft_strncat(temp, buffer, rd);
		free(*st_line);
		*st_line = ft_strdup(temp);
		free(temp);
		if (ft_strchr(*st_line, '\n') != NULL)
		{
			cnt = 1;
			break ;
		}
		cnt = 0;
	}
	return (cnt);
}

static int	buf_work(char **st_line, int fd, int buf_size, int cnt)
{
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (buf_size + 1));
	if (!buffer)
		return (-1);
	while (cnt < buf_size)
		buffer[cnt++] = '0';
	buffer[cnt] = '\0';
	if (ft_strchr(*st_line, '\n') != NULL)
		cnt = 1;
	else if (ft_strlen(*st_line) > 0)
		cnt = 0;
	else
		cnt = -1;
	cnt = read_and_append(st_line, fd, buffer, cnt);
	free(buffer);
	return (cnt);
}

static char	*line_cut(char **st_line)
{
	char	*rtrn;
	char	*rest;
	int		cnt;

	cnt = 0;
	while ((*st_line)[cnt] != '\n')
		cnt++;
	rtrn = ft_substr(*st_line, 0, cnt + 1);
	rest = ft_substr(*st_line, cnt + 1, ft_strlen(*st_line) - (cnt + 1));
	free(*st_line);
	*st_line = NULL;
	*st_line = ft_strdup(rest);
	free(rest);
	rest = NULL;
	return (rtrn);
}

char	*get_next_line(int fd)
{		
	static char	*st_line = NULL;
	char		*rt_line;
	int			result;

	if (st_line == NULL)
	{
		st_line = (char *)malloc(1);
		if (!st_line)
			return (NULL);
		st_line[0] = '\0';
	}
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	result = buf_work(&st_line, fd, BUFFER_SIZE, 0);
	if (result == -1)
		return (NULL);
	if (result == 1)
		return (line_cut(&st_line));
	rt_line = ft_strdup(st_line);
	free(st_line);
	st_line = NULL;
	return (rt_line);
}
/*
#include <fcntl.h>
int	main(void)
{
	int	BUFFER_SIZE = 10;
	char	*toprint;
	
	int fd = open("bigline.txt", O_RDONLY | O_CREAT);
	
	
	
	
	while ((toprint = get_next_line(fd, BUFFER_SIZE)) != NULL )
	{
		printf("%s", toprint);
	}
	close(fd);
	return (0);
	return (0);
}*/