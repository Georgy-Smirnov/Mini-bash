/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 19:53:25 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/09 15:05:09 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_for_reduce(char *tmp, char *buf)
{
	free(tmp);
	free(buf);
	return (-1);
}

int	work_with_static(char **tmp, char **line, char *buf)
{
	if (charinstr('\n', *tmp) != -1)
	{
		*line = ft_substr(*tmp, 0, charinstr('\n', *tmp));
		if (*line == NULL)
			ft_for_reduce(*tmp, buf);
		*tmp = ft_delbeforechar('\n', *tmp);
		if (*tmp == NULL)
			ft_for_reduce(*tmp, buf);
		free(buf);
		return (1);
	}
	else
	{
		*line = *tmp;
		*tmp = NULL;
		free(buf);
		return (0);
	}
}

int	ft_read(int *rs, int fd, char **buf)
{
	*rs = read(fd, *buf, BUFFER_SIZE);
	return (*rs);
}

int	allocate_for_tmp_buf(char **tmp, char **buf)
{
	if (*tmp == NULL)
	{
		*tmp = (char *)malloc(sizeof(char));
		if (*tmp == NULL)
			return (-1);
		**tmp = 0;
	}
	*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (*buf == NULL)
	{
		free(*tmp);
		return (-1);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*tmp;
	int			rs;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (allocate_for_tmp_buf(&tmp, &buf) == -1)
		return (-1);
	while (((charinstr('\n', tmp) == -1)) && (ft_read(&rs, fd, &buf)))
	{
		if (rs == -1)
			return (ft_for_reduce(tmp, buf));
		buf[rs] = 0;
		tmp = ft_strjoin_with_frees1(tmp, buf);
	}
	return (work_with_static(&tmp, line, buf));
}
