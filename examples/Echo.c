#include "../lib/CServe.h"

// HandleRequest gets called whenever a new client is connected. Applications logic goes in here
void HandleRequest(int clientID, __CSERVE_Session session){
    char buffer[256];
    for(;;){
        read(session.sock, buffer, 255);
        if(strncmp(buffer,"quit",4) == 0){
            close(session.sock);
            break;
        } else {
            write(session.sock, buffer, strlen(buffer));
        }
    }
}

// CreateServerSocket starts a socket at port 8088. If it returns -1, something happened. ServerMainLoop takes in 3 parameters: the server's socket, the maximum number of users the server can accept, and the function to call to handle a client

int main(int argc, char** argv){
    int socket = CreateServerSocket(8088);
    if(socket == -1){
        printf("An error occurred\n");
        exit(0);
    }
    ServerMainLoop(socket, 20, HandleRequest);
}