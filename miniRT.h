/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:33:54 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/12/01 15:11:51 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// ### LIBS ###

//open.
# include "fcntl.h"
//close, read, write.
# include "unistd.h"
//printf, perror.
# include "stdio.h"
//malloc, free, exit.
# include "stdlib.h"
//strerror.
# include "string.h"
//math functions.
# include "math.h"
//getttimeofday.
# include <sys/time.h>
//minilibX.
# include "minilibx-linux/mlx.h"
# include <X11/Xlib.h>

// ### STRUCTS ###
/**
 * pos is used to represent the coordinates x, y, z of an element.
 * dir is used to represent the orientation vector or normal vector of an object.
 */
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_3dvector
{
	float	x;
	float	y;
	float	z;
}	t_3dvector;

typedef struct s_ambient_light
{
	float	ratio;
	t_color	rgb;
}	t_ambient_light;

typedef struct s_camera
{
	t_3dvector	pos;
	t_3dvector	dir;
	int			fov;
}	t_camera;

typedef struct s_light
{
	t_3dvector	pos;
	float		ratio;
	t_color		rgb;
}	t_light;

typedef enum e_id
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_id;

typedef struct s_list
{
	t_id	id;
	void	*obj;
	t_list	*next;
}	t_list;

typedef struct s_sphere
{
	t_3dvector	pos;
	float		diameter;
	t_color		rgb;
}	t_sphere;

typedef struct s_plane
{
	t_3dvector	pos;
	t_3dvector	dir;
	t_color		rgb;
}	t_plane;

typedef struct s_cylinder
{
	t_3dvector	pos;
	t_3dvector	dir;
	float		diameter;
	float		height;
	t_color		rgb;
}	t_cylinder;

typedef struct s_miniRT
{
	t_ambient_light	ambient_light;
	t_camera		camera;
	t_light			light;
	t_list			*scene;
}	t_miniRT;

#endif