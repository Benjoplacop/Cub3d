/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:16:06 by bhennequ          #+#    #+#             */
/*   Updated: 2023/09/12 13:30:22 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

char	*ft_strjoin2(char *s1, const char *s2)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		tmp[j++] = s1[i++];
	i = 0;
	while (s2[i])
		tmp[j++] = s2[i++];
	tmp[j] = 0;
	free(s1);
	return (tmp);
}

char	*read_str(int fd, char *str)
{
	char	*buff;
	int		read_size;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	read_size = 1;
	while (ft_strchr(str, '\n') == 0 && read_size != 0 && str)
	{
		read_size = read(fd, buff, BUFFER_SIZE);
		if (read_size == -1)
		{
			free(buff);
			free(str);
			return (NULL);
		}
		else if (read_size == 0)
			break ;
		buff[read_size] = '\0';
		str = ft_strjoin2(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_line(char *str)
{
	char	*tab;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	tab = ft_calloc((i + 2), sizeof(char));
	if (!tab)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		tab[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		tab[i] = str[i];
		i++;
	}
	return (tab);
}

char	*next_line(char *str)
{
	char	*tab;
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	tab = ft_calloc((ft_strlen(str) - i + 1), sizeof(char));
	if (!tab)
		return (NULL);
	j = 0;
	i++;
	while (str[i])
		tab[j++] = str[i++];
	free(str);
	return (tab);
}

char	*get_next_line(int fd, int fin)
{
	char		*line;
	static char	*str[1024];

	if (fin == 1)
	{
		free(str[fd]);
		str[fd] = NULL;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!str[fd])
		str[fd] = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	str[fd] = read_str(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = get_line(str[fd]);
	str[fd] = next_line(str[fd]);
	return (line);
}
