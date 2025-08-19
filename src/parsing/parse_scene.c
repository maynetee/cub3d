#include "../../include/cube3d.h"

static void	free_split_array(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	parse_scene_file(char *filename, t_scene *scene)
{
	int	fd;
	int	result;

	if (!check_file_extension(filename, ".cub"))
		return (print_error("Error\nInvalid file extension"), 0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_error("Error\nCannot open scene file"), 0);
	ft_memset(scene, 0, sizeof(t_scene));
	result = parse_scene_elements(fd, scene);
	if (result)
		result = parse_map_data(fd, scene);
	close(fd);
	if (!result)
		cleanup_scene_data(scene);
	return (result);
}

int	parse_scene_elements(int fd, t_scene *scene)
{
	char	*line;
	int		result;

	result = 1;
	line = NULL;
	while (result && scene->elements_found < 6)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) > 1 && line[0] != '\n')
		{
			if (line[0] == 'N' || line[0] == 'S'
				|| line[0] == 'W' || line[0] == 'E')
				result = parse_texture_line(line, scene);
			else if (line[0] == 'F' || line[0] == 'C')
				result = parse_color_line(line, scene);
			else if (line[0] == '1' || line[0] == '0')
			{
				free(line);
				break ;
			}
		}
		free(line);
		line = NULL;
	}
	return (result && scene->elements_found == 6);
}

int	parse_texture_line(char *line, t_scene *scene)
{
	char	**split;
	int		index;
	int		result;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2])
		return (free_split_array(split),
			print_error("Error\nInvalid texture format"), 0);
	index = -1;
	if (!ft_strcmp(split[0], "NO"))
		index = NO_TEX;
	else if (!ft_strcmp(split[0], "SO"))
		index = SO_TEX;
	else if (!ft_strcmp(split[0], "WE"))
		index = WE_TEX;
	else if (!ft_strcmp(split[0], "EA"))
		index = EA_TEX;
	if (index == -1 || scene->texture_paths[index])
		return (free_split_array(split),
			print_error("Error\nDuplicate or invalid texture"), 0);
	scene->texture_paths[index] = ft_strdup_safe(split[1]);
	scene->elements_found++;
	result = (scene->texture_paths[index] != NULL);
	free_split_array(split);
	return (result);
}

int	parse_color_line(char *line, t_scene *scene)
{
	char	**split;
	char	**rgb_split;
	t_color	*color;
	int		result;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2])
		return (free_split_array(split), 
			print_error("Error\nInvalid color format"), 0);
	color = NULL;
	if (!ft_strcmp(split[0], "F") && scene->floor_color.hex == 0)
		color = &scene->floor_color;
	else if (!ft_strcmp(split[0], "C") && scene->ceiling_color.hex == 0)
		color = &scene->ceiling_color;
	if (!color)
		return (free_split_array(split),
			print_error("Error\nDuplicate or invalid color"), 0);
	rgb_split = ft_split(split[1], ',');
	if (!rgb_split || !rgb_split[0] || !rgb_split[1] || !rgb_split[2]
		|| rgb_split[3])
		return (free_split_array(split), free_split_array(rgb_split),
			print_error("Error\nInvalid RGB format"), 0);
	color->r = ft_atoi(rgb_split[0]);
	color->g = ft_atoi(rgb_split[1]);
	color->b = ft_atoi(rgb_split[2]);
	color->hex = create_color_hex(color->r, color->g, color->b);
	scene->elements_found++;
	result = validate_color_values(color);
	free_split_array(split);
	free_split_array(rgb_split);
	return (result);
}
