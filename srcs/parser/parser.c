#include "minirt.h"

void	parse_r(char **spl, t_scene *scene)
{
	int	width;
	int	height;

	if (scene->width || scene->height
		|| rt_atof(spl[1], spl, scene) <= 0 || rt_atof(spl[2], spl, scene) <= 0)
	{
		ft_free_array(spl);
		ft_exit(scene, "Resolution is incorrect", EXIT_FAILURE);
	}
	scene->width = (int)rt_atof(spl[1], spl, scene);
	scene->height = (int)rt_atof(spl[2], spl, scene);
	mlx_get_screen_size(&width, &height);
	if (scene->width > width)
		scene->width = width;
	if (scene->height > height)
		scene->height = height;
}

void	parse_a(char **spl, t_scene *scene)
{
	if (scene->ambient.ratio >= 0 || rt_atof(spl[1], spl, scene) < 0
		|| rt_atof(spl[1], spl, scene) > 1.0)
	{
		ft_free_array(spl);
		ft_exit(scene,
			"Shine bright like a diamond but in range [0.0,1.0]", EXIT_FAILURE);
	}
	scene->ambient.ratio = rt_atof(spl[1], spl, scene);
	scene->ambient.color = split_colors(spl[2], spl, scene);
	scene->ambient.intense = light_bright(scene->ambient.color,
			scene->ambient.ratio);
}

void	parse_params(char **splitted, t_scene *scene)
{
	if (!(ft_strcmp(splitted[0], "R")) && arr_len(splitted) == 3)
		parse_r(splitted, scene);
	else if (!(ft_strcmp(splitted[0], "A")) && arr_len(splitted) == 3)
		parse_a(splitted, scene);
	else if (!(ft_strcmp(splitted[0], "c")) && arr_len(splitted) == 4)
		parse_c(splitted, scene);
	else if (!(ft_strcmp(splitted[0], "l")) && arr_len(splitted) == 4)
		parse_l(splitted, scene);
	else if (!(ft_strcmp(splitted[0], "#")))
		ft_strcmp(splitted[0], "#");
	else
		parse_obj(splitted, scene);
}

void	parse_end(t_scene *scene)
{
	if (!scene->width)
		ft_exit(scene, "Bro I really need R to show you cool picture",
			EXIT_FAILURE);
	if (!scene->camera)
		ft_exit(scene, "Without camera I'll have render it in my imagination",
			EXIT_FAILURE);
	if (scene->ambient.ratio == -1)
		ft_exit(scene, "Oops, you forgot A", EXIT_FAILURE);
	calc_cam(scene->camera, scene->width, scene->height);
}

void	parse_scene(int fd, t_scene *scene)
{
	char	*line;
	char	**splitted;
	int		i;

	while (1)
	{
		i = get_next_line(fd, &line);
		if (i == -1)
			ft_exit(scene, "Cannot read from file", EXIT_FAILURE);
		if (!check_str_set(line, " 	"))
		{
			splitted = rt_split_set(line, " 	", scene);
			parse_params(splitted, scene);
			ft_free_array(splitted);
		}
		else
			free (line);
		if (i == 0)
		{
			close(fd);
			parse_end(scene);
			break ;
		}
	}
}
