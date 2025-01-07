/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:54:29 by stafpec           #+#    #+#             */
/*   Updated: 2025/01/07 14:54:41 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	update_and_clean_content(t_list **container)
/* clean list after the extract */
{
	t_list	*tmp;
	char	*newline;
	char	*new_content;

	while (*container)
	{
		newline = ft_strchr((*container)->content, '\n');
		if (newline)
		{
			new_content = ft_strdup(newline + 1);
			free((*container)->content);
			(*container)->content = new_content;
			return ;
		}
		tmp = *container;
		*container = (*container)->next;
		free(tmp->content);
		free(tmp);
	}
}

char	*ft_strdup(const char *s)
/* returns a pointer to a new string which is a duplicate of the string s */
{
	int		i;
	char	*dest;

	i = 0;
	while (s[i])
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i++])
		dest[i] = s[i];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *str, int c)
/* returns a pointer to the first occurrence of the character c 
	in the string s */
{
	unsigned int	i;

	i = 0;
	while (str[i++])
	{
		if (str[i] == (unsigned char)c)
			return ((char *)(&str[i]));
	}
	if (!(unsigned char)c)
		return ((char *)(&str[i]));
	return (NULL);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
/* allocates (with malloc(3)) and returns a new element */
{
	struct s_list	*current;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

t_list	*ft_lstnew(void *content)
/* add element ’new’ at the end of list */
{
	struct s_list	*my_new_list;

	my_new_list = malloc(sizeof(t_list));
	if (my_new_list == NULL)
		return (NULL);
	my_new_list->content = content;
	my_new_list->next = NULL;
	return (my_new_list);
}
