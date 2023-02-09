/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 21:46:58 by jrosmari          #+#    #+#             */
/*   Updated: 2023/02/09 19:33:25 by jrosmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	unsigned long	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[j] != '\0')
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	str[size] = '\0';
	while (size--)
		str[size] = '\0';
	return (str);
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


char	*get_next_line(int fd, int BUFFER_SIZE)
{
	char		*buffer;	
	static char	*st_line;
	char 		*temp;
	int		cnt;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	cnt = 0;
	while(ft_strchr(buffer, '\n') == NULL && (cnt = read(fd, buffer, BUFFER_SIZE)) > 0)
	{

		if (!buffer)
			return (NULL);		
		if (st_line == NULL)
			st_line = ft_strnew(0);
		if (cnt < BUFFER_SIZE)
		{
			buffer[cnt] = '\0';
			st_line = ft_strjoin(st_line, ft_substr(buffer, 0, cnt));
		}
		else
		{	
			st_line = ft_strjoin(st_line, buffer);
		}		
	}
	free(buffer);
	buffer = NULL;
	if (st_line == NULL)	
		return (NULL);
	else if (ft_strchr(st_line, '\n') == NULL)
	{
		temp = ft_strdup(st_line);
		free(st_line);	
		st_line = NULL;	
		return (temp);
	}
	else
	{
		cnt = 0;
		while (st_line[cnt] != '\n')
			cnt++;	
		temp = ft_substr(st_line, 0, cnt + 1);
		int 	j = cnt;
		while (st_line[cnt] != '\0')	
			cnt++;
		st_line = ft_substr(st_line, j + 1, cnt - j - 1);
		return (temp);
	}
}


#include <fcntl.h>

int	main(void)
{
	char	*toprint;
	int	BUFFER_SIZE =   2;
	int fd = open("toread.txt", O_RDONLY | O_CREAT);
	


	
	/*printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));
	printf("%s", get_next_line(fd, BUFFER_SIZE));*/
	
	
	
	while ((toprint = get_next_line(fd, BUFFER_SIZE)) != NULL )
	{
		printf("%s", toprint);
	}

	close(fd);

	return (0);
}