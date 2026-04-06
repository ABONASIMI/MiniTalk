/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnasimi <mnasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:19:10 by mnasimi           #+#    #+#             */
/*   Updated: 2026/04/06 13:19:12 by mnasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	long	result;

	result = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result > 2147483647)
			return (-1);
		str++;
	}
	return ((int)result);
}

int	ft_get_pid(char *str)
{
	int	pid;

	pid = ft_atoi(str);
	if (pid <= 0 || kill(pid, 0) == -1)
	{
		write(2, "Invalid PID\n", 12);
		return (0);
	}
	return (pid);
}

int	ft_init_client_signals(struct sigaction *sa)
{
	sigemptyset(&sa->sa_mask);
	sigaddset(&sa->sa_mask, SIGUSR1);
	sa->sa_flags = 0;
	sa->sa_handler = ft_ack_handler;
	if (sigaction(SIGUSR1, sa, NULL) == -1)
		return (0);
	return (1);
}
