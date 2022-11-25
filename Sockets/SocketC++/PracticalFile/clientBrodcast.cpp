#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <thread>   // for multithreading
#include <stdlib.h> // for exit()

#define PORT 8080
#define ALWAYS_RECV true

using namespace std;

bool IS_CONNECTED = true;

void connect(sockaddr_in &serv_addr, int &sock, int &client_fd)
{
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("\n Socket creation error \n");
    exit(1);
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  // Convert IPv4 and IPv6 addresses from text to binary form
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
  {
    printf("\nInvalid address/ Address not supported \n");
    exit(1);
  }

  if ((client_fd = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) < 0)
  {
    printf("\nConnection Failed \n");
    exit(1);
  }
}

void sendMsg(int sock, int client_fd, bool alwaysReceive = false)
{
  char message[1024] = {0};
  int key = 3;
  while (alwaysReceive)
  {
    cin.getline(message, 1024);

    if (!IS_CONNECTED)
      exit(1);

    if (strcmp(message, "!exit") == 0)
    {
      // closing the connected socket
      send(sock, message, strlen(message), 0);
      close(client_fd);
      printf("Connection closed\n");
      exit(1);
    }
    send(sock, message, strlen(message), 0);
  }
}

void recvMsg(int sock, int client_fd, bool alwaysReceive = false)
{
  char buffer[1024] = {0};
  int valread;
  while (alwaysReceive)
  {
    valread = read(sock, buffer, 1024);
    if (valread <= 0)
    {
      // closing the connected socket
      close(client_fd);
      printf("Server down. Closed connection, client_fd(%d)\n", client_fd);
      IS_CONNECTED = false;
      exit(EXIT_FAILURE);
    }
    buffer[valread] = '\0';
    printf("Received message : %s\n", buffer);
  }
}

int main(int argc, char const *argv[])
{
  struct sockaddr_in serv_addr;
  int sock = 0;
  int client_fd = -1;

  connect(serv_addr, sock, client_fd);
  IS_CONNECTED = true;

  thread t1(sendMsg, sock, client_fd, ALWAYS_RECV);
  thread t2(recvMsg, sock, client_fd, ALWAYS_RECV);

  t1.join();
  t2.join();

  close(client_fd);
  printf("Connection closed\n");
  return 0;
}
