#include "../../include/cube3d.h"

int	validate_texture_files(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!scene->texture_paths[i])
			return (print_error("Error\nMissing texture path"), 0);
		if (!check_file_extension(scene->texture_paths[i], ".xpm"))
			return (print_error("Error\nInvalid texture file extension"), 0);
		if (!check_texture_accessibility(scene->texture_paths[i]))
			return (print_error("Error\nCannot access texture file"), 0);
		i++;
	}
	return (1);
}

int	validate_color_values(t_color *color)
{
	if (color->r < 0 || color->r > 255)
		return (print_error("Error\nInvalid red color value"), 0);
	if (color->g < 0 || color->g > 255)
		return (print_error("Error\nInvalid green color value"), 0);
	if (color->b < 0 || color->b > 255)
		return (print_error("Error\nInvalid blue color value"), 0);
	return (1);
}

int	validate_scene_elements(t_scene *scene)
{
	if (!validate_texture_files(scene))
		return (0);
	if (!validate_color_values(&scene->floor_color))
		return (0);
	if (!validate_color_values(&scene->ceiling_color))
		return (0);
	if (!validate_map_format(scene))
		return (0);
	return (1);
}

int	check_file_extension(char *filename, char *extension)
{
	int	filename_len;
	int	ext_len;

	if (!filename || !extension)
		return (0);
	filename_len = ft_strlen(filename);
	ext_len = ft_strlen(extension);
	if (filename_len < ext_len)
		return (0);
	return (ft_strcmp(filename + filename_len - ext_len, extension) == 0);
}

int	check_texture_accessibility(char *path)
{
	int	fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}
