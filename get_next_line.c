#include "get_next_line.h"

int					check_buff(char *buff, char **tmp, char **line)
{
	char			*check;

	check = ft_strchr(buff, '\n');
	if (check != NULL)
	{
		*check = '\0';
		*line = ft_strjoin(*tmp, buff);
		free(*tmp);
		*tmp = ft_strdup(check + 1);
		free (buff);
		return (1);
	}
	return (0);
}

int					check_tmp(char **tmp, char **line)
{
	char			*check;

	check = ft_strchr(*tmp, '\n');
	if (check != NULL)
	{
		*check = '\0';
		*line = ft_strdup(*tmp);
		free(*tmp);
		*tmp = ft_strdup(check + 1);
		return (1);
	}
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	static char		*tmp = NULL;
	char			*buff;
	int				ret;

	buff = (char *)malloc(sizeof(char));
	if (tmp && check_tmp(&tmp, line))
			return (1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (check_buff(buff, &tmp, line))
			return (1);
		tmp = ft_strjoin(tmp, buff);
	}
	free(buff);
	if (ret == -1)
	{
		free(tmp);
		return (-1);
	}
	if (tmp == NULL)
		return (0);
	*line = tmp;
	return (1);
}
