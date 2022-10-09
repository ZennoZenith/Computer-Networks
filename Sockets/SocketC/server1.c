#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 3000

int main(int argc, char const *argv[])
{
  int listening = socket(AF_INET, SOCK_STREAM, 0);

  if (listening == -1)
  {
    
  }
  printf("%d\n", listening);
  return 0;
}