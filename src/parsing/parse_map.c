#include "../../include/cube3d.h"

int	parse_map_data(int fd, t_scene *scene)
{
	char	*line;
	char	**temp_map;
	int		line_count;

	line_count = 0;
	temp_map = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) > 1)
		{
			temp_map = add_line_to_map(temp_map, line, line_count);
			if (!temp_map)
				return (0);
			line_count++;
		}
		free(line);
	}
	scene->map = temp_map;
	scene->map_height = line_count;
	if (line_count > 0)
		scene->map_width = calculate_map_width(scene->map, line_count);
	return (line_count > 0);
}

char	**add_line_to_map(char **map, char *line, int line_count)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (line_count + 2));
	if (!new_map)
		return (print_error("Error\nMemory allocation failed"), NULL);
	i = 0;
	while (i < line_count)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[line_count] = process_map_line(line);
	if (!new_map[line_count])
	{
		free(new_map);
		return (NULL);
	}
	new_map[line_count + 1] = NULL;
	if (map)
		free(map);
	return (new_map);
}

char	*process_map_line(char *line)
{
	char	*processed;
	int		len;
	int		i;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	processed = malloc(len + 1);
	if (!processed)
		return (print_error("Error\nMemory allocation failed"), NULL);
	i = 0;
	while (i < len)
	{
		if (line[i] == ' ' || line[i] == '0' || line[i] == '1'
			|| line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
			processed[i] = line[i];
		else
			return (free(processed),
				print_error("Error\nInvalid map character"), NULL);
		i++;
	}
	processed[len] = '\0';
	return (processed);
}

int	calculate_map_width(char **map, int height)
{
	int	max_width;
	int	current_width;
	int	i;

	max_width = 0;
	i = 0;
	while (i < height)
	{
		current_width = ft_strlen(map[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

int	normalize_map_lines(t_scene *scene)
{
	int		i;
	char	*new_line;

	i = 0;
	while (i < scene->map_height)
	{
		if ((int)ft_strlen(scene->map[i]) < scene->map_width)
		{
			new_line = pad_line_with_spaces(scene->map[i], scene->map_width);
			if (!new_line)
				return (0);
			free(scene->map[i]);
			scene->map[i] = new_line;
		}
		i++;
	}
	return (1);
}
