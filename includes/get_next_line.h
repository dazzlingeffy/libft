#ifndef GET_NEXT_LINE_GET_NEXT_LINE_H
# define GET_NEXT_LINE_GET_NEXT_LINE_H
# define BUFF_SIZE 1024
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"


typedef struct		s_file
{
	int				fd;
	char			*str;
	struct s_file	*next;
}					t_file;


int 	get_next_line(int fd, char **line);

#endif //GET_NEXT_LINE_GET_NEXT_LINE_H
