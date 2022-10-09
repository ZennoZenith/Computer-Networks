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

using namespace std;

#define PORT 8080

int main(int argc, char const *argv[])
{
  int server_fd, new_socket, valread;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);
  char buffer[1024] = {0};
  char *hello = "Hello from server";

  // Creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("socket failed");
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
  // if (listen(server_fd, 3) < 0)
  // {
  //   perror("listen");
  //   exit(EXIT_FAILURE);
  // }

  while (true)
  {
    if (listen(server_fd, 3) < 0)
    {
      perror("listen");
      exit(EXIT_FAILURE);
    }
    new_socket = accept(server_fd, (struct sockaddr *)&address,
                        (socklen_t *)&addrlen);
    if (new_socket < 0)
    {
      perror("accept");
      exit(EXIT_FAILURE);
    }

    cout << "New conection made, new_soc ? : " << new_socket << endl;
    // declaring output string stream
    ostringstream str1;
    str1 << new_socket;
    string geek = str1.str();

    valread = read(new_socket, buffer, 1024);
    if (strcmp(buffer, "!exit") == 0)
    {
      // closing the connected socket
      close(new_socket);
      cout << "Closed connection\n";
    }

    printf("client(%d)> %s\n", new_socket, buffer);
    // send(new_socket, hello, strlen(hello), 0);
    char temp[100] = "Client message : ";
    strcat(temp, buffer);
    strcat(temp, "; Client Id : ");
    strcat(temp, geek.c_str());
    send(new_socket, temp, strlen(temp), 0);

    // send(new_socket, temp, strlen(temp), 0);
    // send(new_socket, temp, strlen(temp), 0);

    printf("Hello message sent\n");

    // closing the connected socket
    // close(new_socket);
  }
  // closing the listening socket
  shutdown(server_fd, SHUT_RDWR);
  return 0;
}
