/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:23:29 by tarini            #+#    #+#             */
/*   Updated: 2025/01/07 17:38:00 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include <stdlib.h>

// static void print_lst(t_list *lst)
// {
// 	printf("==========\n");
// 	if (lst == NULL)
// 		printf("ur fucked up\n");
// 	while (lst != NULL)
// 	{
// 		printf("%s\n",(char *)lst->content);
// 		lst = lst->next;
// 	}
// 	printf("==========\n");
// }

static int	read_and_store(t_list **container, int fd)
/* reads file and stores data in linked list */
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
			update_and_clean_content(container);
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
/* calculates length of the next line */
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
/* copy to line XD */
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
			break ;
		}
		container = container->next;
	}
}

static char	*extract_line(t_list **container)
/* extracts the line from the list */
{
	size_t	line_len;
	char	*line;

	if (!*container)
		return (NULL);
	line_len = compute_line_length(*container);
	line = malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	copy_to_line(*container, line);
	line[line_len] = '\0';
	update_and_clean_content(container);
	return (line);
}

char	*get_next_line(int fd)
/* returns extracted line */
{
	static t_list	*container;
	char			*line;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	if (read_and_store(&container, fd) < 0)
		return (NULL);
	line = extract_line(&container);
	if (!line)
		update_and_clean_content(&container);
	return (line);
}