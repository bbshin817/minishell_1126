/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rufurush <rufurush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 09:39:00 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/11/25 17:54:20 by rufurush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_erro(char *err, char *msg)
{
	ft_putstr_fd(err, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
}

int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (-1);
	return (S_ISDIR(st.st_mode));
}

int	execute_command(char *cmd_path, char **cmd_args, char **envp, t_pipex *ps)
{
	int	directory;
	int	ret;

	ret = validate_cmd_args(cmd_args, ps);
	if (ret != 0)
		return (ret);
	if (!cmd_path)
		return (handle_no_cmd_path(ps, cmd_args));
	directory = is_directory(cmd_path);
	ret = handle_directory_result(directory, cmd_args, ps);
	if (ret != 0)
		return (ret);
	ret = check_exec_permission(cmd_path, cmd_args, ps);
	if (ret != 0)
		return (ret);
	execve(cmd_path, cmd_args, envp);
	return (handle_exec_error(cmd_args, ps));
}
