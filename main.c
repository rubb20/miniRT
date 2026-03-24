/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:20:03 by isastre-          #+#    #+#             */
/*   Updated: 2026/03/24 20:49:56 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	file_has_rt_extension(char *filename);

int main(int argc, char *argv[])
{
	t_miniRT	rt;
	t_sphere	*sphere;

	if (argc != 2 || !file_has_rt_extension(argv[1]))
		error_exit(NULL, WRONG_NUMBER_ARGS);

	rt.camera.pos = (t_3dvector){0.0f, 0.0f, 0.0f};
	rt.camera.dir = (t_3dvector){0.0f, 0.0f, -1.0f};
	rt.camera.fov = 60;

	rt.ambient_light.ratio = 0.5f;
	rt.ambient_light.rgb = (t_color){128,128,128};

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		error_exit(NULL, "Failed to allocate sphere");
sphere->pos = (t_3dvector){0.0f, 0.0f, -1.5f};
sphere->diameter = 1.0f;
	sphere->rgb = (t_color){0, 255, 0};

	rt.light.pos = (t_3dvector){0.0f, 5.0f, -1.0f};
	rt.light.ratio = 1.0f;
	rt.light.rgb = (t_color){0, 0,255};

	rt.scene = malloc(sizeof(t_list));
	if (!rt.scene)
		error_exit(NULL, "Failed to allocate scene node");
	rt.scene->id = SPHERE;
	rt.scene->obj = sphere;
	rt.scene->next = NULL;

t_sphere *sphere2;
t_list   *node2;

/* Allocate second sphere */
sphere2 = malloc(sizeof(t_sphere));
if (!sphere2)
	error_exit(NULL, "Failed to allocate sphere2");

sphere2->pos = (t_3dvector){2.5f, 0.0f, -5.0f};  // Right side
sphere2->diameter = 2.0f;
sphere2->rgb = (t_color){0, 0, 255};             // Blue

/* Allocate new list node */
node2 = malloc(sizeof(t_list));
if (!node2)
	error_exit(NULL, "Failed to allocate scene node");

node2->id = SPHERE;
node2->obj = sphere2;
node2->next = NULL;

/* Link it */
rt.scene->next = node2;

t_plane *plane;
t_list   *plane_node;
/* Allocate plane */
plane = malloc(sizeof(t_plane));
if (!plane)
	error_exit(NULL, "Failed to allocate plane");

/* Floor position (slightly below camera) */
plane->pos = (t_3dvector){0.0f, -1.0f, 0.0f};

/* Normal pointing UP */
plane->dir = vector_normalize((t_3dvector){0.0f, 1.0f, 0.0f});

/* Light gray floor color */
plane->rgb = (t_color){200, 200, 200};

/* Allocate list node */
plane_node = malloc(sizeof(t_list));
if (!plane_node)
	error_exit(NULL, "Failed to allocate plane node");

plane_node->id = PLANE;
plane_node->obj = plane;
plane_node->next = NULL;

/* Link after second sphere */
node2->next = plane_node;

t_cylinder *cyl;
t_list     *cyl_node;

/* Allocate cylinder */
cyl = malloc(sizeof(t_cylinder));
if (!cyl)
	error_exit(NULL, "Failed to allocate cylinder");

/* Cylinder base position */
cyl->pos = (t_3dvector){-2.0f, -2.0f, -5.0f};  // Left side
cyl->dir = vector_normalize((t_3dvector){0.0f, 1.0f, 0.0f}); // Pointing up
cyl->diameter = 1.0f;
cyl->height = 1.5f;
cyl->rgb = (t_color){255, 255, 0}; // Yellow

/* Allocate list node */
cyl_node = malloc(sizeof(t_list));
if (!cyl_node)
	error_exit(NULL, "Failed to allocate cylinder node");

cyl_node->id = CYLINDER;
cyl_node->obj = cyl;
cyl_node->next = NULL;

/* Link after second sphere */
node2->next = cyl_node;

/* Then link plane after cylinder */
cyl_node->next = plane_node;

	create_window(&rt);
	return (EXIT_SUCCESS);
}

/**
 * @brief checks if a filename is .rt
 */
static bool	file_has_rt_extension(char *filename)
{
	int	len;
	int	dot_position;

	len = ft_strlen(filename);
	if (len < RTFILE_EXT_LEN)
		return (false);
	dot_position = len - RTFILE_EXT_LEN;
	return (ft_equals(filename + dot_position, RTFILE_EXT));
}

/**
 * @brief frees miniRT struct and prints error msg
 */
void	error_exit(t_miniRT *rt, char *msg)
{
	printf("Error\n%s\n", msg);
	// free miniRT
	(void) rt;
	exit(EXIT_FAILURE);
}
