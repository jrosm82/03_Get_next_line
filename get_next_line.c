/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 21:46:58 by jrosmari          #+#    #+#             */
/*   Updated: 2023/02/08 15:51:29 by jrosmari         ###   ########.fr       */
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

char	*ft_strndup(const char *s, size_t n)
{
	char			*res;
	unsigned int	i;

	i = 0;
	res = malloc(sizeof(char) * (n + 1));
	if (res == NULL)
		return (NULL);
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = s2[i];
	return (s1);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{	
	size_t	i;

	i = 0;
	if (dest == src)
		return (dest);
	if (dest < src)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{	
		i = n + 1;
		while (--i)
			((unsigned char *)dest)[i - 1] = ((unsigned char *)src)[i - 1];
	}
	return (dest);
}

static int	fts_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (fts_strlen(s1) + fts_strlen(s2) + 1));
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

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (*(src + i) != '\0' && i < n)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	while (i < n)
	{
		*(dest + i) = '\0';
		i++;
	}
	return (dest);
}


char *ft_strcat(char *dest, const char *src)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*get_next_line(int fd, int BUFFER_SIZE)
{
	char		*buffer;	
	static char	*st_line;
	char 		*temp;
	int		cnt;
	
	if ( st_line == NULL)
		st_line = ft_strnew(1);

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);	
	buffer[BUFFER_SIZE] = '\0';
	
	while ((ft_strchr(st_line, '\n') == NULL) && ((cnt = read(fd, buffer, BUFFER_SIZE)) != 0))
	{		
		if (buffer == NULL)
			return (NULL);
		temp = (char *)malloc(sizeof(char)* (ft_strlen(st_line) + ft_strlen(buffer) + 1));
		temp = ft_strjoin(st_line, buffer);
		st_line = ft_strdup(temp);
	}

	if (cnt == 0 && st_line != NULL)
	{
		temp = ft_strdup(st_line);
		st_line = ft_strdup(NULL);
		return(temp);
	}
	else if (cnt == 0 && st_line == NULL)
		return NULL;
	free(temp);
	free(buffer);

	if( cnt < BUFFER_SIZE)
		return (ft_strdup(st_line));
	else
	{
		int	i = 0;
		while (st_line[i] != '\n')
			i++;	
		temp = ft_substr(st_line, 0, i + 1);
		int 	j = i;
		while (st_line[i] != '\0')	
			i++;
		st_line = ft_substr(st_line, j + 1, i - j - 1);

		return (temp);
	}
}


#include <fcntl.h>

int	main(void)
{
	char	*toprint;
	int	BUFFER_SIZE =  5;
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