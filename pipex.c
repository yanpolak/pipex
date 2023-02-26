/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarival <ymarival@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:29:22 by ymarival          #+#    #+#             */
/*   Updated: 2023/02/12 22:20:37 by ymarival         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//  Lire les fichiers d'entrée ou de sortie

int	openfile(char *file, int mode)
{
	int	fd;

	if (mode != 0 && mode != 1)
	{
		write(2, "Invalid mode argument\n", 22);
		return (-1);
	}
	if (mode == 0)
		fd = open(file, O_RDONLY);
	else
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "Error opening file\n", 19);
		return (-1);
	}
	if (mode == 0 && access(file, F_OK) == -1)
	{
		close(fd);
		write(2, "Error accessing file\n", 21);
		return (-1);
	}
	return (fd);
}

//  Trouve le chemin complet de la commande dans les variables d'environnement
//  Jusqu'à ce que nous trouvions le chemin souhaité dans env, itération
//  S'il n'y a pas de chemin, retourne la commande
//  Si le chemin est trouvé, récupérez le chemin complet avec la commande

char	*full_command_path(char *cmd, char **env)
{
	int		i;
	char	*path;
	char	*dir;
	char	*full;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && len_c(path, ':') > -1)
	{
		dir = str_ndup(path, len_c(path, ':'));
		full = make_command(dir, cmd);
		free(dir);
		if (access(full, F_OK) == 0)
			return (full);
		free(full);
		path += len_c(path, ':') + 1;
	}
	return (cmd);
}

//  Traite la seconde commande, 
//  Drapeaux séparés et recherche 

void	second_command_processing(char *command, char **env)
{
	char	**args;
	char	*path;

	args = str_split(command, ' ');
	if (len_c(args[0], '/') > -1)
		path = args[0];
	else
		path = full_command_path(args[0], env);
	execve(path, args, env);
	write(2, "Сommand not found\n", 19);
	exit(127);
}

//  Cloner le processus avec un fork et traiter la première commande:
void	first_command_processing(char *command, char **env, int infile_fd)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		if (infile_fd == 0)
			exit(1);
		else
			second_command_processing(command, env);
	}
}

//  1. Obtenir les descripteurs de fichiers d'entrée et de sortie 
//  2. dupliquez-les, en fermant à l'entrée et à la sortie 
//  3. cloner le processus et exécuter 1 commande 
//  4. exécutez la deuxième commande et réduisez le processus 

int	main(int ac, char **av, char **env)
{
	int	infile_fd;
	int	outfile_fd;

	if (ac == 5)
	{
		infile_fd = openfile(av[1], 0);
		outfile_fd = openfile(av[4], 1);
		dup2(infile_fd, 0);
		dup2(outfile_fd, 1);
		first_command_processing(av[2], env, infile_fd);
		second_command_processing(av[3], env);
	}
	else
		write(2, "Need 4 arguments\n", 18);
	return (1);
}
