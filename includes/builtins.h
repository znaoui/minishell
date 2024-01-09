/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:15:03 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/17 14:45:53 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	handle_builtin(t_cmd *cmd);
int	is_builtin(t_cmd *cmd);
int	main_cd(int argc, char **argv);
int	main_env(int argc, char **argv);
int	main_pwd(int argc, char **argv);
int	main_exit(int argc, char **argv);
int	main_export(int argc, char **argv);
int	main_unset(int argc, char **argv);
int	main_echo(int argc, char **argv);

#endif
