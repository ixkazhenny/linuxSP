#include <stdio.h>

int main()
{
  /* int fflush(FILE *stream); */

  FILE *stream = fopen("data", "w");
  fflush(stream);
  /* with fsync() */
  return 0;
}
