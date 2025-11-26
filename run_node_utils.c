/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rufurush <rufurush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:43:04 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/11/25 19:03:16 by rufurush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rn_status_from_wait(int st)
{
	int	status;
	int	sig;

	status = 0;
	if (WIFEXITED(st))
		status = WEXITSTATUS(st);
	else if (WIFSIGNALED(st))
	{
		sig = WTERMSIG(st);
		status = 128 + sig;
		if (sig == SIGINT)
			write(2, "\n", 1);
		else if (sig == SIGQUIT)
			write(2, "Quit: 3\n", 8);
	}
	return (status);
}

pid_t	rn_fork_and_exec(t_pipex *ps, t_ast *node, char **envp)
{
	pid_t	pid;
	int		st;

	pid = fork();
	if (pid == 0)
	{
		set_signals_child();
		st = run_simple_in_this_process(ps, node, envp);
		_exit(st);
	}
	return (pid);
}

int	rn_wait_pid(pid_t pid)
{
	int	st;
	int	status;

	st = 0;
	status = 0;
	if (waitpid(pid, &st, 0) > 0)
		status = rn_status_from_wait(st);
	return (status);
}
