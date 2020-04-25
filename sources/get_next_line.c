#include "get_next_line.h"
#include <stdio.h>

static char	*ft_strsubchr(const char *s, char c)
{
	char	*ptr;

	if (!(ptr = ft_strchr(s, c)))
		return (NULL);
	return (ft_strsub(s, 0, ptr - s));
}

static t_file	*new_file(const int fd)
{
	t_file *new;

	if ((new = (t_file *)ft_memalloc(sizeof(t_file))))
	{
		new->fd = fd;
		new->str = NULL;
	}
	return (new);
}

static t_file	*get_file(const int fd, t_file **head)
{
	t_file *lst;

	if (!(*head))
		return (*head = new_file(fd));
	lst = *head;
	while (lst->next && lst->fd != fd)
		lst = lst->next;
	return ((lst->fd == fd) ? lst : (lst->next = new_file(fd)));
}

static int		str_divide(char **str, char **line)
{
	char	*new;
	char	*div;

	if (!(*line = ft_strsubchr(*str, '\n')))
		return (-1);
	div = ft_strchr(*str, '\n');
	div++;
	if (!ft_strlen(div))
	{
		free(*str);
		*str = NULL;
		return (1);
	}
	new = ft_strdup(div);
	free(*str);
	*str = new;
	return ((new) ? 1 : -1);
}

int				get_next_line(const int fd, char **line)
{
	static t_file	*head = NULL;
	t_file			*f;
	char			buff[BUFF_SIZE + 1];
	ssize_t			size;
	char			*tmp;


	if (fd < 0 || !line || read(fd, buff, 0) < 0 || !(f = get_file(fd, &head)))
		return (-1);
	while (!ft_strchr(f->str, '\n'))
	{
		if (!(size = read(fd, buff, BUFF_SIZE)))
		{
			if (!(*line = f->str))
				return (0);
			f->str = NULL;
			return (1);
		}
		buff[size] = '\0';
		tmp = f->str;
		f->str = ft_strjoin(f->str, buff);
		free(tmp);
		if (!f->str)
			return (-1);
	}
	return (str_divide(&(f->str), line));
}

//##############################################
//
//int				ft_next_line(char **hold, int fd, char **line)
//{
//	char		*tmp;
//	int			len;
//
//	len = 0;
//	while (hold[fd][len] != '\n' && hold[fd][len] != '\0')
//		len++;
//	if (hold[fd][len] == '\n')
//	{
//		*line = ft_strsub(hold[fd], 0, len);
//		tmp = ft_strdup(hold[fd] + len + 1);
//		free(hold[fd]);
//		hold[fd] = tmp;
//		if (hold[fd][0] == '\0')
//			ft_strdel(&hold[fd]);
//	}
//	else if (hold[fd][len] == '\0')
//	{
//		*line = ft_strdup(hold[fd]);
//		ft_strdel(&hold[fd]);
//	}
//	return (1);
//}
//
//int				get_next_line(const int fd, char **line)
//{
//	static char *hold[10240];
//	char		buf[BUFF_SIZE + 1];
//	char		*tmp;
//	int			ret;
//
//	if (fd < 0 || fd > 10240 || !line || (read(fd, NULL, 0) < 0))
//		return (-1);
//	while (!ft_strchr(hold[fd], '\n'))
//	{
//		if (!(ret = read(fd, buf, BUFF_SIZE)))
//		{
//			if (!(*line = hold[fd]))
//				return (0);
//			hold[fd] = NULL;
//			return (1);
//		}
//		buf[ret] = '\0';
//		tmp = hold[fd];
//		hold[fd] = ft_strjoin(hold[fd], buf);
//		free(tmp);
//		if (!hold[fd])
//			return (-1);
//	}
//	return (ft_next_line(hold, fd, line));
//}

////static char 	*fill_buflie(int fd, char *bufline)
////{
////	char	t[BUFF_SIZE + 1];
////	ssize_t	ret;
////
////	while ((ret = read(fd, t, BUFF_SIZE)) >= 0)
////	{
////		if (ret == 0) {
////			if (!bufline)
////				return (NULL);
////			return (bufline);
////		}
////		t[ret] = '\0';
////		bufline = ft_strjoin(bufline, t);
////	}
////	return (bufline);
////}
////
////int 	get_next_line(int fd, char **line)
////{
////	static char		*bufline;
////	size_t			i;
////
////	if (fd < 0 || line == NULL || read(fd, bufline, 0) < 0)
////		return (-1);
////	if (bufline == NULL)
////		if (!(bufline = (char*)malloc(sizeof(char) * BUFF_SIZE + 1)))
////			return (-1);
////	i = 0;
////	bufline = fill_buflie(fd, bufline);
////	if (bufline)
////	{
////		while (bufline[i] != '\n' && bufline[i])
////			i++;
////		if (i == 0 && bufline[i] == '\n' && bufline[i + 1])
////		{
////			(*line) = ft_strdup("");
////			bufline = &bufline[i + 1];
////			return (1);
////		}
////		if (i > 0)
////		{
////			(*line) = ft_strsub(bufline, 0, i);
////			bufline = &bufline[i + 1];
////			return (1);
////		}
////	}
////	else
////		(*line) = ft_strdup("");
////	return (0);
////}
