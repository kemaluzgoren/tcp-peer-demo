/**
 * @file      client.h
 * @author    Kemal UZGOREN
 *
 * @version   v1.0.0
 * @date      25.05.2025
 *
 * @details   
 */
#ifndef CLIENT_H_
#define CLIENT_H_

#include <sys/socket.h>
#include <netinet/in.h>


struct client_t {

    int socket; 
    int domain; 
    int service; 
    int protocol; 
    int port; 
    u_long interface; 

    char *(*request)(struct client_t *client, char *server_ip, void *request, unsigned long size); 

}; 

struct client_t client_constructor(int domain, int service, int protocol, int port, u_long interface); 


#endif  /*  CLIENT_H_   */