/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarival <ymarival@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:46:38 by ymarival          #+#    #+#             */
/*   Updated: 2023/02/12 04:06:01 by ymarival         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>

char	*make_command(char *path, char *bin);
int		ft_strncmp(char *str1, char *str2, size_t n);
int		len_c(char *str, char c);
int		openfile(char *file, int mode);
char	*full_command_path(char *cmd, char **env);
void	second_command_processing(char *command, char **env);
void	first_command_processing(char *command, char **env, int infile_fd);
int		main(int ac, char **av, char **env);
char	**str_split(char *str, char sep);
char	*str_ndup(char *str, unsigned int n);
int		dup2(int oldfd, int newfd);

#endif