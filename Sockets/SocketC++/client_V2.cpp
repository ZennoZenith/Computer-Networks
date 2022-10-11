#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <sstream>  // for string streams
#include <thread>   // for multithreading
#include <stdlib.h> // for exit()

#define PORT 8080

using namespace std;

bool IS_CONNECTED = true;

void sendMsg(int, int);
void recvMsg(int, int);

int calculateWord(char *sentence)
{
  int words = 0;
  int i = 0;
  while (sentence[i] != '\0')
  {
    if (sentence[i] == ' ' || sentence[i] == '.')
      words++;
    i++;
  }
  return words;
}

void sendMsg(int sock, int client_fd)
{
  char message[1024] = {0};
  while (true)
  {
    printf("Enter message : ");
    cin.getline(message, 1024);

    if (!IS_CONNECTED)
      break;

    if (strcmp(message, "!exit") == 0)
    {
      // closing the connected socket
      send(sock, message, strlen(message), 0);
      close(client_fd);
      printf("Connection closed\n");
      break;
    }
    send(sock, message, strlen(message), 0);
    // closing the connected socket
    // close(client_fd);
  }
}

void recvMsg(int sock, int client_fd)
{
  char buffer[1024] = {0};
  int valread;
  // while (true)
  // {
  valread = read(sock, buffer, 1024);
  if (valread <= 0)
  {
    // closing the connected socket
    close(client_fd);
    printf("Server down. Closed connection, client_fd(%d)\n", client_fd);
    IS_CONNECTED = false;
    exit(EXIT_FAILURE);
    // break;
  }
  buffer[valread] = '\0';
  printf("Message from server : %s\n", buffer);
  // }

  // send(sock, buffer, strlen(buffer), 0);

  int words = calculateWord(buffer);
  ostringstream str1;
  str1 << words;
  const char *temp = str1.str().c_str();

  printf("Number of words in given message : %d\n", words);
  printf("Sending response...\n");
  send(sock, temp, strlen(temp), 0);
}

int main(int argc, char const *argv[])
{
  struct sockaddr_in serv_addr;
  int sock = 0;
  int client_fd = -1;

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

  IS_CONNECTED = true;

  // thread t1(sendMsg, sock, client_fd);
  // thread t2(recvMsg, sock, client_fd);

  // t1.join();
  // t2.join();

  recvMsg(sock, client_fd);
  // sendMsg(sock, client_fd);

  return 0;
}
