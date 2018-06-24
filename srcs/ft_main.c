/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_main.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/15 18:14:45 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/03/15 18:17:48 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "taskmaster.h"
#include <sys/mman.h>
#include <signal.h>
//#include <pthread.h>
//#include <sched.h>

typedef struct		s_keyval
{
	char			*key;
	char			*value;
	struct s_keyval	*next;
}					t_keyval;

typedef struct		s_job
{
	char			name[1000];
	char			cmd[1000];
	int				nb_procs;
	char			umask[5];
	char			working_dir[1000];
	int				autostart;
	int				autorestart;
	int				exit_codes[10];
	int				start_retries;
	int				start_time;
	int				stop_time;
	char			stop_signal[10];
	char			stdout[1000];
	char			stderr[1000];
	t_keyval		*env;
}					t_job;

typedef struct		s_status
{
	pid_t			pid;
	enum {
					stopped,
					running
	}				state;
	int				started_time;
	int				stopped_time;
}					t_status;

typedef struct		s_shared
{
	t_status		status[500];
}					t_shared;

typedef struct		s_tm
{
	t_job			jobs[1000];
//	t_status		status[1000];
//	t_status		*status;
	t_shared		*shared;
	int				jobs_cnt;
	char			**env;
	char			*cmd;
	pid_t			jobs_watcher;
	
}					t_tm;

void	ft_init_job(t_job *job)
{
	int i;

	i = -1;
	ft_bzero(job->cmd, 1000);
	job->nb_procs = 0;
	ft_bzero((char*)job->umask, 5);
	ft_bzero(job->working_dir, 1000);
	job->autostart = 0;
	job->autorestart = 0;
	while (++i < 3)
		job->exit_codes[i] = -42;
	job->start_retries = 0;
	job->start_time = 0;
	job->stop_time = 0;
	ft_bzero(job->stop_signal, 10);
	ft_bzero(job->stdout, 1000);
	ft_bzero(job->stderr, 1000);
	job->env = NULL;
}

void	ft_debug_job(t_tm *tm, int job_id)
{
	ft_printf("\n==> Debugging job id [%d]\n", job_id);
	ft_printf("\e[38;5;208m");
	ft_printf("name:\t\t'%s'\n", tm->jobs[job_id].name);
	ft_printf("cmd:\t\t'%s'\n", tm->jobs[job_id].cmd);
	ft_printf("nb_procs:\t[%d]\n", tm->jobs[job_id].nb_procs);
	ft_printf("umask:\t\t'%s'\n", tm->jobs[job_id].umask);
	ft_printf("workingdir:\t'%s'\n", tm->jobs[job_id].working_dir);
	ft_printf("autostart:\t[%d]\n", tm->jobs[job_id].autostart);
	ft_printf("autorestart:\t[%d]\n", tm->jobs[job_id].autorestart);
	ft_printf("startretries:\t[%d]\n", tm->jobs[job_id].start_retries);
	ft_printf("starttime:\t[%d]\n", tm->jobs[job_id].start_time);
	ft_printf("stoptime:\t[%d]\n", tm->jobs[job_id].stop_time);
	ft_printf("stopsignal:\t'%s'\n", tm->jobs[job_id].stop_signal);
	ft_printf("stdout:\t\t'%s'\n", tm->jobs[job_id].stdout);
	ft_printf("stderr:\t\t'%s'\n", tm->jobs[job_id].stderr);
	ft_printf("exitcodes:\t");
	for (int i = 0; tm->jobs[job_id].exit_codes[i] != -42; i++)
		ft_printf("[%d] ", tm->jobs[job_id].exit_codes[i]);
	ft_printf("\n");
	ft_printf("env:\n");
	for (t_keyval *tmp = tm->jobs[job_id].env; tmp; tmp = tmp->next)
		ft_printf("\t\t'%s' => '%s'\n", tmp->key, tmp->value);
	ft_printf("{eoc}");
}

void	ft_append_int_val(int list[], int val)
{
	int	i;

	i = 0;
	while (list[i] > -42)
		i++;
	list[i] = val;
}

void	ft_append_env(t_job *job, char *key, char *value)
{
	t_keyval *new;
	t_keyval *tmp;

	tmp = job->env;
	while (tmp && tmp->next)
		tmp = tmp->next;
	new = (t_keyval*)malloc(sizeof(t_keyval));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!tmp)
		job->env = new;
	else
		tmp->next = new;
}

