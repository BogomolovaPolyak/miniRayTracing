/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:07:56 by natali            #+#    #+#             */
/*   Updated: 2021/04/26 22:34:47 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	bitmap_file_header(t_scene *sc, int padding_size, int fd)
{
	unsigned char	header[14];
	int				size;

	ft_bzero(header, 14);
	size = 54 + (sc->img.bits_per_pixel / 8 * sc->height
			+ padding_size) * sc->width;
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(size);
	header[3] = (unsigned char)(size >> 8);
	header[4] = (unsigned char)(size >> 16);
	header[5] = (unsigned char)(size >> 24);
	header[10] = (unsigned char)(54);
	write(fd, header, 14);
}

int	bitmap_info_header(t_scene *sc, int fd)
{
	unsigned char	info[40];
	int				ret;

	ft_bzero(info, 40);
	info[0] = (unsigned char)(40);
	info[4] = (unsigned char)((int)sc->width);
	info[5] = (unsigned char)((int)sc->width >> 8);
	info[6] = (unsigned char)((int)sc->width >> 16);
	info[7] = (unsigned char)((int)sc->width >> 24);
	info[8] = (unsigned char)((int)sc->height);
	info[9] = (unsigned char)((int)sc->height >> 8);
	info[10] = (unsigned char)((int)sc->height >> 16);
	info[11] = (unsigned char)((int)sc->height >> 24);
	info[12] = (unsigned char)(1);
	info[14] = (unsigned char)(sc->img.bits_per_pixel);
	ret = write(fd, info, 40);
	return (ret);
}

void	image_to_bmp(t_scene *sc)
{
	int				padding_size;
	int				fd;
	unsigned char	padding[3];
	int				i;

	ft_bzero(padding, 3);
	padding_size = (4 - (sc->height * sc->img.bits_per_pixel / 8) % 4) % 4;
	fd = open("Superimage.bmp", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		ft_exit(sc, "Cannot create bmp file", EXIT_FAILURE);
	bitmap_file_header(sc, padding_size, fd);
	bitmap_info_header(sc, fd);
	i = sc->height;
	while (i >= 0)
	{
		write(fd, sc->img.addr + (i * sc->width
				* sc->img.bits_per_pixel / 8), sc->img.line_length);
		write(fd, padding, padding_size);
		i--;
	}
	close(fd);
	ft_exit(sc, "Your image is ready, bye", EXIT_SUCCESS);
}
