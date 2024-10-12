/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:37:36 by mrochedy          #+#    #+#             */
/*   Updated: 2024/10/12 17:37:39 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** mlx_key_hook.c for MiniLibX in
**
** Made by Charlie Root
** Login   <ol@epitech.net>
**
** Started on  Thu Aug  3 11:49:06 2000 Charlie Root
** Last update Fri Feb 23 17:10:09 2001 Charlie Root
*/

#include "mlx_int.h"

int	mlx_key_hook(t_win_list *win, int (*funct)(), void *param)
{
	win->hooks[KeyRelease].hook = funct;
	win->hooks[KeyRelease].param = param;
	win->hooks[KeyRelease].mask = KeyReleaseMask;
}
