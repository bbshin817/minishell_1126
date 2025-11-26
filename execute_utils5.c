/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:01:28 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/11/25 16:19:58 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_pipe_node(t_pipex *ps, t_ast *left, t_ast *right, char **envp)
{
	int		fds[2];
	pid_t	lp;
	pid_t	rp;
	int		last;

	if (pipe(fds) < 0)
		return (1);
	set_signals_parent_wait();
	lp = fork();
	if (lp == 0)
		ms_run_left_child(ps, left, envp, fds);
	rp = fork();
	if (rp == 0)
		ms_run_right_child(ps, right, envp, fds);
	close(fds[0]);
	close(fds[1]);
	last = ms_wait_pipe_children(lp, rp);
	set_signals_prompt();
	return (last);
}
