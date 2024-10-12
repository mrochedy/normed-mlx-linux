/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_wait_first_expose.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:36:28 by mrochedy          #+#    #+#             */
/*   Updated: 2024/10/12 17:36:48 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** mlx_int_wait_first_expose.c for minilibx in
**
** Made by olivier crouzet
** Login   <ol@epita.fr>
**
** Started on  Tue Oct 17 09:26:45 2000 olivier crouzet
** Last update Fri Feb 23 17:27:10 2001 Charlie Root
*/

#include "mlx_int.h"

int	mlx_int_wait_first_expose(t_xvar *xvar, Window win)
{
	XEvent	ev;

	XWindowEvent(xvar->display, win, ExposureMask, &ev);
	XPutBackEvent(xvar->display, &ev);
}
