#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
int READLINE_READ_SIZE = 512;

void init_my_readline(){
  READLINE_READ_SIZE = 512;
}

//function to read a line from a file descriptor
char *my_readline(int fd){
    // uzunlik -- length
  char *line = NULL;
  // ozgaruvchilarni e`lon qilamiz -- we declare variables
  int number_alloc = 0;
  int l = 0;
  char m = 0;
  int readnumber = 0;
  // Bu erda biz tekshirish uchun sikl aylantiramiz -- Here we cycle to check
  for (l = 0; l < READLINE_READ_SIZE; l++){
    
    readnumber = read(fd, &m, 1);
    // agar readnumber teng bo`lsa o ga -- if readnumber is equal to o
    if (readnumber == 0){
        //siklni to`xtat -- stop the cycle
      break;
    }
    //agar readnumber teng bo`lsa -1 ga -- if readnumber is equal to -1
    if (readnumber == -1){
      perror("read");
      exit(EXIT_FAILURE);
    }
    // if (m == '\n')
    // {
    //   break;
    // }
    // agar number_alloc teng bo`lsa 0 ga -- if number_alloc is equal to 0
    if (number_alloc == 0){
      line = malloc(sizeof(char) * READLINE_READ_SIZE);
      //agar line teng bo`lsa NULL ga -- if line is equal to NULL
      if (line == NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
      }
      number_alloc = READLINE_READ_SIZE;
    }

    //agar l teng bo`lsa number_alloc dan 1 ni ayirilganiga -- 1 is subtracted from number_alloc if l is equal
    if (l == number_alloc - 1){
        //line ni qiymatini o`zgartirish -- change the value of line
      line = realloc(line, sizeof(char) * (number_alloc + READLINE_READ_SIZE));
      // agar line teng bo`lsa NULL ga -- if line is equal to NULL
      if (line == NULL){
        perror("realloc");
        exit(EXIT_FAILURE);
      }
      // number_alloc ga READLINE_READ_SIZE ni qo`shish -- Add READLINE_READ_SIZE to number_alloc
      number_alloc += READLINE_READ_SIZE;
    }
    // line ni 
    line[l] = m;
  }
  return line;
}

int main(int ac, char **av)
{
  char *str = NULL;

  int fd = open("./README.md", O_RDONLY);
  while ((str = my_readline(fd)) != NULL)
  {
      printf("%s\n", str);
      free(str);
  }
  close(fd);
  //
  //  Yes it's also working with stdin :-)
  //  printf("%s", my_readline(0));
  //

  return 0;
}