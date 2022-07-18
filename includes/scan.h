#ifndef SCAN_H
# define SCAN_H

int	is_quote(char *str);
int	is_redirect(char *str);
int	is_separator(char *str);

void	quote_token(t_shell *hell, int *i);
void	redirect_token(t_shell *hell, int *i);
void	create_token(t_shell *hell, int start, int i);

#endif