/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:23:29 by tarini            #+#    #+#             */
/*   Updated: 2025/01/11 16:54:20 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	read_and_store(t_list **container, int fd)
{
	char		*buffer;
	int			reading;
	t_list		*new_node;
	char		*dup_content;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	while (1)
	{
		reading = read(fd, buffer, BUFFER_SIZE);
		if (reading <= 0)
			return (free(buffer), reading);
		buffer[reading] = '\0';
		dup_content = ft_strdup_or_strchr(buffer, 0, 1);
		if (!dup_content)
			return (ft_lstclear_all(container), free(buffer), -1);
		new_node = ft_lstnew(dup_content);
		if (!new_node)
			return (ft_lstclear_all(container), free(buffer), -1);
		ft_lstadd_back(container, new_node);
		if (ft_strdup_or_strchr(buffer, '\n', 0))
			break ;
	}
	return (free(buffer), reading);
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

static void	copy_to_line(t_list *container, char *line)
{
	size_t	i;
	char	*content;

	i = 0;
	while (container)
	{
		content = container->content;
		while (*content && *content != '\n')
			line[i++] = *content++;
		if (*content == '\n')
		{
			line[i++] = *content;
			return ;
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
	if (line_len == 0)
		return (NULL);
	line = malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (ft_lstclear_all(container), NULL);
	copy_to_line(*container, line);
	line[line_len] = '\0';
	update_and_clean_content(container);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*container[OPEN_MAX];
	char			*line;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	if (read_and_store(&container[fd], fd) < 0)
		return (ft_lstclear_all(&container[fd]), NULL);
	line = extract_line(&container[fd]);
	if (!line)
		return (update_and_clean_content(&container[fd]), NULL);
	return (line);
}
