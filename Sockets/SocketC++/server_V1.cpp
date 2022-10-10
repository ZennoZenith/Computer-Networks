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

// #include<st

using namespace std;

#define PORT 8080
#define REQUEST_QUEUE_LEN 3
#define MAX_CLIENTS 3

class Server;
class Message;

class Message
{
private:
  int from;
  int to;
  char *message;

public:
  Message(int, int, char *);
  const char *messageToJSON();
};

class Server
{
private:
  struct sockaddr_in address;
  int server_fd;
  // Client clients[MAX_CLIENTS];
  int numberOfClients;
  static void sendMsg(int, int, const char *);
  static void recvMsg(int);
  static void sendToAll(const char *);

public:
  // Server();
  Server(int);
  void operator()();
  ~Server();
};

Message::Message(int from, int to, char *message)
{
  this->from = from;
  this->to = to;
  this->message = message;
}
const char *Message::messageToJSON()
{
  char fromString[] = {'"', 'f', 'r', 'o', 'm', '"', ':', '"'};
  char toString[] = {'"', 't', 'o', '"', ':', '"'};
  ostringstream str1;
  str1 << '{';
  str1 << fromString << from << '"' << ',';
  str1 << toString << to << '"';
  str1 << '}';
  return str1.str().c_str();
}

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
}

void Server::operator()()
{
  if (listen(server_fd, REQUEST_QUEUE_LEN) < 0)
  {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  int addrlen = sizeof(address);

  while (true)
  {
    int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (new_socket < 0)
    {
      perror("accept");
      exit(EXIT_FAILURE);
    }
    cout << "New conection made, new_soc ? : " << new_socket << endl;
    numberOfClients++;
    new thread(recvMsg, new_socket);
  }
}

Server::~Server()
{
  shutdown(server_fd, SHUT_RDWR);
}

void Server::recvMsg(int new_socket)
{
  int valread;
  char buffer[1024] = {0};

  while (true)
  {
    valread = read(new_socket, buffer, 1024);
    if (strcmp(buffer, "!exit") == 0)
    {
      // closing the connected socket
      close(new_socket);
      printf("Closed connection, new_socket(%d)\n", new_socket);
      break;
    }
    printf("client(%d) valread(%d)> %s\n", new_socket, valread, buffer);
    // send(new_socket, hello, strlen(hello), 0);
    char temp[100] = "Client message : ";

    if (valread <= 0)
    {
      // closing the connected socket
      close(new_socket);
      printf("Closed connection, new_socket(%d)\n", new_socket);
      break;
    }
    buffer[valread] = '\0';
    sendMsg(new_socket, new_socket, buffer);
  }
}

void Server::sendMsg(int from_socket, int to_socket, const char *message = "\0")
{
  if (*message != '\0')
    send(to_socket, message, strlen(message), 0);
}

int main(int argc, char const *argv[])
{
  Server server;
  thread t(server);
  t.join();
  return 0;
}
