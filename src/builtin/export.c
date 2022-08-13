int export( char *args, t_hash_elem **table)
{
	char *arg_find;
	t_hash_elem *check;

	if !ft_strchr(args, "=")
		arg_find = ft_strdup(args);
	else
		arg_find = ft_substr(args, 0, ft_strchr(args, "=") - args);
	check = table_lookup(*table, arg_find);
	if (check)
		remove_element(table, arg_find);
	insert_element(table, args);
	free(arg_find);
	return (0);	
}