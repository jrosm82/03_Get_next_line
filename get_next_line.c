/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:01:57 by jrosmari          #+#    #+#             */
/*   Updated: 2023/02/22 19:51:35 by jrosmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	c = c & 255;
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	ptr = (char *)malloc(sizeof(char) * (i + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	size;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (start >= size)
		return (ft_strdup(""));
	if (start + len > size)
		len = size - start;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// function buffer
int	buf_work( char **st_line, int fd, int BUFFER_SIZE)
{
	char	*buffer;
	int	cnt;
	char	*temp;
	int	rd;

	cnt = 0;
	rd = 0;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	while (cnt < BUFFER_SIZE)
		buffer[cnt++] = '0';

	buffer[cnt] = '\0';
	if (ft_strchr(*st_line, '\n') != NULL)
		cnt = 1;
	else if (strlen(*st_line) > 0)
		cnt = 0;
	else
		cnt = -1;
	//  file is empty or there is nothing left - will return -1
	//  we keep reading the file and add to buffer
	while((rd = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		// in buffer can be>
		// either less than BUFFER_SIZE - this indicates end of file
		// same length as BUFFER_SIZE - it can have \n in the buffer or on the last place
		temp = malloc(strlen(*st_line) + rd + 1);
		if (!temp)	
			return (-1);
        
		// copy the existing contents of str and the new contents of buffer into the new block of memory
		strcpy(temp, *st_line);
		strncat(temp, buffer, rd);
		
		
		// free the old block of memory
		free(*st_line);
		*st_line = NULL;
		
		// update str to point to the new block of memory
		*st_line = ft_strdup(temp);
		
		free(temp);
		temp = NULL;
		if (strchr(*st_line, '\n') != NULL)
		{
			cnt = 1;
			break;
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
	int	cnt;

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
	return(rtrn);
}


char	*get_next_line(int fd, int BUFFER_SIZE)
{
		
	static char	*st_line = NULL;
	char 		*rt_line;
	int		cnt;

	if (st_line == NULL) 
	{      
        	st_line = malloc(1);
		if (!st_line)
			return (NULL);
        	st_line[0] = '\0';
	}
	if ( fd < 0 || BUFFER_SIZE < 1)
		return (NULL);

	// Run 1 - st_line is empty - needs to be initialized
	// Run 2+ - st_line can have remaining characters or can be empty if buffer was ending with \n or if we reached end of file


	// We run buffer function, will get status of file and buffer as return value
	// 
	int result = buf_work(&st_line, fd, BUFFER_SIZE);
	if (result == -1)
		return (NULL);
	else if (result == 1)
	{
		return (line_cut(&st_line));
	}
	rt_line = ft_strdup(st_line);
	free(st_line);
	st_line = NULL;
	return (rt_line);
}



#include <fcntl.h>

int	main(void)
{
	int	BUFFER_SIZE = 10;
	char	*toprint;
	
	int fd = open("bigline.txt", O_RDONLY | O_CREAT);
	


	
	/*printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));*/
	
	
	
	
	while ((toprint = get_next_line(fd, BUFFER_SIZE)) != NULL )
	{
		printf("%s", toprint);
	}

	close(fd);

	return (0);


	return (0);
}