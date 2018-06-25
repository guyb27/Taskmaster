
#include <stdio.h>

typedef struct		s_htime
{
	int				h;
	int				m;
	int				s;
}					t_htime;

void	ft_get_htime(t_htime *htime, size_t time)
{
    if (time > 3600)
    {
        htime->m = time / 60;
        htime->h = htime->m / 60;
        htime->s = time % 60;
        htime->m = htime->m % 60;
    }
    else
    {
        htime->h = 0;
        htime->m = time / 60;
        htime->s = time % 60;
    }
}

int     main(void)
{
    t_htime htime;

    int i = -1;
    while (++i > -1 && i < 128)
    {
        ft_get_htime(&htime, i);
        printf("%02d:%02d:%02d\n", htime.h, htime.m, htime.s);
   //     sleep(1);
    }

    printf("3604 / 60: [%d]\n", 3604 / 60);
}