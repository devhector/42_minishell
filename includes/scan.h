#ifndef SCAN_H
# define SCAN_H

typedef struct s_scan
{
	char	*token;
	char	*type;
	char	*error;
} t_scan;

int	is_quote(char c);
int	is_redirect(char c);
int	is_separator(char c);
int	has_quote(char *str);

#endif