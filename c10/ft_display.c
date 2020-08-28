#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
  int fd;
  char buf[4096];
  char n;
  if (argc == 1)
  {
   write(1,"File name missing\n",18);
   return 0;
  }
  else if (argc > 2)
  {
    write(1, "Too many arguments.\n", 21);
    return 0;
  }
  fd = open(argv[1], O_RDONLY);
  if (fd < 0)
    write(1, "Cannot read file.\n", 19);
  else 
  {
    n = read(fd, buf, 4096);
    if (n > 0)
      write(1, buf, n);
  }
  close(fd);
}
