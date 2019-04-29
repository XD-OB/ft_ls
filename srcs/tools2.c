/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaimou <ishaimou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:20:33 by ishaimou          #+#    #+#             */
/*   Updated: 2019/04/29 11:19:46 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_dot(char *name)
{
	if (!ft_strcmp(name, ".") || !ft_strcmp(name, ".."))
		return (1);
	return (0);
}

int		is_exec(t_file *file)
{
	if (S_ISREG(file->stats->st_mode) &&
		((S_IXUSR & file->stats->st_mode) ||
		(S_IXGRP & file->stats->st_mode) ||
		(S_IXOTH & file->stats->st_mode)))
		return (1);
	return (0);
}

int		is_large(t_opt *opts)
{
	if (opts->l || opts->n ||
			opts->o || opts->g)
		return (1);
	return (0);
}

int		is_special(mode_t mode)
{
	if (S_ISCHR(mode) ||
		S_ISBLK(mode) ||
		S_ISFIFO(mode) ||
		S_ISSOCK(mode))
		return (1);
	return (0);
}
