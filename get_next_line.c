/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:23:29 by tarini            #+#    #+#             */
/*   Updated: 2025/01/06 13:41:09 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_and_store(t_list **container, int fd)
{
	char		*buffer;
	int			reading;
	t_list		*new_node;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	while (1)
	{
		reading = read(fd, buffer, BUFFER_SIZE);
		if (reading <= 0)
			break ;
		buffer[reading] = '\0';
		new_node = ft_lstnew(ft_strdup(buffer));
		if (!new_node)
		{
			free(buffer);
			return (-1);
		}
		ft_lstadd_back(container, new_node);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (reading);
}

static size_t	compute_line_length(t_list *container)
{
	size_t	length;
	char	*content;

	length = 0;
	while (container)
	{
		content = container->content;
		while (*content && *content != '\n')
		{
			length++;
			content++;
		}
		if (*content == '\n')
		{
			length++;
			break ;
		}
		container = container->next;
	}
	return (length);
}

static void	copy_to_line(t_list *container, char *line, size_t length)
{
	size_t	i;
	char	*content;

	i = 0;
	while (container && i < length)
	{
		content = container->content;
		while (*content && *content != '\n' && i < length)
			line[i++] = *content++;
		if (*content == '\n' && i < length)
		{
			line[i++] = *content;
			break ;
		}
		container = container->next;
	}
}

static char	*extract_line(t_list **container)
{
	size_t	line_len;
	char	*line;

	if (!*container)
		return (NULL);
	line_len = compute_line_length(*container);
	line = malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	copy_to_line(*container, line, line_len);
	line[line_len] = '\0';
	update_and_clean_content(container);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*container;
	char			*line;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	if (read_and_store(&container, fd) < 0)
		return (NULL);
	line = extract_line(&container);
	return (line);
}
