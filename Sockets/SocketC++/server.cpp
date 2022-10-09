#include <iostream>
#include <netinet/in.h>
// #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

#define PORT 3000
#define NI_MAXHOST 1025
#define NI_MAXSERV 32

int main(int argc, char const *argv[])
{
  // Creating a socket
  int listening = socket(AF_INET, SOCK_STREAM, 0);

  if (listening == -1)
  {
    cout << "Cannot create socket\n";
  }
  printf("lstening ? : %d\n", listening);

  // Forcefully attaching socket to the port 8080
  /*
  int opt = 1;
  if (setsockopt(listening, SOL_SOCKET,
                 SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt)))
  {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  */

  // Binding the socket to a IP / port
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);
  // inet_pton()

  if (bind(listening, (struct sockaddr *)&address,
           sizeof(address)) < 0)
  {
    cerr << "Cannot bind to IP/port";
    return -2;
  }

  // Mark socket for listning
  if (listen(listening, SOMAXCONN) == -1)
  {
    cerr << "Can't listen\n";
    return -3;
  }

  // Accept a call
  sockaddr_in cleint;
  socklen_t clientSize;
  char host[NI_MAXHOST];
  char svc[NI_MAXSERV];
  return 0;
}