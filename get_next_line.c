/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrosmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 21:46:58 by jrosmari          #+#    #+#             */
/*   Updated: 2023/02/05 17:56:35 by jrosmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	srclen;
	size_t	i;

	srclen = 0;
	i = 0;
	while (src[srclen] != '\0')
		srclen++;
	if (destsize == 0)
		return (srclen);
	while (src[i] != '\0' && i < destsize - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i == destsize - 1)
		dest[destsize - 1] = '\0';
	else
		dest[i] = '\0';
	return (srclen);
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

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	srclen;
	size_t	destlen;
	size_t	i;

	srclen = 0;
	destlen = 0;
	while (src[srclen] != '\0')
		srclen++;
	if (size == 0)
		return (srclen);
	while (dest[destlen] != '\0' && destlen < size)
		destlen++;
	if (destlen == size)
		return (srclen + size);
	i = destlen;
	while (src[i - destlen] != '\0' && i < size - 1)
	{
		dest[i] = src[i - destlen];
		i++;
	}
	dest[i] = '\0';
	return (destlen + srclen);
}

char	*get_next_line(int fd, int BUFFER_SIZE)
{
	
	char		*buf;
	static char	*line ;
	char		*dup;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	read(fd, buf, BUFFER_SIZE);
	//line = ft_strdup(buf);
	//ft_strlcat(line, buf, BUFFER_SIZE );

	return (buf);
}



#include <fcntl.h>

int	main(void)
{
	char	*toprint;
	int	BUFFER_SIZE = 50;
	int fd = open("toread.txt", O_RDONLY | O_CREAT);


	 if (fd == -1) {
        perror("open");
        return 1;
    }

    char *line;
    while ((line = return_line(fd, BUFFER_SIZE)) != NULL) {
        printf("%s\n", line);
        free(line);
    }

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;


	/*
	while ((toprint = returnline(fd, BUFFER_SIZE)) != NULL)
	{
		printf("%s\n", toprint);
		free(toprint);
	}
	*/
	/*
	printf("\nNEXT LINE\n");
	printf("%s", returnline(fd, BUFFER_SIZE));
	printf("\nNEXT LINE\n");
	printf("%s", returnline(fd, BUFFER_SIZE));
	printf("\nNEXT LINE\n");
	printf("%s", returnline(fd, BUFFER_SIZE));
	printf("\nNEXT LINE\n");
	printf("%s", returnline(fd, BUFFER_SIZE));
	printf("\nNEXT LINE\n");
	printf("%s", returnline(fd, BUFFER_SIZE));
	printf("\nNEXT LINE\n");
	printf("%s", returnline(fd, BUFFER_SIZE));
	printf("\nNEXT LINE\n");
	printf("%s", returnline(fd, BUFFER_SIZE));
	printf("\nNEXT LINE\n");
	printf("%s", returnline(fd, BUFFER_SIZE));
	printf("\nNEXT LINE\n");

	close(fd);*/

	return (0);
}

