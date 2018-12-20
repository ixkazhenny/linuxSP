#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define TIMEOUT 5
#define BUF_LENT 1024

int main()
{
  /* int select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, structt timeval *timeout); */

  /* FD_CLR(int fd, fd_set *set); in set, delete fd */
  /* FD_ISSET(int fd, fd_set *set); in set, verify fd*/
  /* FD_SET(int fd, fd_set *set); fd add to set */
  /* FD_ZERO(fd_set *set); in set, all are deleted*/
  
  /* FD_ZERO -> select() -> (FD_SET, FD_CLR) -> FD_ISSET */
  
  struct timeval tv;
  fd_set readfds;
  int ret;

  /* waiting for INPUT on stdin*/
  FD_ZERO(&readfds);
  FD_SET(STDIN_FILENO, &readfds);

  /*setting to struct timeval for wait 5sec to select() */
  tv.tv_sec = TIMEOUT;
  tv.ttv_usec = 0;

  /* waiting INPUT */
  ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
  if (ret == -1) {
    perror("select");
    return 1;
  }
  else if (!ret) {
    printf("%d seconds elapsed.\n", TIMEOUT);
    return 0;
  }

  /*
   * fd can read!
   */

  if (FD_ISSET(STDIN_FILENO, &readfds)){
    char buf[BUF_LEN+1];
    int len;

    /*no read() is blocked*/
    len = read(STDIN_FILENO, buf, BUF_LEN);
    if (len == -1) {
      perror("read");
      return 1;
    }

    if (len) {
      buf[len] = '\0';
      printf("read: %s\n", buf);
    }
    return 0;
  }

  fprintf(stderr, "This shoulld not happen!\n");
  return 1;
}
