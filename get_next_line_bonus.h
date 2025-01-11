/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:09:15 by tarini            #+#    #+#             */
/*   Updated: 2025/01/11 14:57:36 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef OPEN_MAX
#  define OPEN_MAX 65534
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
char	*ft_strdup_or_strchr(const char *s, int c, int flag);
void	update_and_clean_content(t_list **container);
void	ft_lstclear_all(t_list **list);

#endif