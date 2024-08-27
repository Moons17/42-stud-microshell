/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:28:40 by jveuille          #+#    #+#             */
/*   Updated: 2024/08/27 14:52:41 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "microshell.h"

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0; 
	while (str[i])
		i++;
	return (i);
}

static void	ft_perr(char *str, char *arg)
{
	if (str)
	{
		write(STDERR_FILENO, str, ft_strlen(str));
		if (arg)
			write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, "\n", 1);
	}
	return ;
}

static void	ft_cd(char **arg, int	i)
{
	if (i != 2)
		ft_perr(ERR_CD_01, NULL);
	//	exit(EXIT_FAILURE); dont pass test12 of exam correction 
	else
	{
		if (chdir(arg[1]) == ERR)
		{
			ft_perr(ERR_CD_02, arg[1]);
			exit(EXIT_FAILURE);
		}
	}
	return ;
}

static void	ft_close(int fd)
{
	if (close(fd) == ERR)
	{
		ft_perr(ERR_SYS, NULL);
		exit (EXIT_FAILURE);
	}
	return ;
}

static int	ft_dup(int fd2)
{
	int fd1;

	fd1 = dup(fd2);
	if (fd1 == ERR)
	{
		ft_perr(ERR_SYS, NULL);
		exit (EXIT_FAILURE);
	}
	return (fd1);
}		

static void	ft_dup2(int fd1 , int fd2)
{
	if (dup2(fd1, fd2) == ERR)
	{
		ft_perr(ERR_SYS, NULL);
		exit (EXIT_FAILURE);
	}
	return ;
}

static pid_t	ft_fork()
{
	pid_t	cpid;

	cpid = fork();
	if (cpid == ERR)
	{
		ft_perr(ERR_SYS, NULL);
		exit (EXIT_FAILURE);
	}
	return (cpid);
}

static void	ft_execve(char **arg, int i, char **env, int fd_tmp)
{
	arg[i] = NULL;
	ft_dup2(fd_tmp, STDIN_FILENO);
	ft_close(fd_tmp);
	if (execve(arg[0], arg, env) == ERR)
	{
		ft_perr(ERR_EXEC, arg[0]);
		exit (EXIT_FAILURE);
	}
	return ;
}
int	main(int argc, char **argv, char **env)
{
	int		i;
	int		fd_tmp;
	int		fd[2];

	fd_tmp = ft_dup(STDIN_FILENO);
	if (argc < 2)
		return (EXIT_SUCCESS);
	i = 0;
	while (argv[i] && argv[i + 1])
	{
		argv = &argv[i + 1];
		i = 0 ;
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			i++;
		if (!*argv)
			break ;
		if (strcmp(argv[0], "cd") == 0)
			ft_cd(argv, i);
		else if (argv[i] && (i != 0) && strcmp(argv[i], "|") == 0)
		{
			if (pipe(fd) == ERR)
			{
				ft_perr(ERR_SYS, NULL);
				exit (EXIT_FAILURE);
			}
			if (ft_fork() == 0)
			{
				ft_dup2(fd[1], STDOUT_FILENO);
				ft_close(fd[0]);
				ft_close(fd[1]);
				ft_execve(argv, i, env, fd_tmp);
			}
			else
			{
				ft_close(fd[1]);
				ft_close(fd_tmp);
				fd_tmp = fd[0];
			}
		}
		else if ((i != 0) &&((argv[i] == NULL)|| (argv[i] && strcmp(argv[i], ";") == 0)))
		{
			if (ft_fork() == 0)
				ft_execve(argv, i, env, fd_tmp);
			else
			{
				ft_close(fd_tmp);
				while (waitpid(-1, NULL, WUNTRACED) != ERR)
					;
				fd_tmp = ft_dup(STDIN_FILENO);
			}
		}
	}
	ft_close(fd_tmp);
	return (EXIT_SUCCESS);
}
