/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_modes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaimou <ishaimou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:36:48 by ishaimou          #+#    #+#             */
/*   Updated: 2019/04/29 11:22:55 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_type(t_file *file)
{
	if (S_ISBLK(file->stats->st_mode))
		ft_putchar('b');
	else if (S_ISCHR(file->stats->st_mode))
		ft_putchar('c');
	else if (S_ISDIR(file->stats->st_mode))
		ft_putchar('d');
	else if (S_ISFIFO(file->stats->st_mode))
		ft_putchar('p');
	else if (S_ISLNK(file->stats->st_mode))
		ft_putchar('l');
	else if (S_ISSOCK(file->stats->st_mode))
		ft_putchar('s');
	else
		ft_putchar('-');
}

static void		print_aclxattr(t_file *file)
{
	acl_t		acl;

	acl = acl_get_link_np(file->path, ACL_TYPE_EXTENDED);
	if (listxattr(file->path, NULL, 0, XATTR_NOFOLLOW))
		ft_putchar('@');
	else if (acl)
		ft_putchar('+');
	else
		ft_putchar(' ');
	if (acl)
		acl_free(acl);
}

static void		print_perm(t_file *file)
{
	(file->stats->st_mode & S_IRUSR) ? ft_putchar('r') : ft_putchar('-');
	(file->stats->st_mode & S_IWUSR) ? ft_putchar('w') : ft_putchar('-');
	if ((file->stats->st_mode & S_ISUID) && (S_IXUSR & file->stats->st_mode))
		ft_putchar('s');
	else if (file->stats->st_mode & S_ISUID)
		ft_putchar('S');
	else
		(file->stats->st_mode & S_IXUSR) ? ft_putchar('x') : ft_putchar('-');
	(file->stats->st_mode & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
	(file->stats->st_mode & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
	if ((file->stats->st_mode & S_ISGID) && (S_IXGRP & file->stats->st_mode))
		ft_putchar('s');
	else if (file->stats->st_mode & S_ISGID)
		ft_putchar('S');
	else
		(file->stats->st_mode & S_IXGRP) ? ft_putchar('x') : ft_putchar('-');
	(file->stats->st_mode & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
	(file->stats->st_mode & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
	if (file->stats->st_mode & S_ISVTX && (S_IXOTH & file->stats->st_mode))
		ft_putchar('t');
	else if (file->stats->st_mode & S_ISVTX)
		ft_putchar('T');
	else
		(file->stats->st_mode & S_IXOTH) ? ft_putchar('x') : ft_putchar('-');
}

void			print_modes(t_file *file)
{
	print_type(file);
	print_perm(file);
	print_aclxattr(file);
}
