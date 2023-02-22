/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:01:57 by jrosmari          #+#    #+#             */
/*   Updated: 2023/02/22 22:08:03 by jrosmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	buf_work(char **st_line, int fd, int buf_size)
{
	char	*buffer;	
	char	*temp;
	int		cnt;
	int		rd;

	cnt = 0;
	rd = 0;
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
	while ((rd = read(fd, buffer, buf_size)) > 0)
	{
		temp = malloc(ft_strlen(*st_line) + rd + 1);
		if (!temp)
			return (-1);
		strcpy(temp, *st_line);
		strncat(temp, buffer, rd);
		free(*st_line);
		*st_line = NULL;
		*st_line = ft_strdup(temp);
		free(temp);
		temp = NULL;
		if (strchr(*st_line, '\n') != NULL)
		{
			cnt = 1;
			break ;
		}
		cnt = 0;
	}
	free(buffer);
	buffer = NULL;
	return (cnt);
}

char	*line_cut(char **st_line)
{
	char	*rtrn;
	char	*rest;
	int		cnt;

	cnt = 0;
	while ((*st_line)[cnt] != '\n')
		cnt++;
	rtrn = ft_substr(*st_line, 0, cnt + 1);
	rest = ft_substr(*st_line, cnt + 1, strlen(*st_line) - (cnt + 1));
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
		st_line = malloc(1);
		if (!st_line)
			return (NULL);
		st_line[0] = '\0';
	}
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	result = buf_work(&st_line, fd, BUFFER_SIZE);
	if (result == -1)
		return (NULL);
	if (result == 1)
		return (line_cut(&st_line));
	rt_line = ft_strdup(st_line);
	free(st_line);
	st_line = NULL;
	return (rt_line);
}
/*#include <fcntl.h>

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