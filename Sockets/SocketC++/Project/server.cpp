// Server

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <string> // for string

using namespace std;

#define PORT 8080
#define REQUEST_QUEUE_LEN 3
#define NUMBER_BASE 10
#define NUMBER_OF_MESSAGES 10

const char sentMessages[NUMBER_OF_MESSAGES][100] = {
    "Well done is better than well said.",
    "Great ideas often receive violent opposition from mediocre minds.",
    "If it is not right do not do it; if it is not true do not say it.",
    "I checked to make sure that he was still alive.",
    "Don't wait for people to be friendly. Show them how.",
    "Sometimes the biggest act of courage is a small one.",
    "As long as your going to be thinking anyway, think big.",
    "As long as your going to be thinking anyway, think big.",
    "The cautious seldom err.",
    "Tom got a small piece of pie.",
};

int calculateWord(const char *sentence)
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

int intermediateFunc(char message[])
{
  char *strPtr = NULL;
  int result = strtol(message, &strPtr, NUMBER_BASE);
  return result;
}

class Server
{
private:
  struct sockaddr_in address;
  int server_fd;
  int numberOfClients;
  static char buffer[1024];
  static void sendMsg(int, int, const char *);
  static void closeConnection(int, const char *);
  static bool recvMsg(int);
  static void sendToAll(const char *);
  static void recvSendStructure(int, bool);

public:
  Server(int);
  void operator()(bool);
  ~Server();
};
char Server::buffer[1024];

Server::Server(int port = PORT)
{
  srand(time(0));

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
  printf(message, new_socket);
}

bool Server::recvMsg(int new_socket)
{
  int valread = read(new_socket, buffer, sizeof(buffer));
  if (strcmp(buffer, "!exit") == 0)
  {
    closeConnection(new_socket);
    return false;
  }

  if (valread <= 0)
    return false;

  buffer[valread] = '\0';
  return true;
}

void Server::sendMsg(int from_socket, int to_socket, const char *message = "\0")
{
  if (*message != '\0')
    send(to_socket, message, strlen(message), 0);
}

void Server::recvSendStructure(int new_socket, bool alwaysReceive = false)
{
  do
  {
    const char *message = sentMessages[rand() % NUMBER_OF_MESSAGES];
    int numberOfWords = calculateWord(message);
    sendMsg(new_socket, new_socket, message);
    if (!recvMsg(new_socket))
      break;

    printf("server  > %s\n", message);
    printf("expected message > %d\n", numberOfWords);
    printf("client(%d) > %s\n", new_socket, buffer);
    if (numberOfWords == intermediateFunc(buffer))
      sendMsg(new_socket, new_socket, "Accepted\n");
    else
      sendMsg(new_socket, new_socket, "Rejected\n");

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
    numberOfClients++;
    recvSendStructure(new_socket, alwaysReceive);
  }
}

int main(int argc, char const *argv[])
{
  Server server;
  server();
  return 0;
}
