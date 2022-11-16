#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"

void	recive_str(int sig, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int	i;

	(void)context;
	if (!i)
	{
		i = 1;
		c = 0;
	}
	c |= (sig == SIGUSR2);
	if (i++ == 8)
	{
		if (!c)
		{
			kill(info->si_pid, SIGUSR2);
			return;
		}
		ft_putchar_fd(c, 1);
		i = 1;
		c = 0;
		kill(info->si_pid, SIGUSR1);
	}
	else
		c <<= 1;
}
int	main()
{
	struct sigaction	s_sigaction;
	
	ft_putnbr_fd(getpid(), 1);
	s_sigaction.sa_sigaction = recive_str;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
}