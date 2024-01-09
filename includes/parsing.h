/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:17:43 by cdudzik           #+#    #+#             */
/*   Updated: 2022/11/04 01:24:16 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define HEREDOC_EOF_ERROR "-minishell: warning: here-document \
delimited by end-of-file\n"

# include "minishell.h"

char		*process_arg(char *arg, int heredoc);
void		dump_arr(char **arr);
char		*cmd_type_to_str(t_cmd_type type);
char		*remove_substr(char *str, int index, int len);
char		*replace_str(char *str, int index, int len, char *new);
void		dump_cmd(t_cmd *cmd);
void		free_cmd(t_cmd *t);
void		free_array(char **arr);
t_cmd		*null_and_free(t_cmd *cmd);
int			handle_redir(t_cmd *cmd, char **str, char **start);
int			char_bckw(char *str, char *start, char c);
t_cmd		*new_command(void);
char		**reallocate_and_push(char **arr, char *str, int size);
char		*redir_type_to_str(t_redir_type type);

#endif
