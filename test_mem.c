
#include <stdio.h>
#include <sys/mman.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define NAME        "loop"
#define TOTAL_PROC  3

/*
typedef struct		s_status
{
	pid_t			pid;
	enum {
					stopped,
					running
	}				state;
	time_t			started_time;
	time_t			stopped_time;
}					t_status;*/

typedef struct		        s_status
{
    int             id_job;
	pid_t		    pid;
	enum {
                    stopped,
                    running
	}				state;
	time_t			started_time;
	time_t          stopped_time;
    struct s_status *next_same;
    struct s_status *next;
}                   t_status;

typedef struct		s_shared
{
//	t_status		status[500];
    t_status        status;
}					t_shared;
//------------------------------------------------------------------------------

void    *ft_shared_malloc(int size)
{
    void *ret;

    if (size > 0)
        ret = mmap(NULL, size, PROT_READ|PROT_WRITE, 
                    MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    else
        ret = NULL;
    return (ret);
}

int    ft_free_shared(void *var, int size)
{
    if (var)
        munmap(var, size);
    else
        return (0);
    return (1);
}

void        ft_init_status(t_status *s)
{
    s->pid = 0;
    s->state = stopped;
    s->started_time = 0;
    s->stopped_time = 0;
    s->next_same = NULL;
    s->next = NULL;
}

void        ft_fork_job(t_shared *shared)
{
    pid_t	father;
    t_status *tmp;

	father = fork();

    tmp = &shared->status;
    while (tmp->next_same)
        tmp = tmp->next_same;
    ft_init_status(tmp);
    tmp->pid = father;
    tmp->state = running;

	if (!father)
    {
        

        execl("/tmp/a.out", NULL);
        printf("%s", "Oh shit! an error occured :(\n");
        exit(0);
    }
	if (father > 0)
	{
        printf("starting %s (pid: %d)\n", NAME, father);
	}
}

void        ft_exec_jobs(t_shared *shared)
{
    int i;

    ft_init_status(&shared->status); // init first link


    // (foreach jobs)
    if (TOTAL_PROC > 0)
    {
        i = -1;
        while (++i < TOTAL_PROC)
        {
            if (i > 0)
            {
                t_status *tmp = &shared->status;
                while (tmp->next_same)
                    tmp = tmp->next_same;
                tmp->next_same = ft_shared_malloc(sizeof(t_shared));
            }
            printf("starting: [%s]\n", NAME);
            ft_fork_job(shared);
        }
    } 
}



int main(void)
{
    t_shared *shared;

//    shared = (t_shared*)mmap(NULL, sizeof(t_shared), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    shared = ft_shared_malloc(sizeof(t_shared));

    ft_exec_jobs(shared);
//    ft_do_stuff(shared);
    t_status *tmp = &shared->status;
    while (tmp)
    {
        printf("Pid: [%d]\n", tmp->pid);
        tmp = tmp->next_same;
    }

//    munmap(shared, sizeof(t_shared));
    ft_free_shared(shared, sizeof(shared));
    system("pkill a.out");
}