void	ft_parse_token(t_tm *tm, char *token, char *value, int current_job)
{
	if (!ft_strcmp(token, "name"))
		ft_strcpy(tm->jobs[current_job].name, value);
	else if (!ft_strcmp(token, "cmd"))
		ft_strcpy(tm->jobs[current_job].cmd, value);
	else if (!ft_strcmp(token, "numprocs"))
		tm->jobs[current_job].nb_procs = ft_atoi(value);
	else if (!ft_strcmp(token, "umask"))
		ft_strcpy(tm->jobs[current_job].umask, value);
	else if (!ft_strcmp(token, "workingdir"))
		ft_strcpy(tm->jobs[current_job].working_dir, value);
	else if (!ft_strcmp(token, "autostart"))
		tm->jobs[current_job].autostart = ft_atoi(value);
	else if (!ft_strcmp(token, "autorestart"))
		tm->jobs[current_job].autorestart = ft_atoi(value);
	else if (!ft_strcmp(token, "exitcodes"))
		ft_append_int_val(tm->jobs[current_job].exit_codes, ft_atoi(value));
	else if (!ft_strcmp(token, "startretries"))
		tm->jobs[current_job].start_retries = ft_atoi(value);
	else if (!ft_strcmp(token, "starttime"))
		tm->jobs[current_job].start_time = ft_atoi(value);
	else if (!ft_strcmp(token, "stoptime"))
		tm->jobs[current_job].stop_time = ft_atoi(value);
	else if (!ft_strcmp(token, "stopsignal"))
		ft_strcpy(tm->jobs[current_job].stop_signal, value);
	else if (!ft_strcmp(token, "stdout"))
		ft_strcpy(tm->jobs[current_job].stdout, value);
	else if (!ft_strcmp(token, "stderr"))
		ft_strcpy(tm->jobs[current_job].stderr, value);
	else
		ft_printf("Unknown token: [%s]\n", token);
}

void	ft_parse_next_token(t_tm *tm, char *line, int current_job)
{
	char	*token;

	token = NULL;
	if (ft_strlen(line) > 1 && line[0] == '-')
		ft_append_int_val(tm->jobs[current_job].exit_codes, ft_atoi(line + 1));
	else if (ft_strlen(line) > 1 && line[0] == '_' && ft_strchr(line, ':'))
	{
	//	ft_printf("add key -> value to env\n");
		ft_sprintf(&token, "%.*s", ft_strchr(line, ':') - line - 1, line + 1);
		if (ft_strlen(line) > (ft_strlen(token) + 3))
			ft_append_env(&tm->jobs[current_job], token, line + ft_strlen(token) + 3);
	//	ft_printf("adding key: [%s], value: [%s]\n", token, line + ft_strlen(token) + 3);
	}
	else if (ft_strchr(line, ':'))
	{
		ft_sprintf(&token, "%.*s", ft_strchr(line, ':') - line, line);
		if (ft_strlen(line) > (size_t)((ft_strchr(line, ':') - line) + 2))
			ft_parse_token(tm, token, line + (ft_strchr(line, ':') - line) + 2, current_job);
	//		ft_printf("token: [%s], value: [%s]\n", token, line + (ft_strchr(line, ':') - line) + 2);
		else
			ft_printf("bad token: [%s]\n", token);
	}	
}

void	ft_parse_config(t_tm *tm, char *config_file)
{
	int		fd;
	char	*line;
	int		current_job;
	
	current_job = 0;
	ft_init_job(&tm->jobs[current_job]);
	fd = open(config_file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (line && !line[0])
			ft_init_job(&tm->jobs[++current_job]);
		else
			ft_parse_next_token(tm, line, current_job);
		free(line);
	}
	free(line);
	close(fd);
	tm->jobs_cnt = current_job + 1;
}

