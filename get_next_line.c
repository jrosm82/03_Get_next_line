/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 21:46:58 by jrosmari          #+#    #+#             */
/*   Updated: 2023/02/06 22:11:12 by jrosmari         ###   ########.fr       */
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

char    *ft_strcpy(char *s1, char *s2)
{
      int i;
 
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

char	*get_next_line(int fd)
{
	char		*buf;
	char		*new_line_ptr;
	static char	backup[16384];
	static char	*backup_ptr = backup;
	int			read_len;
	int			backup_len;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';
	backup_len = ft_strlen(backup_ptr);
	new_line_ptr = ft_strchr(backup_ptr, '\n');
	while (new_line_ptr == NULL)
	{
		read_len = read(fd, buf, BUFFER_SIZE);
		if (read_len <= 0)
		{
			free(buf);
			if (backup_len == 0)
				return (NULL);
			buf = ft_strdup(backup_ptr);
			backup_ptr = backup;
			backup_ptr[0] = '\0';
			return (buf);
		}
		buf[read_len] = '\0';
		ft_strcpy(backup_ptr + backup_len, buf);
		backup_len += read_len;
		new_line_ptr = ft_strchr(backup_ptr, '\n');
	}
	free(buf);
	buf = ft_strndup(backup_ptr, new_line_ptr - backup_ptr + 1);
	backup_len -= (new_line_ptr - backup_ptr + 1);
	ft_memmove(backup_ptr, new_line_ptr + 1, backup_len + 1);
	return (buf);
}
/*
#include <fcntl.h>

int	main(void)
{
	char	*toprint;
	int	BUFFER_SIZE = 50;
	int fd = open("big_line_no_nl.txt", O_RDONLY | O_CREAT);


	
	//printf("\n");

	while ((toprint = get_next_line(fd, BUFFER_SIZE)) != NULL )
	{
		printf("%s", toprint);
	}

	close(fd);

	return (0);
}*/