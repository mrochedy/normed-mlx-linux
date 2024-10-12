/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:09:01 by mrochedy          #+#    #+#             */
/*   Updated: 2024/10/12 18:09:53 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 ** mlx_pixel_put.c for MiniLibX in
 **
 ** Made by Charlie Root
 ** Login   <ol@epitech.net>
 **
 ** Started on  Mon Jul 31 19:01:33 2000 Charlie Root
** Last update Tue Sep 25 17:09:49 2001 Charlie Root
 */

#include "mlx_int.h"

int	mlx_pixel_put(t_xvar *xvar, t_win_list *win, int x, int y, int color)
{
	XGCValues	xgcv;

	xgcv.foreground = mlx_int_get_good_color(xvar, color);
	XChangeGC(xvar->display, win->gc, GCForeground, &xgcv);
	XDrawPoint(xvar->display, win->window, win->gc, x, y);
	if (xvar->do_flush)
		XFlush(xvar->display);
}
