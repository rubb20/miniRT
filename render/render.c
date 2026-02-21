/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 21:22:25 by ralba-ji          #+#    #+#             */
/*   Updated: 2026/02/21 21:13:31 by ralba-ji         ###   ########.fr       */
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

static int	render_pixel(t_ray ray, t_miniRT *scene)
{
	t_list		*hit;
	float		t;
	t_color		obj;
	t_color		amb;
	t_color		diff;
	t_color		final;
	t_3dvector	hit_point;
	t_3dvector	normal;
	t_3dvector	L;
	float		diffuse;

	t = intersect(ray, scene->scene, &hit);
	if (t < 0.0f)
		return (0);
	hit_point = vector_sum(ray.origin, vector_scale(ray.dir, t));
	normal = vector_normalize(
		vector_sub(hit_point, ((t_sphere *)hit->obj)->pos));
	L = vector_normalize(vector_sub(scene->light.pos, hit_point));
	diffuse = fmaxf(vec_dot(normal, L), 0.0f) * scene->light.ratio;
	obj = get_color(*hit);
	amb = ambient_color(scene, obj);

	diff.r = obj.r * diffuse * (scene->light.rgb.r / 255.0f);
	diff.g = obj.g * diffuse * (scene->light.rgb.g / 255.0f);
	diff.b = obj.b * diffuse * (scene->light.rgb.b / 255.0f);

	final.r = fminf(amb.r + diff.r, 255);
	final.g = fminf(amb.g + diff.g, 255);
	final.b = fminf(amb.b + diff.b, 255);

	return (color_to_int(final));
}


static void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->data
		+ (y * img->size_line)
		+ (x * (img->bpp / 8));

	*(unsigned int *)dst = color;
}
