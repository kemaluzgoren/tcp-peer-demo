/**
 * @file      server.h 
 * @author    Kemal UZGOREN
 *
 * @version   v1.0.0
 * @date      25.05.2025
 *
 * @details   
 */
#ifndef SERVER_H_
#define SERVER_H_

#include "dictionary.h"

#include <sys/socket.h>
#include <netinet/in.h>

struct server_t {

    int domain; 
    int service; 
    int protocol; 
    u_long interface; 
    int port; 
    int backlog; 
    struct sockaddr_in address; 
    int socket; 

    struct dictionary_t router; 

    void (*register_routes)(struct server_t *server, 
                            char *(*router_function)(void *arg),
                            char *path); 

};

struct server_route_t {
    char *(*router_function)(void *arg); 
}; 

struct server_t server_constructor(int domin, int service, int protocol, u_long interface, int port, int backlog); 


#endif  /*  SERVER_H_   */