#include "get_next_line.h"

long	ft_strlen(char *str)
{
	long	position;

	if (str == NULL)
		return (0);
	position = 0;
	while (str[position] != '\0')
		position++;
	return (position);
}

char	*get_remainder(char *buf)
{
	long	position;

	position = 0;
	while (*(buf + position) != '\0')
	{
		if (*(buf + position) == '\n')
			return (buf + position);
		position++;
	}
	return (NULL);
}

char	*gnl_ATL_front(char **line_progress, char **line, long position)
{
	(*line_progress)[position] = '\0';
	if (*line != NULL)
		free(*line);
	*line = *line_progress;
	return (*line_progress);
}

char	*add_to_line(char *buf, char **line)
{
	long	position;
	long	buf_length;
	long	line_length;
	char	*line_progress;

	position = 0;
	buf_length = ft_strlen(buf);
	line_length = ft_strlen(*line);
	line_progress = (char *)malloc(buf_length + line_length + 1);
	if (line_progress == NULL)
	{
		gnl_free_allocate(line, &buf);
		return (NULL);
	}
	while (position < line_length)
	{
		line_progress[position] = (*line)[position];
		position++;
	}
	while (position < buf_length + line_length)
	{
		line_progress[position] = buf[position - line_length];
		position++;
	}
	return (gnl_ATL_front(&line_progress, line, position));
}
