/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:33:54 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/01/17 21:15:08 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// ### LIBS ###

//open.
# include <fcntl.h>
//close, read, write.
# include <unistd.h>
//printf, perror.
# include <stdio.h>
//malloc, free, exit.
# include <stdlib.h>
//strerror.
# include <string.h>
//math functions.
# include <math.h>
//getttimeofday.
# include <sys/time.h>
//minilibX.
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <X11/Xlib.h>
// booleans
# include <stdbool.h>
// libft
# include "libft/libft.h"

// ### DEFINES ###
// 	   MSG ERRORS
# define WRONG_NUMBER_ARGS "miniRT only accepts a .rt scene as input"
# define FAIL_MLX_INIT "minilibx failed on init"
# define FAIL_WINDOW_CREATE "minilibx failed to create a window"
//     CONSTANTS
# define RTFILE_EXT ".rt"
# define RTFILE_EXT_LEN 3
# define WINDOW_TITLE "miniRT"
# define CLOSE_WINDOW 17

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
	t_id			id;
	void			*obj;
	struct s_list	*next;
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
	t_mlxinfo		mlxinfo;
	t_list			*scene;
}	t_miniRT;

typedef struct s_mlxinfo
{
	void	*mlx;
	void	*win;
	int		height;
	int		width;
}	t_mlxinfo;

// ### OPERATIONS ###
t_3dvector	vector_sum(t_3dvector a, t_3dvector b);
t_3dvector	vector_sub(t_3dvector a, t_3dvector b);
t_3dvector	vector_scale(t_3dvector a, float k);
float		vector_length(t_3dvector a);
t_3dvector	vector_normalize(t_3dvector a);
float		vec_dot(t_3dvector a, t_3dvector b);
t_3dvector	vec_cross(t_3dvector a, t_3dvector b);
float		vec_distance(t_3dvector a, t_3dvector b);

// ### FUNCTIONS ###
void		error_exit(t_miniRT *rt, char *msg);

//     lists utils
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(t_id id, void *obj);

//     window management
void	create_window(t_miniRT scene);
void	manage_hooks(t_mlxinfo *window);

#endif