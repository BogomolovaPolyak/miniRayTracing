#include "minirt.h"

void	lets_do_it(t_scene *scene, int save)
{
	create_win(scene, save);
	create_canvas(scene, save);
	mlx_key_hook(scene->win, press_key, scene);
	mlx_hook(scene->win, 17, 1L << 17, red_cross, scene);
	mlx_loop(scene->init);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;
	int		fd;
	int		save;

	scene = new_scene();
	save = 0;
	if (argc < 2 || argc > 3)
		ft_exit(scene, "Wrong number of arguments", EXIT_FAILURE);
	if (ft_strcmp(ft_strrchr(argv[1], '.'), ".rt"))
		ft_exit(scene, "Wrong filename", EXIT_FAILURE);
	if (argc == 3)
	{
		if (ft_strcmp(argv[2], "--save"))
			ft_exit(scene, "Wrong option", EXIT_FAILURE);
		else
			save = 1;
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exit(scene, "Cannot open file", EXIT_FAILURE);
	parse_scene(fd, scene);
	lets_do_it(scene, save);
}
