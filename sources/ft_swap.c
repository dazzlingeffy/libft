/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 23:59:23 by cmeowth           #+#    #+#             */
/*   Updated: 2019/12/28 23:59:23 by cmeowth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_swap(void *a, void *b, size_t size)
{
	void	*tmp;

	if ((tmp = ft_memalloc(size)))
	{
		ft_memcpy(tmp, a, size);
		ft_memcpy(a, b, size);
		ft_memcpy(b, tmp, size);
	}
	ft_memdel(&tmp);
}
