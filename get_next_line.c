#include "get_next_line.h"

void	gnl_free_allocate(char **line, char **buf)
{
	if (*line != NULL)
		free(*line);
	if (*buf != NULL)
		free(*buf);
}

int	remainder_handler(char **remainder, char **line, char **buf)
{
	char	*remainder_two;

	if (*remainder == NULL || **remainder == '\0')
		return (0);
	remainder_two = get_remainder(*remainder);
	if (remainder_two != NULL)
	{
		*remainder_two = '\0';
		if (add_to_line(*remainder, line) == NULL)
			return (-1);
		*remainder = remainder_two + 1;
		return (1);
	}
	else
	{
		if (add_to_line(*remainder, line) == NULL)
			return (-1);
		free(*buf);
		*remainder = NULL;
		return (0);
	}
}

int	gnl_init_checks(char **line, char **remainder, char **buf)
{
	int	handler;

	if (line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	*line = NULL;
	handler = remainder_handler(remainder, line, buf);
	if (handler != 0)
		return (handler);
	if (*remainder != NULL && *(*remainder - 1) == '\0')
		free(*buf);
	*buf = (char *)malloc(BUFFER_SIZE + 1);
	if (*buf == NULL)
		return (-1);
	return (0);
}

int	gnl_init_return(char **line, char **buf, long length_read)
{
	if (length_read == 0)
	{
		(*buf)[length_read] = '\0';
		if (add_to_line((*buf), line) == NULL)
			return (-1);
	}
	free(*buf);
	if (length_read <= 0)
		return (length_read);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	long		length_read;
	static char	*remainder;
	static char	*buf;
	int			init_checks;

	init_checks = gnl_init_checks(line, &remainder, &buf);
	if (init_checks != 0)
		return (init_checks);
	length_read = read(fd, buf, BUFFER_SIZE);
	while (length_read > 0)
	{
		buf[length_read] = '\0';
		remainder = get_remainder(buf);
		if (remainder != NULL)
			*(remainder++) = '\0';
		if (add_to_line(buf, line) == NULL)
			return (-1);
		if (remainder != NULL)
			return (1);
		length_read = read(fd, buf, BUFFER_SIZE);
	}
	return (gnl_init_return(line, &buf, length_read));
}
