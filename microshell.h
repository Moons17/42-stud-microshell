/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:29:28 by jveuille          #+#    #+#             */
/*   Updated: 2024/08/27 09:27:18 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

# define  ERR -1
# define ERR_SYS "error: fatal"
# define  ERR_CD_01 "error: cd: bad arguments"
# define  ERR_CD_02 "error: cd: cannot change directory "
# define  ERR_EXEC "error: cannot execute "

#endif