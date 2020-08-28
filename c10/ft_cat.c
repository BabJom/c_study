#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void echo()
{
  char data[100];
  int n;
  char c;

  while (1)
  {
    c = '0';

    n = read(0, data, 100);
    if (n < 0 || n == 0x80)
    {
      write(1, &n, 1);
      exit(-1);
    }
    write(1, data, n);  
  }
}

int main(int argc, char *argv[]) {
  int fd;
  char buf[4096];
  char n;
  int i;

  if (argc == 1)
    echo();
  else if (argc >= 2)
  {
    i = 2;
    while (i <= argc)
    {
     fd = open(argv[i - 1], O_RDONLY);
     n = read(fd, buf, 4096);
     if (n > 0)
      write(1, buf, n);
     else
      write(1, "cat: asdf: No such file or directory\n", 37);
     i++;
    }
    close (fd);
  }
}
