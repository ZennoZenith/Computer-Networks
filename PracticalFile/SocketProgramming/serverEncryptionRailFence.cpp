// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <sstream> // for string streams
#include <string>  // for string
#include <thread>  // for multithreading

#include "cryptography.h"

using namespace std;

#define PORT 8080
#define REQUEST_QUEUE_LEN 3
#define MAX_CLIENTS 100
#define ALWAYS_RECV true
#define KEY 3

string intermediateFunc(char message[], int key)
{
  Cryptography c;
  c.setEncryptedText(message);
  c.setKey(key);
  strcpy(message, c.decrypt(RAILFENCE_CYPHER).c_str());
  return c.getEncryptedText();
}

class Server;

class Server
{
private:
  struct sockaddr_in address;
  int server_fd;
  int clients[MAX_CLIENTS];
  int numberOfClients;
  char buffer[1024];
  void sendMsg(int, int, const char *);
  void closeConnection(int, const char *);
  bool recvMsg(int);
  void sendToAll(int, const char *);
  void recvSendStructure(int, bool);

public:
  // Server();
  Server(int);
  void operator()(bool);
  ~Server();
};
// char Server::buffer[1024];

Server::Server(int port = PORT)
{
  this->numberOfClients = 0;

  int opt = 1;

  // Creating socket file descriptor
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0)
  {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Forcefully attaching socket to the port 8080
  if (setsockopt(server_fd, SOL_SOCKET,
                 SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt)))
  {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // Forcefully attaching socket to the port 8080
  if (bind(server_fd, (struct sockaddr *)&address,
           sizeof(address)) < 0)
  {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
  if (listen(server_fd, REQUEST_QUEUE_LEN) < 0)
  {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  cout << "Server started...\n";
}

Server::~Server()
{
  shutdown(server_fd, SHUT_RDWR);
  cout << "Server shutdown.\n";
}

void Server::closeConnection(int new_socket, const char *message = "Closed connection, new_socket(%d)\n")
{
  close(new_socket);
  int flag = 0;
  for (int i = 0; i < numberOfClients - 1; i++)
  {
    if (clients[i] == new_socket)
      flag = 1;
    if (flag == 1)
      clients[i] = clients[i + 1];
  }
  numberOfClients--;
  printf(message, new_socket);
}

bool Server::recvMsg(int new_socket)
{
  int valread;
  // char buffer[1024] = {0};
  valread = read(new_socket, buffer, sizeof(buffer));
  // if (strcmp(buffer, "!exit") == 0)
  // {
  //   closeConnection(new_socket);
  //   return false;
  // }

  if (valread <= 0)
  {
    // closing the connected socket
    // closeConnection(new_socket);
    return false;
  }

  // printf("client(%d) valread(%d)> %s\n", new_socket, valread, buffer);

  buffer[valread] = '\0';
  return true;
}

void Server::sendMsg(int from_socket, int to_socket, const char *message = "\0")
{
  if (*message != '\0')
    send(to_socket, message, strlen(message), 0);
}

void Server::sendToAll(int from_socket, const char *message = "\0")
{
  for (int i = 0; i < numberOfClients; i++)
  {
    sendMsg(from_socket, clients[i], message);
  }
}

void Server::recvSendStructure(int new_socket, bool alwaysReceive = false)
{

  do
  {
    if (!recvMsg(new_socket))
      break;
    printf("client(%d) > %s\n", new_socket, buffer);
    intermediateFunc(buffer, KEY);
    printf("Decrypted messsage using key value as 3 : %s\n", buffer);

    // sendMsg(new_socket, new_socket, buffer);
    // sendToAll(new_socket, buffer);
  } while (alwaysReceive);

  closeConnection(new_socket);
}

void Server::operator()(bool alwaysReceive = false)
{
  int addrlen = sizeof(address);

  cout << "Server listning...\n";
  while (true)
  {
    int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (new_socket < 0)
    {
      perror("accept");
      exit(EXIT_FAILURE);
    }
    cout << "New conection made, new_soc ? : " << new_socket << endl;
    clients[numberOfClients] = new_socket;
    numberOfClients++;
    // new thread(recvSendStructure, new_socket, false);
    recvSendStructure(new_socket, alwaysReceive);
  }
}

int main(int argc, char const *argv[])
{
  Server server;
  server();
  // server(ALWAYS_RECV);
  return 0;
}
