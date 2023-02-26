/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarival <ymarival@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:38:35 by ymarival          #+#    #+#             */
/*   Updated: 2023/02/12 20:37:46 by ymarival         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// compte la longueur de la chaine jusqu'a c
int	len_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

int	ft_strncmp( char *str1, char *str2, size_t n)
{
	while (*str1 && *str2 && *str1 == *str2 && --n > 0)
	{
		str1++;
		str2++;
	}
	return (*str2 - *str1);
}

char	*make_command(char *path, char *bin)
{
	int			i;
	int			j;
	char		*buff;

	buff = malloc(len_c(path, 0) + len_c(bin, 0) + 2);
	i = 0;
	j = 0;
	while (path[j])
		buff[i++] = path[j++];
	buff[i++] = '/';
	j = 0;
	while (bin[j])
		buff[i++] = bin[j++];
	buff[i] = 0;
	return (buff);
}

char	*str_ndup(char *str, unsigned int n)
{
	unsigned int	i;	
	char			*buff;

	i = 0;
	buff = malloc(sizeof(char) * (n + 1));
	while (i < n)
		buff[i++] = *str++;
	buff[n] = 0;
	return (buff);
}

char	**str_split(char *str, char sep)
{
	char	**tab;
	int		count;
	int		i;
	int		j;

	count = 0;
	j = 0;
	while (str[j])
	{
		if (str[j++] == sep)
			count++;
	}
	tab = malloc(sizeof(char *) * (count + 2));
	tab[count + 1] = NULL;
	i = 0;
	while (i < count + 1)
	{
		j = 0;
		while (str[j] && str[j] != sep)
			j++;
		tab[i++] = str_ndup(str, j);
		str = str + j + 1;
	}
	return (tab);
}
