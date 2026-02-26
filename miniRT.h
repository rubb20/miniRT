/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:33:54 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/02/26 17:38:33 by isastre-         ###   ########.fr       */
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
// limits
# include <limits.h>
# include <float.h>
// libft
# include "libft/libft.h"

// ### DEFINES ###
//     ELEMENT TYPES
# define ID_AMBIENT_LIGHT "A"
# define ID_CAMERA "C"
# define ID_LIGHT "L"
# define ID_SPHERE "sp"
# define ID_PLANE "pl"
# define ID_CYLINDER "cy"
// 	   MSG ERRORS
# define WRONG_NUMBER_ARGS "miniRT only accepts a .rt scene as input"
# define FAIL_MLX_INIT "minilibx failed on init"
# define FAIL_WINDOW_CREATE "minilibx failed to create a window"
# define OPEN_ERROR "Error while opening the file"
//     CONSTANTS
# define RTFILE_EXT ".rt"
# define RTFILE_EXT_LEN 3
# define WINDOW_TITLE "miniRT"
# define CLOSE_WINDOW 17
# define INT_MAX_LEN 10 // 2147483647
# define INT_MIN_ACCEPTED INT_MIN
# define INT_MAX_ACCEPTED INT_MAX
# define DECIMAL_MIN_ACCEPTED -DBL_MAX
# define DECIMAL_MAX_ACCEPTED DBL_MAX
# define DECIMAL_MAX_LEN 2
# define EPSILON 1e-6

// ### STRUCTS ###
/**
 * pos is used to represent the coordinates x, y, z of an element.
 * dir is used to represent the orientation vector or normal vector of an object.
 */
typedef struct s_color
{
	int	r; // [0,255]
	int	g; // [0,255]
	int	b; // [0,255]
}	t_color;

typedef struct s_3dvector
{
	double	x;
	double	y;
	double	z;
}	t_3dvector;

typedef struct s_ambient_light
{
	double	ratio; // [0,1]
	t_color	rgb;
}	t_ambient_light;

typedef struct s_camera
{
	t_3dvector	pos; // [N]
	t_3dvector	dir; // [-1,1]
	int			fov; // [0,180]
}	t_camera;

typedef struct s_light
{
	t_3dvector	pos; // [N]
	double		ratio; // [0,1]
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
	t_3dvector	pos; // [N]
	double		diameter; // [N]
	t_color		rgb;
}	t_sphere;

typedef struct s_plane
{
	t_3dvector	pos; // [N]
	t_3dvector	dir; // [-1,1]
	t_color		rgb;
}	t_plane;

typedef struct s_cylinder
{
	t_3dvector	pos; // [N]
	t_3dvector	dir; // [-1,1]
	double		diameter; // [N]
	double		height; // [N]
	t_color		rgb;
}	t_cylinder;

typedef struct s_mlxinfo
{
	void	*mlx;
	void	*win;
	int		height;
	int		width;
}	t_mlxinfo;

typedef struct s_miniRT
{
	t_ambient_light	ambient_light;
	t_camera		camera;
	t_light			light;
	t_mlxinfo		mlxinfo;
	t_list			*scene;
}	t_miniRT;

// ### OPERATIONS ###
t_3dvector	vector_sum(t_3dvector a, t_3dvector b);
t_3dvector	vector_sub(t_3dvector a, t_3dvector b);
t_3dvector	vector_scale(t_3dvector a, double k);
double		vector_length(t_3dvector a);
t_3dvector	vector_normalize(t_3dvector a);
double		vec_dot(t_3dvector a, t_3dvector b);
t_3dvector	vec_cross(t_3dvector a, t_3dvector b);
double		vec_distance(t_3dvector a, t_3dvector b);
bool		is_unit_vector(t_3dvector a);

// ### FUNCTIONS ###
void		error_exit(t_miniRT *rt, char *msg);

//     structs
t_color		*create_color(char *input);
t_3dvector	*create_3dvector(char *input);

//     parse
void		parse(t_miniRT *rt, char *filename);
int			atoi_err(char *str, bool *err, int min, int max);
double		atod_err(char *str, bool *err, double min, double max);

//     lists utils
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(t_id id, void *obj);

//     window management
void		create_window(t_miniRT scene);
void		manage_hooks(t_mlxinfo *window);

#endif
