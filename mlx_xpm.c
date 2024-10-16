/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_xpm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:39:34 by mrochedy          #+#    #+#             */
/*   Updated: 2024/10/12 19:08:15 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 ** xpm-read.c for MinilibX in
 **
 ** Made by Charlie Root
 ** Login   <ol@epitech.net>
 **
 ** Started on  Tue Dec 11 15:25:27 2001 olivier crouzet
 ** Last update Sat Oct  1 14:56:13 2005 Olivier Crouzet
 */

#include "mlx_int.h"

extern struct s_col_name	g_mlx_col_name[];

#define RETURN { if (colors) free(colors); if (tab) free(tab); \
		tab = (void *)0; if (colors_direct) free(colors_direct); \
		if (img) {XDestroyImage(img->image); \
				XFreePixmap(xvar->display,img->pix);free(img);} \
		return ((void *)0);}

char	*mlx_int_get_line(char *ptr, int *pos, int size)
{
	int	pos2;
	int	pos3;
	int	pos4;

	pos2 = mlx_int_str_str(ptr + *pos, "\"", size - *pos);
	if (pos2 == -1)
		return ((char *)0);
	pos3 = mlx_int_str_str(ptr + *pos + pos2 + 1, "\"", size - *pos - pos2 - 1);
	if (pos3 == -1)
		return ((char *)0);
	*(ptr + *pos + pos2) = 0;
	*(ptr + *pos + pos2 + 1 + pos3) = 0;
	pos4 = *pos + pos2 + 1;
	*pos += pos2 + pos3 + 2;
	return (ptr + pos4);
}

unsigned int	strlcpy_is_not_posix(char *dest, char *src, unsigned int size)
{
	unsigned int	count;
	unsigned int	i;

	count = 0;
	while (src[count] != '\0')
		++count;
	i = 0;
	while (src[i] != '\0' && i < (size - 1))
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (count);
}

char	*mlx_int_static_line(char **xpm_data, int *pos, int size)
{
	static char	*copy = 0;
	static int	len = 0;
	int			len2;
	char		*str;

	str = xpm_data[(*pos)++];
	len2 = strlen(str);
	if (len2 > len)
	{
		if (copy)
			free(copy);
		copy = malloc(len2 + 1);
		if (!copy)
			return ((char *)0);
		len = len2;
	}
	strlcpy_is_not_posix(copy, str, len2);
	return (copy);
}

int	mlx_int_get_col_name(char *str, int size)
{
	int	result;

	result = 0;
	while (size--)
		result = (result << 8) + *(str++);
	return (result);
}

int	mlx_int_get_text_rgb(char *name, char *end)
{
	int		i;
	char	buff[64];

	if (*name == '#')
		return (strtol(name + 1, 0, 16));
	if (end)
	{
		snprintf(buff, 64, "%s %s", name, end);
		name = buff;
	}
	i = 0;
	while (g_mlx_col_name[i].name)
	{
		if (!strcasecmp(g_mlx_col_name[i].name, name))
			return (g_mlx_col_name[i].color);
		i++;
	}
	return (0);
}

int	mlx_int_xpm_set_pixel(t_img *img, char *data, int opp, int col, int x)
{
	int	dec;

	dec = opp;
	while (dec--)
	{
		if (img->image->byte_order)
			*(data + x * opp + dec) = col & 0xFF;
		else
			*(data + x * opp + opp - dec - 1) = col & 0xFF;
		col >>= 8;
	}
}

