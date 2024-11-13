
#include "../minishell.h"


t_cmd *pipecmd(t_cmd *left, t_cmd *right)
{
    t_pipecmd *cmd;

    cmd = malloc(sizeof(*cmd));
    ft_memset(cmd, 0, sizeof(*cmd));
    cmd->type = PIPE;
    cmd->left = left;
    cmd->right = right;
    return (t_cmd*)cmd;
}

t_cmd *execcmd(void)
{
    t_execcmd   *cmd;
    cmd = malloc(sizeof(*cmd));
    ft_memset(cmd, 0, sizeof(*cmd));
    cmd->type = EXEC;
    return (t_cmd*)cmd;
}

t_cmd *redircmd(t_cmd *left, t_cmd *right)
{
    t_redircmd *cmd;

    cmd = malloc(sizeof(*cmd));
    ft_memset(cmd, 0, sizeof(*cmd));
    cmd->type = REDIR;
    cmd->left = left;
    cmd->right = right;
    return (t_cmd*)cmd;
}