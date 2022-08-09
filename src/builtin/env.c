int env(t_hash_elem **table, int fd)
{
	t_hash_elem *tmp;

	tmp = *table;
	while (tmp)
	{
		write(fd, tmp->key, ft_strlen(tmp->key));
		write(fd, "=", 1);
		write(fd, tmp->value, ft_strlen(tmp->value));
		write(fd, "\n", 1);
		tmp = tmp->next;
	}
	return(0);
}