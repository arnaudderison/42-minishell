


// Parsed command representation
#define EXEC  1
#define REDIR 2
#define PIPE  3
#define LIST  4
#define BACK  5

#define MAXARGS 10

///////////////// STRUCTURES /////////////////
typedef struct s_cmd
{
    int type;
    
}   t_cmd;

typedef struct s_execcmd
{
    int type;
    char    *argv[MAXARGS];
    char    *eargv[MAXARGS];
}   t_execcmd;

typedef struct s_pipecmd
{
    int type;
    t_cmd   *left;
    t_cmd   *right;
}   t_pipecmd;

typedef struct s_redircmd
{
    int     type;
    t_cmd   *cmd;
    char    *file;
    char    *efile;
    int     mode;
    int     fd;
}   t_redircmd;