void	*mlx_int_parse_xpm(t_xvar *xvar, void *info, int info_size, char *(*f)())
{
	int			pos;
	char		*line;
	char		**tab;
	char		*data;
	char		*clip_data;
	int			nc;
	int			opp;
	int			cpp;
	int			col;
	int			rgb_col;
	int			col_name;
	int			method;
	int			x;
	int			i;
	int			j;
	t_img		*img;
	t_xpm_col	*colors;
	int			*colors_direct;
	int			width;
	int			height;
	XImage		*clip_img;
	XGCValues	xgcv;
	Pixmap		clip_pix;

	colors = 0;
	colors_direct = 0;
	img = 0;
	tab = 0;
	pos = 0;
	line = f(info, &pos, info_size);
	if (!line)
		RETURN;
	tab = mlx_int_str_to_wordtab(line);
	if (!tab)
		RETURN;
	width = atoi(tab[0]);
	height = atoi(tab[1]);
	nc = atoi(tab[2]);
	cpp = atoi(tab[3]);
	if (!width || !height || !nc || !cpp)
		RETURN;
	free(tab);
	tab = 0;
	method = 0;
	if (cpp <= 2)
	{
		method = 1;
		colors_direct = malloc((cpp == 2 ? 65536 : 256) * sizeof(int));
		if (!colors_direct)
			RETURN;
	}
	else
		if (!(colors = malloc(nc * sizeof(*colors))))
			RETURN;
	clip_data = 0;
	i = nc;
	while (i--)
	{
		line = f(info, &pos, info_size);
		if (!line)
			RETURN;
		tab = mlx_int_str_to_wordtab(line + cpp);
		if (!tab )
			RETURN;
		j = 0;
		while (tab[j] && strcmp(tab[j++], "c"));
			if (!tab[j])
				RETURN;
		rgb_col = mlx_int_get_text_rgb(tab[j], tab[j + 1]);
		if (method)
			colors_direct[mlx_int_get_col_name(line, cpp)] = rgb_col;
		else
		{
			colors[i].name = mlx_int_get_col_name(line, cpp);
			colors[i].col = rgb_col;
		}
		free(tab);
		tab = (void *)0;
	}
	img = mlx_new_image(xvar, width, height);
	if (!img)
		RETURN;
	opp = img->bpp / 8;
	i = height;
	data = img->data;
	while (i--)
	{
		line = f(info, &pos, info_size);
		if (!line)
			RETURN;
		x = 0;
		while (x < width)
		{
			col = 0;
			col_name = mlx_int_get_col_name(line + cpp * x, cpp);
			if (method)
				col = colors_direct[col_name];
			else
			{
				j = nc;
				while (j--)
					if (colors[j].name == col_name)
					{
						col = colors[j].col;
						j = 0;
					}
			}
			if (col==-1)
				col = 0xFF000000;
			mlx_int_xpm_set_pixel(img, data, opp, col, x);
			++x;
		}
		data += img->size_line;
	}
	if (colors)
		free(colors);
	if (colors_direct)
		free(colors_direct);
	return (img);
}

int	mlx_int_file_get_rid_comment(char *ptr, int size)
{
	int	com_begin;
	int	com_end;

	com_begin = mlx_int_str_str_cote(ptr, "/*", size);
	while (com_begin != -1)
	{
		com_end = mlx_int_str_str(ptr + com_begin + 2, "*/",
			size - com_begin - 2);
		memset(ptr + com_begin, ' ', com_end + 4);
	}
	com_begin = mlx_int_str_str_cote(ptr, "//", size);
	while (com_begin != -1)
	{
		com_end = mlx_int_str_str(ptr + com_begin + 2, "\n",
			size - com_begin - 2);
		memset(ptr + com_begin, ' ', com_end + 3);
	}
}

void	*mlx_xpm_file_to_image(t_xvar *xvar, char *file, int *width, int *height)
{
	int		fd;
	int		size;
	char	*ptr;
	t_img	*img;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return ((void *)0);
	size = lseek(fd, 0, SEEK_END);
	if (size == -1)
		return (close(fd), (void *)0);
	ptr = mmap(0, size, PROT_WRITE | PROT_READ, MAP_PRIVATE, fd, 0);
	if (ptr == (void *)MAP_FAILED)
		return (close(fd), (void *)0);
	mlx_int_file_get_rid_comment(ptr, size);
	img = mlx_int_parse_xpm(xvar, ptr, size, mlx_int_get_line)
	if (img)
	{
		*width = img->width;
		*height = img->height;
	}
	munmap(ptr,size);
	close(fd);
	return (img);
}

void	*mlx_xpm_to_image(t_xvar *xvar, char **xpm_data, int *width, int *height)
{
	t_img	*img;

	img = mlx_int_parse_xpm(xvar, xpm_data, 0, mlx_int_static_line);
	if (img)
	{
		*width = img->width;
		*height = img->height;
	}
	return (img);
}