//------------------------------------------------------------------------------
void	ft_process_watcher(t_tm *tm)
{
//	pid_t	pid;
	int		i;
	int		res;

//while (1)
//{
	i = -1;
	while (++i < tm->jobs_cnt)
	{
	//	pid = waitpid(tm->status[i].pid, NULL, WNOHANG|WUNTRACED);
//		pid = waitpid(tm->shared->status[i].pid, NULL, WNOHANG|WUNTRACED);
		if (!tm->shared->status[i].pid)
			res = 99;
		else
			res = kill(tm->shared->status[i].pid, 0);
		if (res == 0)
		{
	//		ft_printf("process: [%s] is still running.\n", tm->jobs[i].name);
			tm->shared->status[i].state = running;
			tm->shared->status[i].started_time = time(NULL);
		}
//		else if (res == -1)
//		{
			// maybe we should remove current pid or retry
		//	ft_printf("waitpid error for process '%s' (pid %d)\n", tm->jobs[i].name, tm->status[i].pid);
	//		ft_printf("waitpid error for process '%s' (pid %d)\n", tm->jobs[i].name, tm->shared->status[i].pid);
//			ft_printf("process watcher error checking: [%s]\n", tm->jobs[i].name);
//		}
//		else if (res > 0)
		else
		{
//			ft_printf("process: [%s] terminated.\n", tm->jobs[i].name);
			tm->shared->status[i].state = stopped;
			tm->shared->status[i].stopped_time = time(NULL);
		}
		sleep(3);
	}
//}
}

void	ft_start_process_watcher(t_tm *tm)
{
	pid_t	father;
//	t_status	*shared;
//	pthread_t thread1;

//	for (int cnt = 0; cnt < 5; cnt++)

//	if(pthread_create(&thread1, NULL, ft_process_watcher(tm), NULL) == -1) {
//		perror("pthread_create");

//int shm_id = shmget(IPC_PRIVATE, sizeof(t_status), IPC_CREAT | 0666);
//shm = shmat(shm_id, 0, 0);
(void)tm;
//shared = (t_status*)mmap(NULL, sizeof(t_status), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
//shared->state = 1;
//ft_printf("Genial: [%d]\n", shared->state);

	father = fork();
	if (!father)
	{
		while (1)
			ft_process_watcher(tm);
//		exit(0);
	}
	else
	{
		ft_printf("Starting process watcher. [pid: %d]\n", father);
	}
}
//------------------------------------------------------------------------------
void	ft_debug_status(t_status *status)
{
	ft_printf("pid:\t[%d]\n", status->pid);
	ft_printf("state:\t[%d]\n", status->state);
	ft_printf("stime:\t[%d]\n", status->started_time);
	ft_printf("ttime:\t[%d]\n", status->stopped_time);
}

void	ft_init_status(t_status *status)
{
	status->pid = 0;
	status->state = stopped;
	status->started_time = 0;
	status->stopped_time = 0;
}

void	ft_exec_job(t_tm *tm, int id_job)
{
/*	pid_t pid;

	ft_init_status(&tm->status[id_job]);
	pid = fork();
	if (!pid)
	{
		ft_printf("Starting program: [%s]\n", tm->jobs[id_job].name);
		char *args[3] = { "ls", "-l", NULL };
		execve("/bin/ls", args, tm->env);
		tm->status[id_job].started_time = time(NULL);
		ft_printf("on dirait que lexec a merdée");
	}
	if (pid > 0)
		wait(&pid);*/
	ft_printf("executing: [%s]\n", tm->jobs[id_job].name);
//	tm->status[job_id].


//	endID = waitpid(childID, &status, WNOHANG|WUNTRACED);
	//   -1: error
	//    0: child still running
	// else: child ended

	pid_t	father;
	char	**args;

//	ft_init_status(&tm->status[id_job]);
ft_init_status(&tm->shared->status[id_job]);
	father = fork();
	if (!father)
	{
		
		args = NULL;
		args = ft_strsplit(tm->jobs[id_job].cmd, ' ');
		if (args && execve(args[0], args, tm->env) < 0)
			ft_printf("{red}Error executing '%s'{eoc}\n", tm->jobs[id_job].name);
		ft_free_list(args);
		exit(0);
	}
	if (father > 0)
	{
		tm->shared->status[id_job].pid = father;
		ft_printf("process id: [%d]\n", father);
	}
}

