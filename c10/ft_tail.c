#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define error_msg1 ": cannot open '"
#define error_msg1_2 "' for reading: No such file or directory"
#define error_msg2 ": invalid number of bytes: `"

int ft_strlen(char *str)
{
  int i;
  i = 0;
  while (str[i])
    i++;
  return (i);
}

int ft_atoi(char *str)
{
  int i;
  int r;

  i = 0;
  while (str[i])
  {
    if (str[i] - '0' < 0 || str[i] - '0' > 9)
      return -1;
    r = r * 10 + str[i] - '0';
    i++;
  }
  return (r);
}

void echo(int i, char **str)
{
  write(1, str[0]+2, ft_strlen(str[0])-2);
  if (i == 0)
  {
    write(1, &error_msg2, ft_strlen(error_msg2));
    write(1, str[1], ft_strlen(str[1]));
    write(1, "`", 1);
  }
  if (i == 1)
  {
    write(1, &error_msg1, ft_strlen(error_msg1));
    write(1, str[1], ft_strlen(str[1]));
    write(1, &error_msg1_2, ft_strlen(error_msg1_2));
  }
  if (i >= 2)
  {
    write(1, &error_msg1, ft_strlen(error_msg1));
    write(1, str[i], ft_strlen(str[i]));
    write(1, &error_msg1_2, ft_strlen(error_msg1_2));
  }
  write(1,"\n", 1);
}

void multiple(char **str, int argc)
{
  int i;
  int n;
  int fd;
  char buf[4096];
  
  n = ft_atoi(str[1]);
  i = 2;
  if (n <= 0)
  {
   echo(1, str);
   return ;
  }
  while (i <argc)
  {
    fd = open(str[i], O_RDONLY);
    if (fd < 0)
      echo(i, str);
    else if(read(fd, buf, n) > 0)
    {
      if (i != 2)
        write(1, "\n", 1);
      write(1, "==> ", 4);
      write(1, str[i], ft_strlen(str[i]));
      write(1, " <==\n", 5);
      write(1, buf, n);
    }
    close(fd);
    i++;
  }
}

int main(int argc, char *argv[]) {
  int fd;
  char buf[4096];
  int n = -1;
  int i;

  if (argc == 1)
    ;
  else if (argc == 2)
    echo(1, argv);
  else if (argc == 3)
  {
    n = ft_atoi(argv[1]);
    fd = open(argv[2], O_RDONLY);
    if (n <= 0)
    {
      echo(1, argv);
      return (0);
    }
    if (fd < 0)
    {
      echo(2, argv);
      return (0);
    }
    if(read(fd, buf, n) > 0)
      write(1, buf, n);
    close(fd);
  }
  else
    multiple(argv, argc);
  return (0);
}
