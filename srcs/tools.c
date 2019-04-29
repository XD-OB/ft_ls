/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaimou <ishaimou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:19:27 by ishaimou          #+#    #+#             */
/*   Updated: 2019/04/29 12:24:58 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		permis_error(char *name, int error)
{
	if (error)
	{
		write(2, "ft_ls: ", 7);
		ft_putstr_fd(name, 2);
		write(2, ": ", 2);
		ft_putstr_fd(strerror(error), 2);
		write(2, "\n", 1);
		errno = 0;
		return (1);
	}
	return (0);
}

int		pure_dir(t_file *file)
{
	if (!is_dot(file->name) &&
			S_ISDIR(file->stats->st_mode))
		return (1);
	return (0);
}

void	print_enoent(void *item)
{
	t_file	*file;

	file = (t_file*)item;
	write(2, "ft_ls: ", 7);
	ft_putstr_fd(file->name, 2);
	write(2, ": ", 2);
	ft_putstr_fd(strerror(file->error), 2);
	write(2, "\n", 1);
}
