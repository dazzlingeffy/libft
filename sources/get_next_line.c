#include "get_next_line.h"

static char 	*fill_buflie(int fd, char *bufline)
{
	char	t[BUFF_SIZE + 1];
	ssize_t	ret;

	while ((ret = read(fd, t, BUFF_SIZE)) > 0)
	{
		t[ret] = '\0';
		bufline = ft_strjoin(bufline, t);
	}
	return (bufline);
}

int 	get_next_line(int fd, char **line)
{
	static char		*bufline;
	size_t			i;

	if (fd < 0 || line == NULL || read(fd, bufline, 0) < 0)
		return (-1);
	if (bufline == NULL)
		if (!(bufline = (char*)malloc(sizeof(char) * BUFF_SIZE + 1)))
			return (-1);
	i = 0;
	bufline = fill_buflie(fd, bufline);
	if (bufline)
	{
		while (bufline[i] != '\n' && bufline[i])
			i++;
		if (i == 0 && bufline[i] == '\n' && bufline[i + 1])
		{
			(*line) = ft_strdup("");
			bufline = &bufline[i + 1];
			return (1);
		}
		if (i > 0)
		{
			(*line) = ft_strsub(bufline, 0, i);
			bufline = &bufline[i + 1];
			return (1);
		}
	}
	else
		(*line) = ft_strdup("");
	return (0);
}