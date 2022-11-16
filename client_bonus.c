#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"
#include <stdlib.h>

int	ft_sleep(int i)
{
	static int	recived;
	if (!recived)
		recived = 0;
	if (i == 0)
		recived++;
	return(recived);
}
void	recive_signals(int sig)
{
	int	i;

	if (sig == SIGUSR1)
		ft_sleep(0);
	else
	{
		i = ft_sleep(1);
		ft_putnbr_fd(i, 1);
		exit(0);
	}

}
void	sendbits(int pid, char *s)
{
	int	bit;
	char	c;

	bit = 8;
	while(*s)
	{
		c = *s++;
		while (bit-- >= 0)
		{
			if (c >> bit & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
			bit--;
		}
		bit = 8;
	} 
	while (bit--)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

int main (int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
		return(1);
	signal(SIGUSR1, recive_signals);
	signal(SIGUSR2, recive_signals);
	ft_putstr_fd("Sent: ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("Recived: ", 1);
	sendbits(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return(0);
}