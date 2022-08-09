int check_n (char *args)
{
	if (ft_strncmp(args, "-n",2) == 0)
		return (1);
	else
		return (0);
}

int echo(char *args, int fd)
{
	int i;
	int nline;

	i = 1;
	nline = check_n(args[i]);
	if (nline)
		i++;
	while (args[i])
	{
		if (args[i + 1)
			write(fd, " ", 1);
		else
			write(fd, args[i], ft_strlen(args[i]);
		i++;	
	}
	if (check_n)
		return (0);
	write(fd, "\n", 1);
}