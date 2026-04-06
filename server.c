/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnasimi <mnasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:19:00 by mnasimi           #+#    #+#             */
/*   Updated: 2026/04/06 13:19:02 by mnasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void	ft_handler(int signal, siginfo_t *info, void *context)
{
	static int				bit = 0;
	static unsigned char	c = 0;
	static pid_t			current_pid = 0;

	(void)context;
	if (current_pid != info->si_pid)
	{
		current_pid = info->si_pid;
		bit = 0;
		c = 0;
	}
	if (signal == SIGUSR1)
		c |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		bit = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

void	ft_putnbr(int n)
{
	char	c;

	if (n >= 10)
		ft_putnbr(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
		return (write(2, "Wrong usage\n", 12), 1);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (write(2, "sigaction error\n", 16), 1);
	while (1)
		pause();
	return (0);
}
