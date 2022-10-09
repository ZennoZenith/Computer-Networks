// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <thread>   // for multithreading
#include <stdlib.h> // for exit()

#define PORT 8080

using namespace std;

bool IS_CONNECTION_CLOSED = true;

void writeServer(int sock, int client_fd)
{
  char hello[1024] = {0};
  while (true)
  {
    printf("Enter message : ");
    scanf("%s", hello);
    printf("Hello message sent : %s\n", hello);

    if (IS_CONNECTION_CLOSED)
      break;

    if (strcmp(hello, "!exit") == 0)
    {
      // closing the connected socket
      send(sock, hello, strlen(hello), 0);
      close(client_fd);
      break;
    }
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // closing the connected socket
    // close(client_fd);
  }
}
void recvServerData(int sock, int client_fd)
{
  char buffer[1024] = {0};
  int valread;
  while (true)
  {
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);
    if (valread <= 0)
    {
      // closing the connected socket
      close(client_fd);
      printf("Closed connection, client_fd(%d)\n", client_fd);
      IS_CONNECTION_CLOSED = true;
      exit(EXIT_FAILURE);
      break;
    }
  }
}

int main(int argc, char const *argv[])
{
  int sock = 0, valread, client_fd;
  struct sockaddr_in serv_addr;
  // char *hello = "Hello from client";
  char hello[1024] = {0};
  char buffer[1024] = {0};
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("\n Socket creation error \n");
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  // Convert IPv4 and IPv6 addresses from text to binary
  // form
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
  {
    printf(
        "\nInvalid address/ Address not supported \n");
    return -1;
  }

  if ((client_fd = connect(sock, (struct sockaddr *)&serv_addr,
                           sizeof(serv_addr))) < 0)
  {
    printf("\nConnection Failed \n");
    return -1;
  }
  IS_CONNECTION_CLOSED = false;

  thread t1(writeServer, sock, client_fd);
  thread t2(recvServerData, sock, client_fd);

  t1.join();
  t2.join();
  return 0;
}