void	ft_get_job_status(t_tm *tm, int id_job)
{
/*	struct stat		fs;
	char			*process_path;
	
	process_path = NULL;
	ft_sprintf(&process_path, "/proc/%d", tm->shared->status[id_job].pid);
	ft_printf("p_path: [%s]\n", process_path);
	int res = stat(process_path, &fs);
	ft_printf("res: [%d]\n", res);
	ft_printf("omfg: [%s]\n", ctime(&fs.st_mtime));*/

	// name RUNNING pid uptime
//	ft_printf("state: [%d]\n", tm->status[id_job].state);
	ft_printf("%s", tm->shared->status[id_job].state ? "\e[92m" : "\e[91m");
	ft_printf("%-20s ", tm->jobs[id_job].name);
	ft_printf("%-10s ", tm->shared->status[id_job].state ? "RUNNING" : "STOPPED");
	ft_printf("pid %-10d", tm->shared->status[id_job].pid);
//	ft_printf("%-10s\n", "uptime 0:05:03");
	ft_printf("uptime %-10d\n", time(NULL) - tm->shared->status[id_job].started_time);
	ft_printf("{eoc}");
//	ft_printf("Uptime: ", time(NULL) - tm->status[id_job].stopped_time);
}

void	ft_cmd_start(t_tm *tm, char *name)
{
	int i;

	i = -1;
	while (++i < tm->jobs_cnt)
		if (!ft_strcmp(name, tm->jobs[i].name) || !ft_strcmp(name, "all"))
			ft_exec_job(tm, i);
}

void	ft_cmd_status(t_tm *tm, char *name)
{
	int i;

	i = -1;
	while (++i < tm->jobs_cnt)
		if (!ft_strcmp(name, tm->jobs[i].name) || !ft_strcmp(name, "all"))
			ft_get_job_status(tm, i);
}

void	ft_autostart_jobs(t_tm *tm)
{
	int i;

	i = -1;
	while (++i < tm->jobs_cnt)
	{
		if (tm->jobs[i].autostart == 1)
			ft_exec_job(tm, i);
	}
}
//------------------------------------------------------------------------------

void	ft_process_cmd(t_tm *tm)
{
	if (!ft_strcmp(tm->cmd, "exit"))
		exit(0);
	else if (!strncmp(tm->cmd, "start", 5) && (ft_strlen(tm->cmd) > 6))
	{
		ft_printf("starting: [%s]\n", tm->cmd + 6);
		ft_cmd_start(tm, tm->cmd + 6);
	}
	else if (!strncmp(tm->cmd, "restart", 7) && (ft_strlen(tm->cmd) > 8))
	{
		ft_printf("restarting: [%s]\n", tm->cmd + 8);
	}
	else if (!strncmp(tm->cmd, "stop", 4) && (ft_strlen(tm->cmd) > 5))
	{
		ft_printf("stopping: [%s]\n", tm->cmd + 5);
	}
	else if (!strncmp(tm->cmd, "status", 6) && (ft_strlen(tm->cmd) > 7))
	{
		ft_printf("getting status of: [%s]\n", tm->cmd + 7);
		ft_cmd_status(tm, tm->cmd + 7);
	}
	else if (!strcmp(tm->cmd, "reload"))
	{
		ft_printf("reloading config file\n");
	}
	else if (!strcmp(tm->cmd, "shutdown"))
	{
		ft_printf("Quitting taskmaster\n");
		exit(0);
	}
}

void	ft_get_user_input(t_tm *tm)
{
	if (tm->cmd)
		free(tm->cmd);
	ft_printf("$> ");
	get_next_line(0, &tm->cmd);
}

int		main(int argc, char *argv[], char *env[])
{
	t_tm	tm;

	signal(SIGCHLD, SIG_IGN); // ignore fcking SIGCHLD so wait become useless and no more zombies
	tm.shared = (t_shared*)mmap(NULL, sizeof(t_shared), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	tm.env = env;
	tm.jobs_cnt = 0;
	if (argc == 2)
	{
		ft_parse_config(&tm, argv[1]);
		for (int i = 0; i < tm.jobs_cnt; i++)
			ft_debug_job(&tm, i);
	//	ft_autostart_jobs(tm);
	ft_start_process_watcher(&tm);
		while (1)
		{
			ft_get_user_input(&tm);
			ft_process_cmd(&tm);
//			ft_start_process_watcher(&tm);
		}
	}
	else
		ft_printf("usage: taskmaster config_file\n");
munmap(tm.shared, sizeof(t_shared));
	return (0);
}
