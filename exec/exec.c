/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plachard <plachard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 21:09:39 by plachard          #+#    #+#             */
/*   Updated: 2024/11/10 03:05:30 by plachard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

///////////////// FUNCTIONS /////////////////
///////// HELPERS ///////// 
void panic(char *s)
{
    fprintf(2, "%s\n", s);
    exit(1);
}

int fork1(void)
{
    int pid;
    pid = fork();
    if (pid == -1)
        panic("fork");
    return(pid);
}
///////// EXEC ///////// 

void    pipeline(int *p, int fd_child)
{
        close(fd_child);
        dup(p[fd_child]);
        close(p[0]);
        close(p[1]);
}

void runcmd(t_cmd *cmd)
{

    int         p[2];
    t_execcmd   *ecmd;
    t_pipecmd   *pcmd;
    t_redircmd  *rcmd;

    if (!cmd)
        exit(1);
    if (cmd->type == EXEC)
    {
        ecmd = (t_execcmd*)cmd;
        if (ecmd->argv[0] == 0)
            exit(1);
        exec(ecmd->argv[0], ecmd->argv);
        fprintf(2, "exec %s failed\n", ecmd->argv[0]);
    }
    if (cmd->type == REDIR)
    {
        rcmd = (t_redircmd*)cmd;
        close(rcmd->fd);
        if (open(rcmd->file, rcmd->mode) < 0)
        {
            fprintf(2, "open %s failed\n", rcmd->file);
            exit(1);
        }
        runcmd(rcmd->cmd);
    }
    if (cmd->type == PIPE)
    {
        pcmd = (t_pipecmd*)cmd;
        if (pipe(p) < 0)
            panic("pipe");
        if (fork1() == 0)
        {            
            pipeline(p, 1);
            runcmd(pcmd->right);
        }
        if (fork1() == 0)
        {
            pipeline(p, 0);
            runcmd(pcmd->left);
        }
        close(p[0]);
        close(p[1]);
        wait(0);
        wait(0);
    }
    else
        panic("runcmd");
    exit (0);       
}

int main(void)
{
    static char buf[100];
    int fd;

    // ensure 3 fd open
    while ((fd = open("console", O_RDWR)) >= 0)
    {
        if (fd >= 3)
        {
            close(fd);
            break;
        }
    }
    //read and run cmd
    while (getcmd(buf, sizeof(buf)) >= 0)
    {
        // CHECK CD BEFORE EXECUTE CMD
        // if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ')
        // {
        //     buf[strlen(buf)-1] = 0;
        //     if (chdir(buf+3) < 0)
        //         fprintf("cannot cd %s\n", buf+3);
        //     continue;
        // }
        if (fork1() == 0)
            runcmd(parsecmd(buf));
        wait(0);
    }
    exit(0);
}