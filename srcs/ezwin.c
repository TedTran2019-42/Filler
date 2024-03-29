/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ezwin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 00:55:37 by ttran             #+#    #+#             */
/*   Updated: 2018/01/23 00:55:39 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		closest_distance(t_fill *ted)
{
	int			i;
	int			n;
	int			tempdistance;

	tempdistance = 2000000000;
	n = 0;
	i = 0;
	while (ted->map[n])
	{
		while (ted->map[n][i])
		{
			if (ted->map[n][i] == ted->enemy ||
			ted->map[n][i] == ted->enemy - 32)
				leak_token(ted, i, n, &tempdistance);
			i++;
		}
		i = 0;
		n++;
	}
	return (tempdistance);
}

static void		losing_alg(t_fill *ted, t_maptemp *h)
{
	int			tmp;

	if (ted->distance == 999999999)
	{
		ted->x = h->norm_x;
		ted->y = h->norm_y;
		ted->distance = closest_distance(ted);
	}
	else
	{
		tmp = closest_distance(ted);
		if (tmp < ted->distance)
		{
			ted->x = h->norm_x;
			ted->y = h->norm_y;
			ted->distance = tmp;
		}
	}
}

static void		pls_win(t_fill *ted, int map_x, int map_y, t_maptemp *h)
{
	h->map_x = map_x;
	h->map_y = map_y;
	if (valid_placement(ted, h) == 1)
		losing_alg(ted, h);
}

/*
** A distance of zero means none of the pieces can be placed.
*/

int				ez_win(t_fill *ted)
{
	int			i;
	int			n;
	t_maptemp	*h;

	i = 0;
	n = 0;
	h = malloc(sizeof(t_maptemp));
	ted->ptr = h;
	ted->distance = 999999999;
	while (ted->map[n])
	{
		while (ted->map[n][i])
		{
			pls_win(ted, i, n, h);
			i++;
		}
		i = 0;
		n++;
	}
	if (ted->distance != 999999999)
	{
		ft_put_coordinates(ted);
		return (1);
	}
	return (0);
}
