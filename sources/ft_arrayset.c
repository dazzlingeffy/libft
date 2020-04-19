//
// Created by ira on 18.04.2020.
//

#include "libft.h"

int				*ft_arrayset(int *array, int n, size_t len)
{
	int 		*t;

	t = array;
	while (len--)
		*(t++) = n;
	return (array);
}
