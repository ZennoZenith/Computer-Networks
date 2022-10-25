// Client

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <sstream>  // for string streams
#include <stdlib.h> // for exit()

#define PORT 8080
#define NUMBER_BASE 10

using namespace std;

bool IS_CONNECTED = true;

char buffer[1024] = {0};

/**
 * Calculates number of non alphabetic character
 */
int calculateWord(char *sentence)
{
  int words = 0;
  int i = 0;
  while (sentence[i] != '\0')
  {
    if (sentence[i] < 'A' || sentence[i] == 'z' || (sentence[i] > 'Z' && sentence[i] < 'a'))
      words++;
    i++;
  }
  return words;
}

/**
 * Calculates number of words and then converts (int) to (char *)
 */
string intermediateFunc(char message[])
{
  int words = calculateWord(message);
  ostringstream str1;
  str1 << words;
  string temp = str1.str();
  strcpy(message, temp.c_str());
  return temp;
}

void connect(sockaddr_in &serv_addr, int &sock, int &client_fd)
{
  /**
   * int sock = socket(DOMAIN, TYPE, PROTOCOL)
   * DOMAIN: integer, specifies communication domain.
   * type: communication type
     SOCK_STREAM: TCP(reliable, connection oriented)
     SOCK_DGRAM: UDP(unreliable, connectionless)
   * Create a new socket of type TYPE in domain DOMAIN, using
     protocol PROTOCOL.  If PROTOCOL is zero, one is chosen automatically.
     Returns a file descriptor for the new socket, or -1 for errors.
   */
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

void sendMsg(int sock, int client_fd)
{
  int key = 3;

  if (!IS_CONNECTED)
    exit(1);

  if (strcmp(buffer, "!exit") == 0)
  {
    // closing the connected socket
    send(sock, buffer, strlen(buffer), 0);
    close(client_fd);
    printf("Connection closed\n");
    exit(1);
  }
  intermediateFunc(buffer);
  cout << "Number of words : " << buffer << endl;
  send(sock, buffer, strlen(buffer), 0);
}

void recvMsg(int sock, int client_fd)
{
  int valread;
  valread = read(sock, buffer, 1024);
  if (valread <= 0)
  {
    // closing the connected socket
    close(client_fd);
    printf("Server down. Closed connection, client_fd(%d)\n", client_fd);
    IS_CONNECTED = false;
    exit(EXIT_FAILURE);
    exit(1);
  }
  buffer[valread] = '\0';
  printf("Received message : %s\n", buffer);
}

int main(int argc, char const *argv[])
{
  struct sockaddr_in serv_addr;

  /**
   * sock: socket descriptor, an integer (like a file-handle)
   */
  int sock = 0;

  int client_fd = -1;

  connect(serv_addr, sock, client_fd);
  IS_CONNECTED = true;

  recvMsg(sock, client_fd);
  sendMsg(sock, client_fd);
  recvMsg(sock, client_fd);

  close(client_fd);
  printf("Connection closed\n");
  return 0;
}
