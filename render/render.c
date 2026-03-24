/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 21:22:25 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/03/24 21:21:43 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	put_pixel(t_img *img, int x, int y, int color);
static int	render_pixel(t_ray ray, t_miniRT *scene);

void	render(t_miniRT *scene)
{
	int		y;
	int		x;
	t_ray	ray;

	y = 0;
	scene->frame = mlx_new_image(scene->mlxinfo.mlx, scene->mlxinfo.width,
			scene->mlxinfo.height);
	while (y < scene->mlxinfo.height)
	{
		x = 0;
		while (x < scene->mlxinfo.width)
		{
			ray = create_ray(x, y, scene);
			put_pixel(scene->frame, x, y, render_pixel(ray, scene));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlxinfo.mlx,
		scene->mlxinfo.win, scene->frame, 0, 0);
}

static t_color	ambient_color(t_miniRT *scene, t_color obj)
{
	t_color	a;

	a.r = obj.r * scene->ambient_light.ratio
		* (scene->ambient_light.rgb.r / 255.0f);
	a.g = obj.g * scene->ambient_light.ratio
		* (scene->ambient_light.rgb.g / 255.0f);
	a.b = obj.b * scene->ambient_light.ratio
		* (scene->ambient_light.rgb.b / 255.0f);
	return (a);
}

/**
 * 
 * Formula de Phong para el calculo de iluminacion en un punto:
 * luz difusa + luz ambiental.
 * luz difusa: kd * lightColor * max(0,N*L) siendo N la normal y L el vector desde el punto a la luz.
 * luz ambiental: ka * ambientColor.
 * kd y ka son factores de luz del objeto (el color del objeto).
 */
static int	render_pixel(t_ray ray, t_miniRT *scene)
{
	t_list		*hit;
	float		t;
	t_color		obj;
	t_color		diff;
	t_3dvector	hit_point;
	t_3dvector	L;
	t_3dvector	normalL;
	float		diffuse;

	t = intersect(ray, scene->scene, &hit);
	if (t < 0.0f)
		return (0);
	hit_point = vector_sum(ray.origin, vector_scale(ray.dir, t));
	L = vector_sub(scene->light.pos, hit_point);
	normalL = vector_normalize(L);
	obj = get_color(*hit);
	t = intersect((t_ray){vector_sum(hit_point, vector_scale(get_normal(hit, hit_point),1e-4f)), normalL}, scene->scene, NULL);
	diff = ambient_color(scene, obj);
	if (!(t > 0.0f && t < vector_length(L)))
	{
		diffuse = fmaxf(vec_dot(get_normal(hit, hit_point), normalL), 0.0f) * scene->light.ratio;
        diff = fminf_color(apply_light(obj, diffuse, scene->light.rgb), diff, 255);
	}
	return (color_to_int(diff));
}

static void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->data
		+ (y * img->size_line)
		+ (x * (img->bpp / 8));

	*(unsigned int *)dst = color;
}
