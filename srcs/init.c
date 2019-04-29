/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaimou <ishaimou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 14:47:51 by ishaimou          #+#    #+#             */
/*   Updated: 2019/04/29 11:18:04 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				init_opts(t_ls *ls)
{
	ls->nbr_dir = 0;
	ls->nbr_reg = 0;
	ls->opts.l = 0;
	ls->opts.a = 0;
	ls->opts.r = 0;
	ls->opts.t = 0;
	ls->opts.i = 0;
	ls->opts.o = 0;
	ls->opts.g = 0;
	ls->opts.m = 0;
	ls->opts.n = 0;
	ls->opts.p = 0;
	ls->opts.u = 0;
	ls->opts.cap_r = 0;
	ls->opts.cap_s = 0;
	ls->opts.cap_a = 0;
	ls->opts.cap_g = 0;
}

void				init_mw(t_max *mw)
{
	mw->total = 0;
	mw->count = 0;
	mw->major = 0;
	mw->minor = 0;
	mw->size = 1;
	mw->link = 1;
	mw->own = 0;
	mw->grp = 0;
	mw->nown = 0;
	mw->ngrp = 0;
}

void				fill_mw(t_max *p_mw, t_file *file)
{
	struct group	*grp;
	struct passwd	*own;

	file->c_mw = p_mw;
	p_mw->count++;
	p_mw->total += file->stats->st_blocks;
	if ((grp = getgrgid(file->stats->st_gid)))
		p_mw->grp = ft_max(p_mw->grp, ft_strlen(grp->gr_name));
	if ((own = getpwuid(file->stats->st_uid)))
		p_mw->own = ft_max(p_mw->own, ft_strlen(own->pw_name));
	p_mw->ngrp = ft_max(p_mw->ngrp, ft_intlen(file->stats->st_gid));
	p_mw->nown = ft_max(p_mw->nown, ft_intlen(file->stats->st_uid));
	p_mw->size = ft_max(p_mw->size, ft_intlen(file->stats->st_size));
	p_mw->link = ft_max(p_mw->link, ft_intlen(file->stats->st_nlink));
	p_mw->major = ft_max(p_mw->major, ft_intlen(major(file->stats->st_dev)));
	p_mw->minor = ft_max(p_mw->minor, ft_intlen(minor(file->stats->st_dev)));
}

char				*set_path(t_file *file, char *path)
{
	char			*full_path;
	int				path_len;
	int				name_len;
	int				buff_len;

	if (!*path)
		return (ft_strdup(file->name));
	name_len = ft_strlen(file->name);
	path_len = ft_strlen(path);
	buff_len = name_len + path_len + 2;
	full_path = ft_strnew(name_len + path_len + 1);
	full_path = ft_strcpy(full_path, path);
	if (path[path_len - 1] != '/')
		ft_strlcat(full_path, "/", buff_len);
	ft_strlcat(full_path, file->name, buff_len);
	return (full_path);
}

t_file				*init_file(char *name, char *path, t_opt *opts)
{
	t_file			*file;

	if (!(file = (t_file*)malloc(sizeof(t_file))))
		exit(-1);
	file->name = ft_strdup(name);
	file->path = set_path(file, path);
	file->opts = opts;
	file->node = NULL;
	file->p_mw = NULL;
	file->c_mw = NULL;
	file->rcs = 0;
	if (!(file->stats = (struct stat*)malloc(sizeof(struct stat))))
		exit(-1);
	lstat(file->path, file->stats);
	file->error = errno;
	errno = 0;
	return (file);
}
