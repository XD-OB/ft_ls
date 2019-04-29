/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freef.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 14:58:10 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/29 11:20:03 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	freef(void **item)
{
	t_file	*file;

	file = (t_file*)*item;
	if (!file)
		return ;
	free(file->name);
	free(file->path);
	if (file->p_mw)
		free(file->p_mw);
	if (file->stats)
		free(file->stats);
	free(file);
	*item = NULL;
}
