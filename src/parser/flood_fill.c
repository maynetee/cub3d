/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteichma <mteichma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:17:37 by mteichma          #+#    #+#             */
/*   Updated: 2025/08/06 00:12:25 by mteichma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static int	enqueue_neighbor(t_flood_data *data, int i, int j)
{
	char	c;
	int		idx;

	if (i < 0 || j < 0 || i >= data->map->height || j >= data->map->width)
		return (1);
	c = data->map->grid[i][j];
	if (c == ' ' || c == '\0')
		return (1);
	idx = i * data->map->width + j;
	if (c != '1' && !data->vis[idx])
	{
		data->vis[idx] = 1;
		(*(data->top))++;
		data->stack[*(data->top)].x = j;
		data->stack[*(data->top)].y = i;
	}
	return (0);
}

static int	check_flood_conditions(t_map *m, int *vis, int i, int j)
{
	if (i < 0 || j < 0 || i >= m->height || j >= m->width)
		return (1);
	if (m->grid[i][j] == ' ' || m->grid[i][j] == '\0')
		return (1);
	if (m->grid[i][j] == '1' || vis[i * m->width + j])
		return (0);
	return (2);
}

static int	alloc_flood_stack(t_flood_data *data, t_map *m)
{
	data->stack = malloc(sizeof(t_point) * m->height * m->width);
	if (!data->stack)
		return (-1);
	return (0);
}

static int	flood_loop(t_flood_data *data, int *t)
{
	t_point	cur;

	while (*t >= 0)
	{
		cur = data->stack[*t];
		(*t)--;
		if (enqueue_neighbor(data, cur.y + 1, cur.x) || enqueue_neighbor(data,
				cur.y - 1, cur.x) || enqueue_neighbor(data, cur.y, cur.x + 1)
			|| enqueue_neighbor(data, cur.y, cur.x - 1))
		{
			return (1);
		}
	}
	return (0);
}

int	flood_fill(t_map *m, int *vis, int i, int j)
{
	t_flood_data	data;
	int				t;
	int				cond_result;

	cond_result = check_flood_conditions(m, vis, i, j);
	if (cond_result != 2)
		return (cond_result);
	data.map = m;
	data.vis = vis;
	if (alloc_flood_stack(&data, m) == -1)
		return (-1);
	t = 0;
	data.stack[0].x = j;
	data.stack[0].y = i;
	vis[i * m->width + j] = 1;
	data.top = &t;
	if (flood_loop(&data, &t))
	{
		free(data.stack);
		return (1);
	}
	free(data.stack);
	return (0);
}
