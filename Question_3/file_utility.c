#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

struct Emp { int id; char name[20]; int sal; };

int main() {
  int fd = open("emp.dat", O_RDWR | O_CREAT | O_TRUNC, 0644);

  struct Emp e1 = {1 , "Alice", 5000}, e2  = {2, "Bob", 6000};
  write(fd, &e1, sizeof(struct Emp));
  write(fd, &e2, sizeof(struct Emp));

  lseek(fd, 1 * sizeof(struct Emp), SEEK_SET);
  struct Emp e2_up = {2, "Bob", 7500};
  write(fd, &e2_up, sizeof(struct Emp));

  lseek(fd, 1 * sizeof(struct Emp), SEEK_SET);
  struct Emp tmp;
  read(fd, &tmp, sizeof(struct Emp));
  printf("Read ID: %d, Name: %s, Salary: %d\n", tmp.id, tmp.name, tmp.sal);

  close(fd);
  return 0;
}
