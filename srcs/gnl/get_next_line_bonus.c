#include "minishell.h"

/*This function takes the read_line string, splits it in 
 * both line and rest_line, fils lline_out with the line
 * and redefines read_line as the rest.*/
char	*ft_write_line(ssize_t len_rd, char *rd_ln, char **ln_out)
{
	char		*rest_ln;
	ssize_t		len;
	ssize_t		rest_len;

	len = 0;
	while (*(rd_ln + len) != '\n' && *(rd_ln + len))
		len++;
	*ln_out = (char *)malloc(sizeof(char) * (len + 1));
	if (!*ln_out)
		return (NULL);
	*(rd_ln + len) = '\0';
	rest_len = len_rd - len;
	while (len-- >= 0)
		*(*(ln_out) + len + 1) = *(rd_ln + len + 1);
	rest_ln = (char *)malloc(sizeof(char) * (rest_len));
	if (rest_len == 0 || !rest_ln)
	{
		free(rd_ln);
		free(rest_ln);
		return (NULL);
	}
	while (rest_len-- > 0)
		*(rest_ln + rest_len) = *(rd_ln + rest_len + 1 + ft_strlen(*ln_out));
	free(rd_ln);
	return (rest_ln);
}

/*This function reads from the fd until it either ends or reads a
 * \n. Then it passes what's been read to the write_line function.*/
char	*ft_read_line(int fd, char *read_line)
{
	char	*buff;
	ssize_t	read_ret;

	read_ret = BUFFER_SIZE;
	while (!(ft_strchr(read_line, '\n')) && read_ret == BUFFER_SIZE)
	{
		buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		read_ret = read(fd, buff, BUFFER_SIZE);
		if (read_ret < 0)
		{
			free(buff);
			return (NULL);
		}
		*(buff + read_ret) = '\0';
		read_line = ft_strjoin_n_free(read_line, buff);
	}
	return (read_line);
}

/*This function fills *line with the line read from the archive fd. It 
 * has "memory", as in it remembers what was the last line printed from
 * that same fd, and so it prints the next to that last one. If succesfull,
 * the output is 1, if the line is the last one from the file then the 
 * output is a 0, and if there has been some kind of error it outputs a -1.*/
int	get_next_line(int fd, char **line)
{
	static char		*r_fd[FD_SETSIZE];

	if (BUFFER_SIZE > 0 && line && fd >= 0 && fd <= FD_SETSIZE)
	{
		r_fd[fd] = ft_read_line(fd, r_fd[fd]);
		if (!r_fd[fd])
			return (-1);
		else
		{
			if (!ft_strchr(r_fd[fd], '\n'))
			{
				r_fd[fd] = ft_write_line(ft_strlen(r_fd[fd]), r_fd[fd], line);
				return (0);
			}
			r_fd[fd] = ft_write_line(ft_strlen(r_fd[fd]), r_fd[fd], line);
		}
	}
	else
		return (-1);
	return (1);
}
